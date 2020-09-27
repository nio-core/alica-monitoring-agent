#include <conversion/RoleSwitch.h>
#include <stdexcept>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>


namespace conversion {
    RoleSwitch RoleSwitch::from(capnp::MessageReader &reader) {
        auto roleSwitch = reader.getRoot<alica_msgs::RoleSwitch>();
        if (!isValid(roleSwitch)) {
            throw std::runtime_error("Invalid Role Switch");
        }

        auto senderIdReader = roleSwitch.getSenderId();
        auto senderId = capnzero::Id::from(senderIdReader);

        return {
                senderId,
                roleSwitch.getRoleId(),
                roleSwitch.getType()
        };
    }

    bool RoleSwitch::isValid(alica_msgs::RoleSwitch::Reader &reader) {
        return reader.hasSenderId() && reader.hasType();
    }

    RoleSwitch::RoleSwitch(const capnzero::Id &senderId, int64_t roleId, const std::string &type)
            : senderId_(senderId), roleId_(roleId), type_(type) {}

    capnzero::Id RoleSwitch::getSenderId() const {
        return senderId_;
    }

    int64_t RoleSwitch::getRoleId() const {
        return roleId_;
    }

    const std::string RoleSwitch::toJson() const {
        rapidjson::Document roleSwitch(rapidjson::kObjectType);

        rapidjson::Document senderId;
        senderId.Parse(senderId_.toJson().c_str());
        roleSwitch.AddMember("senderId", senderId.GetObject(), roleSwitch.GetAllocator());

        roleSwitch.AddMember("roleId", roleId_, roleSwitch.GetAllocator());

        rapidjson::Value type;
        type.SetString(type_.c_str(), type_.size());
        roleSwitch.AddMember("type", type, roleSwitch.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        roleSwitch.Accept(writer);

        return buffer.GetString();

    }
}