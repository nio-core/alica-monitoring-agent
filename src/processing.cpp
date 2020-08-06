#include <processing.h>
#include <iostream>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <json_helper.h>
#include <rapidjson/writer.h>

bool is_valid(alica_msgs::SyncReady::Reader& syncReady) {
    return syncReady.hasSenderId();
}

bool is_valid(alica_msgs::SyncTalk::Reader& syncTalk) {
    auto syncDataIsValid = true;
    for(auto entry: syncTalk.getSyncData()) {
        syncDataIsValid = syncDataIsValid && entry.hasRobotId();
    }
    return syncTalk.hasSenderId() && syncTalk.hasSyncData() && syncDataIsValid;
}

std::string processing::sync_ready_capnproto_to_json(::capnp::FlatArrayMessageReader &reader) {
    auto syncReady = reader.getRoot<alica_msgs::SyncReady>();
    std::cout << "+++ Received sync ready" << std::endl;
    if(!is_valid(syncReady)) {
        throw std::runtime_error("Could not parse Sync Ready from message");
    }

    rapidjson::Document doc(rapidjson::kObjectType);
    auto senderId = helper::capnzero_id_to_json_value(syncReady.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());
    doc.AddMember("synchronisationId", syncReady.getSynchronisationId(), doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

std::string processing::sync_talk_capnproto_to_json(::capnp::FlatArrayMessageReader &reader) {
    auto syncTalk = reader.getRoot<alica_msgs::SyncTalk>();
    std::cout << "+++ Received sync talk" << std::endl;
    if(!is_valid(syncTalk)) {
        throw std::runtime_error("Could not parse Sync Talk from message");
    }

    rapidjson::Document doc(rapidjson::kObjectType);
    auto senderId = helper::capnzero_id_to_json_value(syncTalk.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());
    rapidjson::Value syncData(rapidjson::kArrayType);
    for(auto d: syncTalk.getSyncData()) {
        rapidjson::Value data(rapidjson::kObjectType);
        auto robotId = helper::capnzero_id_to_json_value(d.getRobotId(), doc.GetAllocator());
        data.AddMember("robotId", robotId, doc.GetAllocator());
        data.AddMember("transitionId", d.getTransitionId(), doc.GetAllocator());
        data.AddMember("transitionHolds", d.getTransitionHolds(), doc.GetAllocator());
        data.AddMember("ack", d.getAck(), doc.GetAllocator());
        syncData.PushBack(data, doc.GetAllocator());
    }
    doc.AddMember("syncData", syncData, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}