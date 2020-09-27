#pragma once

#include <capnp/message.h>
#include <conversion/capnzero/Id.h>
#include <RoleSwitch.capnp.h>


namespace conversion {
    class RoleSwitch {
    public:
        static RoleSwitch from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::RoleSwitch::Reader &reader);

    public:
        RoleSwitch(const capnzero::Id &senderId, int64_t roleId, const std::string &type);

        capnzero::Id getSenderId() const;

        int64_t getRoleId() const;

        const std::string toJson() const;

    private:
        capnzero::Id senderId_;
        int64_t roleId_;
        std::string type_;
    };
}