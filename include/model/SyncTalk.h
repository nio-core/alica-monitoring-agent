#pragma once

#include <model/capnzero/Id.h>
#include <model/SyncData.h>

namespace model {
    class SyncTalk {
    public:
        static SyncTalk from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::SyncTalk::Reader &reader);

    public:
        SyncTalk(const capnzero::Id &senderId, std::vector<SyncData> &syncData);

        capnzero::Id getSenderId() const;

        std::vector<SyncData> getSyncData() const;

    private:
        capnzero::Id senderId_;
        std::vector<SyncData> syncData_;
    };
}