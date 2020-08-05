#pragma once

#include <capnp/message.h>
#include <model/capnzero/Id.h>

class RoleSwitch {

public:
    RoleSwitch(const capnzero::Id &senderId, int64_t roleId);

    static RoleSwitch from(capnp::MessageReader &reader);

    capnzero::Id getSenderId() const;

    int64_t getRoleId() const;

    const std::string toJson() const;

private:
    capnzero::Id senderId_;
    int64_t roleId_;
};
