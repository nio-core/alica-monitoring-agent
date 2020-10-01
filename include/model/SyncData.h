#pragma once

#include <string>
#include <model/capnzero/Id.h>
#include <SyncTalk.capnp.h>

namespace model {
    class SyncData {
    public:
        static SyncData from(capnp::MessageReader &reader);

        static SyncData from(alica_msgs::SyncData::Reader &reader);

        static bool isValid(alica_msgs::SyncData::Reader &reader);

    public:
        SyncData(const capnzero::Id &robotId, int64_t transitionId, bool transitionHolds, bool ack);

        capnzero::Id getRobotId() const;

        int64_t getTransitionId() const;

        bool transitionHolds() const;

        bool ack() const;

        const std::string toJson() const;

    private:
        capnzero::Id robotId_;
        int64_t transitionId_;
        bool transitionHolds_;
        bool ack_;
    };
}