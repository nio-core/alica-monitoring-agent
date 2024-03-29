#pragma once

#include <string>
#include <model/capnzero/Id.h>
#include <SyncReady.capnp.h>

namespace model {
    class SyncReady {
    public:
        static SyncReady from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::SyncReady::Reader &reader);

    public:
        SyncReady(const capnzero::Id &senderId, int64_t syncId);

        capnzero::Id getSenderId() const;

        int64_t getSyncId() const;

    private:
        capnzero::Id senderId_;
        int64_t syncId_;
    };
}