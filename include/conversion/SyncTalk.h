#pragma once

#include <conversion/capnzero/Id.h>
#include "SyncData.h"

namespace conversion {
    class SyncTalk {
    public:
        static SyncTalk from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::SyncTalk::Reader &reader);

    public:
        SyncTalk(const capnzero::Id &senderId, std::vector<SyncData> &syncData);

        capnzero::Id getSenderId() const;

        std::vector<SyncData> getSyncData() const;

        const std::string toJson() const;

    private:
        capnzero::Id senderId_;
        std::vector<SyncData> syncData_;
    };
}