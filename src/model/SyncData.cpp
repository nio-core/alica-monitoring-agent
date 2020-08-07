#include <model/SyncData.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <SyncTalk.capnp.h>

SyncData::SyncData(const capnzero::Id &robotId, int64_t transitionId, bool transitionHolds, bool ack)
        : robotId_(robotId), transitionId_(transitionId), transitionHolds_(transitionHolds), ack_(ack) {}

const std::string SyncData::toJson() const {
    rapidjson::Document syncData(rapidjson::kObjectType);

    rapidjson::Document robotId;
    robotId.Parse(robotId_.toJson().c_str());
    syncData.AddMember("robotId", robotId, syncData.GetAllocator());
    syncData.AddMember("transitionId", transitionId_, syncData.GetAllocator());
    syncData.AddMember("transitionHolds", transitionHolds_, syncData.GetAllocator());
    syncData.AddMember("ack", ack_, syncData.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    syncData.Accept(writer);

    return buffer.GetString();
}

SyncData SyncData::from(capnp::MessageReader& reader) {
    auto syncData = reader.getRoot<alica_msgs::SyncData>();
    return from(syncData);
}

SyncData SyncData::from(alica_msgs::SyncData::Reader& syncData) {
    if(!syncData.hasRobotId()) {
        throw std::runtime_error("Invalid Sync Data");
    }

    auto robotIdReader = syncData.getRobotId();
    auto robotId = capnzero::Id::from(robotIdReader);

    return {
            robotId,
            syncData.getTransitionId(),
            syncData.getTransitionHolds(),
            syncData.getAck()
    };
}