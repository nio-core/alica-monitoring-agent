#include <serialization/JsonSerializationStrategy.h>
#include <rapidjson/pointer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

std::string to_string(rapidjson::Document& doc) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return buffer.GetString();
}

std::string JsonSerializationStrategy::serializeCapnzeroId(model::capnzero::Id &id) const {
    rapidjson::Document idJson(rapidjson::kObjectType);
    rapidjson::Value genericJsonValue;

    genericJsonValue.SetUint(id.getType());
    idJson.AddMember("type", genericJsonValue, idJson.GetAllocator());

    auto value = id.getValue();
    auto stringifiedValue = std::string(value.begin(), value.end());
    genericJsonValue.SetString(stringifiedValue.c_str(), stringifiedValue.size(), idJson.GetAllocator());
    idJson.AddMember("value", genericJsonValue, idJson.GetAllocator());

    return to_string(idJson);
}

std::string JsonSerializationStrategy::serializeEntryPointRobots(model::EntrypointRobots &entrypointRobots) const {
    rapidjson::Document entrypointRobotsJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    genericJsonValue.SetInt64(entrypointRobots.getEntrypoint());
    entrypointRobotsJson.AddMember("entrypoint", genericJsonValue, entrypointRobotsJson.GetAllocator());

    auto robots = entrypointRobots.getRobots();
    genericJsonValue.SetArray().Reserve(robots.size(), entrypointRobotsJson.GetAllocator());
    for (auto robot: robots) {
        genericJsonDocument.Parse(serializeCapnzeroId(robot).c_str());
        genericJsonValue.PushBack(genericJsonDocument, entrypointRobotsJson.GetAllocator());
    }
    entrypointRobotsJson.AddMember("robots", genericJsonValue, entrypointRobotsJson.GetAllocator());

    return to_string(entrypointRobotsJson);
}

std::string JsonSerializationStrategy::serializeSolverVar(model::SolverVar &solverVar) const {
    rapidjson::Document solverVarJson(rapidjson::kObjectType);
    rapidjson::Value genericJsonValue;

    genericJsonValue.SetInt64(solverVar.getId());
    solverVarJson.AddMember("id", genericJsonValue, solverVarJson.GetAllocator());

    auto value = solverVar.getValue();
    genericJsonValue.SetArray().Reserve(value.size(), solverVarJson.GetAllocator());
    for (auto entry: value) {
        genericJsonValue.PushBack(entry, solverVarJson.GetAllocator());
    }
    solverVarJson.AddMember("value", genericJsonValue, solverVarJson.GetAllocator());

    return to_string(solverVarJson);
}

std::string JsonSerializationStrategy::serializeSyncData(model::SyncData &syncData) const {
    rapidjson::Document syncDataJson(rapidjson::kObjectType);
    rapidjson::Document robotIdJson;

    auto robotId = syncData.getRobotId();
    robotIdJson.Parse(serializeCapnzeroId(robotId).c_str());
    syncDataJson.AddMember("robotId", robotIdJson, syncDataJson.GetAllocator());
    syncDataJson.AddMember("transitionId", syncData.getTransitionId(), syncDataJson.GetAllocator());
    syncDataJson.AddMember("transitionHolds", syncData.transitionHolds(), syncDataJson.GetAllocator());
    syncDataJson.AddMember("ack", syncData.ack(), syncDataJson.GetAllocator());

    return to_string(syncDataJson);
}

