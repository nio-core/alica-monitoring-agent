#include <model/RoleSwitch.h>
#include <stdexcept>
#include <RoleSwitch.capnp.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

RoleSwitch::RoleSwitch(const capnzero::Id &senderId, int64_t roleId) : senderId_(senderId), roleId_(roleId) {}

RoleSwitch RoleSwitch::from(capnp::MessageReader &reader) {
    auto roleSwitch = reader.getRoot<alica_msgs::RoleSwitch>();
    if(!roleSwitch.hasSenderId()) {
        throw std::runtime_error("Invalid Role Switch");
    }

    auto senderIdReader = roleSwitch.getSenderId();
    auto senderId = capnzero::Id::from(senderIdReader);

    return {
        senderId,
        roleSwitch.getRoleId()
    };
}

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

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    roleSwitch.Accept(writer);

    return buffer.GetString();

}
