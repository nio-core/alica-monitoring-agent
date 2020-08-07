#pragma once

#include <string>
#include <model/capnzero/Id.h>
#include <SyncTalk.capnp.h>

class SyncData {

public:
    SyncData(const capnzero::Id &robotId, int64_t transitionId, bool transitionHolds, bool ack);

    const std::string toJson() const;

    static SyncData from(capnp::MessageReader &reader);

    static SyncData from(alica_msgs::SyncData::Reader& syncData);

    capnzero::Id getRobotId() const;

    int64_t getTransitionId() const;

    bool transition_holds() const;

    bool ack() const;

private:
    capnzero::Id robotId_;
    int64_t transitionId_;
    bool transitionHolds_;
    bool ack_;
};
