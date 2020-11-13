#include <model/RoleSwitch.h>
#include <stdexcept>

namespace model {
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


    std::string RoleSwitch::getType() const {
        return type_;
    }
}