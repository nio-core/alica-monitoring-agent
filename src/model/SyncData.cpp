#include <model/SyncData.h>
#include <stdexcept>

namespace model {
    SyncData SyncData::from(capnp::MessageReader &reader) {
        auto syncData = reader.getRoot<alica_msgs::SyncData>();
        return from(syncData);
    }

    SyncData SyncData::from(alica_msgs::SyncData::Reader &reader) {
        if (!reader.hasRobotId()) {
            throw std::runtime_error("Invalid Sync Data");
        }

        auto robotIdReader = reader.getRobotId();
        auto robotId = capnzero::Id::from(robotIdReader);

        return {
                robotId,
                reader.getTransitionId(),
                reader.getTransitionHolds(),
                reader.getAck()
        };
    }

    bool SyncData::isValid(alica_msgs::SyncData::Reader &reader) {
        return reader.hasRobotId();
    }

    SyncData::SyncData(const capnzero::Id &robotId, int64_t transitionId, bool transitionHolds, bool ack)
            : robotId_(robotId), transitionId_(transitionId), transitionHolds_(transitionHolds), ack_(ack) {}

    capnzero::Id SyncData::getRobotId() const {
        return robotId_;
    }

    int64_t SyncData::getTransitionId() const {
        return transitionId_;
    }

    bool SyncData::transitionHolds() const {
        return transitionHolds_;
    }

    bool SyncData::ack() const {
        return ack_;
    }
}