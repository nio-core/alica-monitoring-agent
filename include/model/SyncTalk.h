#pragma once

#include <model/capnzero/Id.h>
#include "SyncData.h"

class SyncTalk {

public:
    SyncTalk(const capnzero::Id &senderId, std::vector<SyncData> &syncData);

    const std::string toJson() const;

    static SyncTalk from(capnp::MessageReader& reader);

    capnzero::Id getSenderId() const;

    std::vector<SyncData> getSyncData() const;

private:
    capnzero::Id senderId_;
    std::vector<SyncData> syncData_;

    static bool isValid(alica_msgs::SyncTalk::Reader &reader);
};
