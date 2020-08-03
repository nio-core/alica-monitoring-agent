#include <processing.h>
#include <iostream>
#include <AlicaEngineInfo.capnp.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <PlanTreeInfo.capnp.h>
#include <RoleSwitch.capnp.h>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <json_helper.h>

bool is_valid(alica_msgs::AlicaEngineInfo::Reader& engineInfo) {
    return engineInfo.hasSenderId() && engineInfo.hasMasterPlan() && engineInfo.hasCurrentPlan()
        && engineInfo.hasCurrentTask() && engineInfo.hasCurrentState() && engineInfo.hasCurrentRole()
        && engineInfo.hasAgentIdsWithMe();
}

bool is_valid(alica_msgs::AllocationAuthorityInfo::Reader& allocationAuthorityInfo) {
    return allocationAuthorityInfo.hasAuthority() && allocationAuthorityInfo.hasSenderId()
        && allocationAuthorityInfo.hasEntrypointRobots();
}

bool is_valid(alica_msgs::PlanTreeInfo::Reader& planTreeInfo) {
    return planTreeInfo.hasSenderId() && planTreeInfo.hasStateIds() && planTreeInfo.hasSucceededEps();
}

bool is_valid(alica_msgs::RoleSwitch::Reader& roleSwitch) {
    return roleSwitch.hasSenderId();
}

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

std::string processing::alica_engine_info_capnproto_to_json(::capnp::FlatArrayMessageReader& reader) {
    auto alicaEngineInfo = reader.getRoot<alica_msgs::AlicaEngineInfo>();
    if(!is_valid(alicaEngineInfo)) {
        throw std::runtime_error("Could not read Alica Engine Info from message");
    }
    std::cout << "+++ Received alica engine information" << std::endl;

    rapidjson::Document doc(rapidjson::kObjectType);
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value val;

    auto senderId = helper::capnzero_id_to_json_value(alicaEngineInfo.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());

    val.SetString(alicaEngineInfo.getCurrentPlan().cStr(), static_cast<rapidjson::SizeType>(alicaEngineInfo.getCurrentPlan().size()));
    doc.AddMember("currentPlan", val, doc.GetAllocator());

    val.SetString(alicaEngineInfo.getMasterPlan().cStr(), static_cast<rapidjson::SizeType>(alicaEngineInfo.getMasterPlan().size()));
    doc.AddMember("masterPlan", val, doc.GetAllocator());

    val.SetString(alicaEngineInfo.getCurrentState().cStr(), static_cast<rapidjson::SizeType>(alicaEngineInfo.getCurrentState().size()));
    doc.AddMember("currentState", val, doc.GetAllocator());

    val.SetString(alicaEngineInfo.getCurrentRole().cStr(), static_cast<rapidjson::SizeType>(alicaEngineInfo.getCurrentRole().size()));
    doc.AddMember("currentRole", val, doc.GetAllocator());

    val.SetString(alicaEngineInfo.getCurrentTask().cStr(), static_cast<rapidjson::SizeType>(alicaEngineInfo.getCurrentTask().size()));
    doc.AddMember("currentTask", val, doc.GetAllocator());

    for(auto agent: alicaEngineInfo.getAgentIdsWithMe()) {
        rapidjson::Value entry = helper::capnzero_id_to_json_value(agent, doc.GetAllocator());
        array.PushBack(entry, doc.GetAllocator());
    }
    doc.AddMember("agentsWithMe", array, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

std::string processing::allocation_authority_info_capnproto_to_json(::capnp::FlatArrayMessageReader &reader) {
    auto allocationAuthorityInformation = reader.getRoot<alica_msgs::AllocationAuthorityInfo>();
    if(!is_valid(allocationAuthorityInformation)) {
        throw std::runtime_error("Could not parse Allocation Authority Info from message");
    }
    std::cout << "+++ Received allocation authority information" << std::endl;

    rapidjson::Document doc(rapidjson::kObjectType);
    rapidjson::Value val;

    val.SetInt64(allocationAuthorityInformation.getParentState());
    doc.AddMember("parentState", val, doc.GetAllocator());

    val.SetInt64(allocationAuthorityInformation.getPlanType());
    doc.AddMember("planType", val, doc.GetAllocator());

    val.SetInt64(allocationAuthorityInformation.getPlanId());
    doc.AddMember("planId", val, doc.GetAllocator());

    auto authority = helper::capnzero_id_to_json_value(allocationAuthorityInformation.getAuthority(), doc.GetAllocator());
    doc.AddMember("authority", authority, doc.GetAllocator());

    auto senderId = helper::capnzero_id_to_json_value(allocationAuthorityInformation.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());

    rapidjson::Value entryPointRobots(rapidjson::kArrayType);
    for(auto entryPointRobot: allocationAuthorityInformation.getEntrypointRobots()) {
        rapidjson::Value epr(rapidjson::kObjectType);
        epr.AddMember("entryPoint", entryPointRobot.getEntrypoint(), doc.GetAllocator());
        rapidjson::Value robots(rapidjson::kArrayType);
        for(auto robot: entryPointRobot.getRobots()) {
            auto r = helper::capnzero_id_to_json_value(robot, doc.GetAllocator());
            robots.PushBack(r, doc.GetAllocator());
        }
        epr.AddMember("robots", robots, doc.GetAllocator());
        entryPointRobots.PushBack(epr, doc.GetAllocator());
    }
    doc.AddMember("entryPointRobots", entryPointRobots, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

std::string processing::plan_tree_info_capnproto_to_json(::capnp::FlatArrayMessageReader &reader) {
    auto planTreeInfo = reader.getRoot<alica_msgs::PlanTreeInfo>();
    if(!is_valid(planTreeInfo)) {
        throw std::runtime_error("Could not parse Plan Tree Info from message");
    }
    std::cout << "+++ Received plan tree information" << std::endl;

    rapidjson::Document doc(rapidjson::kObjectType);
    auto senderId = helper::capnzero_id_to_json_value(planTreeInfo.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());

    rapidjson::Value stateIds(rapidjson::kArrayType);
    for(auto stateId: planTreeInfo.getStateIds()) {
        stateIds.PushBack(stateId, doc.GetAllocator());
    }
    doc.AddMember("stateIds", stateIds, doc.GetAllocator());

    rapidjson::Value succeededEps(rapidjson::kArrayType);
    for(auto ep: planTreeInfo.getSucceededEps()) {
        succeededEps.PushBack(ep, doc.GetAllocator());
    }
    doc.AddMember("succeededEps", succeededEps, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

std::string processing::role_switch_capnproto_to_json(::capnp::FlatArrayMessageReader &reader) {
    auto roleSwitch = reader.getRoot<alica_msgs::RoleSwitch>();
    if(!is_valid(roleSwitch)) {
        throw std::runtime_error("Could not parse Role Switch from message");
    }
    std::cout << "+++ Received role switch" << std::endl;

    rapidjson::Document doc(rapidjson::kObjectType);
    auto senderId = helper::capnzero_id_to_json_value(roleSwitch.getSenderId(), doc.GetAllocator());
    doc.AddMember("senderId", senderId, doc.GetAllocator());
    doc.AddMember("roleId", roleSwitch.getRoleId(), doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
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
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
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
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
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
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}