std::string JsonSerializationStrategy::serializeAlicaEngineInfo(model::AlicaEngineInfo &alicaEngineInfo) const {
    rapidjson::Document alicaEngineInfoJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    auto senderId = alicaEngineInfo.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    alicaEngineInfoJson.AddMember("senderId", genericJsonDocument.GetObject(), alicaEngineInfoJson.GetAllocator());

    auto currentPlan = alicaEngineInfo.getCurrentPlan();
    genericJsonValue.SetString(currentPlan.c_str(), currentPlan.size(), alicaEngineInfoJson.GetAllocator());
    alicaEngineInfoJson.AddMember("currentPlan", genericJsonValue, alicaEngineInfoJson.GetAllocator());

    auto masterPlan = alicaEngineInfo.getMasterPlan();
    genericJsonValue.SetString(masterPlan.c_str(), masterPlan.size(), alicaEngineInfoJson.GetAllocator());
    alicaEngineInfoJson.AddMember("masterPlan", genericJsonValue, alicaEngineInfoJson.GetAllocator());

    auto currentState = alicaEngineInfo.getCurrentState();
    genericJsonValue.SetString(currentState.c_str(), currentState.size(), alicaEngineInfoJson.GetAllocator());
    alicaEngineInfoJson.AddMember("currentState", genericJsonValue, alicaEngineInfoJson.GetAllocator());

    auto currentRole = alicaEngineInfo.getCurrentRole();
    genericJsonValue.SetString(currentRole.c_str(), currentRole.size(), alicaEngineInfoJson.GetAllocator());
    alicaEngineInfoJson.AddMember("currentRole", genericJsonValue, alicaEngineInfoJson.GetAllocator());

    auto currentTask = alicaEngineInfo.getCurrentTask();
    genericJsonValue.SetString(currentTask.c_str(), currentTask.size(), alicaEngineInfoJson.GetAllocator());
    alicaEngineInfoJson.AddMember("currentTask", genericJsonValue, alicaEngineInfoJson.GetAllocator());

    auto agentIdsWithMe = alicaEngineInfo.getAgentIdsWithMe();
    genericJsonValue.SetArray().Reserve(agentIdsWithMe.size(), alicaEngineInfoJson.GetAllocator());
    for (auto agent: agentIdsWithMe) {
        genericJsonDocument.Parse(serializeCapnzeroId(agent).c_str());
        genericJsonValue.PushBack(genericJsonDocument, alicaEngineInfoJson.GetAllocator());
    }
    alicaEngineInfoJson.AddMember("agentIdsWithMe", genericJsonValue, alicaEngineInfoJson.GetAllocator());

    return to_string(alicaEngineInfoJson);
}

std::string JsonSerializationStrategy::serializeAllocationAuthorityInfo(
        model::AllocationAuthorityInfo &allocationAuthorityInfo) const {
    rapidjson::Document allocationAuthorityInfoJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    allocationAuthorityInfoJson.AddMember("parentState", allocationAuthorityInfo.getParentState(), allocationAuthorityInfoJson.GetAllocator());
    allocationAuthorityInfoJson.AddMember("planType", allocationAuthorityInfo.getPlanType(), allocationAuthorityInfoJson.GetAllocator());
    allocationAuthorityInfoJson.AddMember("planId", allocationAuthorityInfo.getPlanId(), allocationAuthorityInfoJson.GetAllocator());

    auto authority = allocationAuthorityInfo.getAuthority();
    genericJsonDocument.Parse(serializeCapnzeroId(authority).c_str());
    allocationAuthorityInfoJson.AddMember("authority", genericJsonDocument, allocationAuthorityInfoJson.GetAllocator());

    auto senderId = allocationAuthorityInfo.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    allocationAuthorityInfoJson.AddMember("senderId", genericJsonDocument, allocationAuthorityInfoJson.GetAllocator());

    auto entrypointRobots = allocationAuthorityInfo.getEntrypointRobots();
    genericJsonValue.SetArray().Reserve(entrypointRobots.size(), allocationAuthorityInfoJson.GetAllocator());
    for (auto entryPointRobot: entrypointRobots) {
        genericJsonDocument.Parse(serializeEntryPointRobots(entryPointRobot).c_str());
        genericJsonValue.PushBack(genericJsonDocument, allocationAuthorityInfoJson.GetAllocator());
    }
    allocationAuthorityInfoJson.AddMember("entrypointRobots", genericJsonValue, allocationAuthorityInfoJson.GetAllocator());

    return to_string(allocationAuthorityInfoJson);
}

