#pragma once

#include <string>
#include <model/capnzero/Id.h>

class SyncReady {

public:
    SyncReady(const capnzero::Id &senderId, int64_t syncId);

    const std::string toJson() const;

    static SyncReady from(capnp::MessageReader &reader);

    capnzero::Id getSenderId() const;

    int64_t getSyncId() const;

private:
    capnzero::Id senderId_;
    int64_t syncId_;
};
