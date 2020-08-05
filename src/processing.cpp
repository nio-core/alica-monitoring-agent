#include <processing.h>
#include <iostream>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <json_helper.h>
#include <rapidjson/writer.h>

bool is_valid(alica_msgs::SolverResult::Reader& solverResult) {
    bool varsAreValid = true;
    for(auto var: solverResult.getVars()) {
        varsAreValid = varsAreValid && var.hasValue();
    }
    return solverResult.hasSenderId() && solverResult.hasVars() && varsAreValid;
}

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

std::string processing::solver_result_capnproto_to_json(::capnp::FlatArrayMessageReader &reader) {
    auto solverResult = reader.getRoot<alica_msgs::SolverResult>();
    if(!is_valid(solverResult)) {
        throw std::runtime_error("Could not parse Solver Result from message");
    }

    rapidjson::Document doc(rapidjson::kObjectType);
    auto senderId = helper::capnzero_id_to_json_value(solverResult.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());

    rapidjson::Value vars(rapidjson::kArrayType);
    for(auto v: solverResult.getVars()) {
        rapidjson::Value var(rapidjson::kObjectType);
        var.AddMember("id", v.getId(), doc.GetAllocator());

        rapidjson::Value value(rapidjson::kArrayType);
        for(auto val: v.getValue()) {
            value.PushBack(val, doc.GetAllocator());
        }
        var.AddMember("value", value, doc.GetAllocator());
        vars.PushBack(var, doc.GetAllocator());
    }
    doc.AddMember("vars", vars, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
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