std::string JsonSerializationStrategy::serializePlanTreeInfo(model::PlanTreeInfo &planTreeInfo) const {
    rapidjson::Document planTreeInfoJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    auto senderId = planTreeInfo.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    planTreeInfoJson.AddMember("senderId", genericJsonDocument, planTreeInfoJson.GetAllocator());

    auto stateIds = planTreeInfo.getStateIds();
    genericJsonValue.SetArray().Reserve(stateIds.size(), planTreeInfoJson.GetAllocator());
    for (auto stateId: stateIds) {
        genericJsonValue.PushBack(stateId, planTreeInfoJson.GetAllocator());
    }
    planTreeInfoJson.AddMember("stateIds", genericJsonValue, planTreeInfoJson.GetAllocator());

    auto succeededEps = planTreeInfo.getSucceededEps();
    genericJsonValue.SetArray().Reserve(succeededEps.size(), planTreeInfoJson.GetAllocator());
    for (auto succeededEp: succeededEps) {
        genericJsonValue.PushBack(succeededEp, planTreeInfoJson.GetAllocator());
    }
    planTreeInfoJson.AddMember("succeededEps", genericJsonValue, planTreeInfoJson.GetAllocator());

    return to_string(planTreeInfoJson);
}

std::string JsonSerializationStrategy::serializeRoleSwitch(model::RoleSwitch &roleSwitch) const {
    rapidjson::Document roleSwitchJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    auto senderId = roleSwitch.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    roleSwitchJson.AddMember("senderId", genericJsonDocument, roleSwitchJson.GetAllocator());
    roleSwitchJson.AddMember("roleId", roleSwitch.getRoleId(), roleSwitchJson.GetAllocator());

    auto type = roleSwitch.getType();
    genericJsonValue.SetString(type.c_str(), type.size(), roleSwitchJson.GetAllocator());
    roleSwitchJson.AddMember("type", genericJsonValue, roleSwitchJson.GetAllocator());

    return to_string(roleSwitchJson);
}

std::string JsonSerializationStrategy::serializeSolverResult(model::SolverResult &solverResult) const {
    rapidjson::Document solverResultJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    auto senderId = solverResult.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    solverResultJson.AddMember("senderId", genericJsonDocument, solverResultJson.GetAllocator());

    auto vars = solverResult.getVars();
    genericJsonValue.SetArray().Reserve(vars.size(), solverResultJson.GetAllocator());
    for (auto var: vars) {
        genericJsonDocument.Parse(serializeSolverVar(var).c_str());
        genericJsonValue.PushBack(genericJsonDocument, solverResultJson.GetAllocator());
    }
    solverResultJson.AddMember("vars", genericJsonValue, solverResultJson.GetAllocator());

    return to_string(solverResultJson);
}

std::string JsonSerializationStrategy::serializeSyncReady(model::SyncReady &syncReady) const {
    rapidjson::Document syncReadyJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;

    auto senderId = syncReady.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    syncReadyJson.AddMember("senderId", genericJsonDocument, syncReadyJson.GetAllocator());
    syncReadyJson.AddMember("synchronisationId", syncReady.getSyncId(), syncReadyJson.GetAllocator());

    return to_string(syncReadyJson);
}

std::string JsonSerializationStrategy::serializeSyncTalk(model::SyncTalk &syncTalk) const {
    rapidjson::Document syncTalkJson(rapidjson::kObjectType);
    rapidjson::Document genericJsonDocument;
    rapidjson::Value genericJsonValue;

    auto senderId = syncTalk.getSenderId();
    genericJsonDocument.Parse(serializeCapnzeroId(senderId).c_str());
    syncTalkJson.AddMember("senderId", genericJsonDocument, syncTalkJson.GetAllocator());

    auto syncData = syncTalk.getSyncData();
    genericJsonValue.SetArray().Reserve(syncData.size(), syncTalkJson.GetAllocator());
    for (auto data: syncData) {
        genericJsonDocument.Parse(serializeSyncData(data).c_str());
        genericJsonValue.PushBack(genericJsonDocument, syncTalkJson.GetAllocator());
    }
    syncTalkJson.AddMember("syncData", genericJsonValue, syncTalkJson.GetAllocator());

    return to_string(syncTalkJson);
}
