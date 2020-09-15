#include <test_messages_common.h>
#include <test_values_common.h>
#include <capnzero/ID.capnp.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <AlicaEngineInfo.capnp.h>
#include <PlanTreeInfo.capnp.h>
#include <RoleSwitch.capnp.h>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>
#include <capnp/message.h>


kj::Array<capnp::word> capnzero_id_message() {
    capnp::MallocMessageBuilder builder;
    auto id = builder.initRoot<capnzero::ID>();
    id.setValue(kj::StringPtr(ID_VALUE).asBytes());
    id.setType(ID_TYPE);

    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> prepare_allocation_authority_info_message() {
    capnp::MallocMessageBuilder builder;
    auto allocationAuthorityInformation = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    allocationAuthorityInformation.setParentState(PARENT_STATE);
    allocationAuthorityInformation.setPlanType(PLAN_TYPE);
    allocationAuthorityInformation.setPlanId(PLAN_ID);
    auto authority = allocationAuthorityInformation.initAuthority();
    authority.setType(ID_TYPE);
    authority.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto senderId = allocationAuthorityInformation.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto entryPoints = allocationAuthorityInformation.initEntrypointRobots(ENTRY_POINT_COUNT);
    for(auto entryPoint: entryPoints) {
        entryPoint.setEntrypoint(ENTRY_POINT);
        auto robots = entryPoint.initRobots(ROBOT_COUNT);
        for(auto robot: robots) {
            robot.setType(ID_TYPE);
            robot.setValue(kj::StringPtr(ID_VALUE).asBytes());
        }
    }
    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> entrypoint_robots_message() {
    capnp::MallocMessageBuilder builder;
    auto entryPointRobots = builder.initRoot<alica_msgs::EntrypointRobots>();
    entryPointRobots.setEntrypoint(ENTRY_POINT);
    auto robots = entryPointRobots.initRobots(ROBOT_COUNT);
    for(auto robot: robots) {
        robot.setType(ID_TYPE);
        robot.setValue(kj::StringPtr(ID_VALUE).asBytes());
    }

    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> alica_engine_info_message() {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    engineInfo.setMasterPlan(MASTER_PLAN);
    engineInfo.setCurrentPlan(PLAN);
    engineInfo.setCurrentState(STATE);
    engineInfo.setCurrentRole(ROLE);
    engineInfo.setCurrentTask(TASK);
    auto senderId = engineInfo.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto agentsWithMe = engineInfo.initAgentIdsWithMe(AGENT_COUNT);
    for(int i = 0; i < AGENT_COUNT; i++) {
        agentsWithMe[i].setType(ID_TYPE);
        agentsWithMe[i].setValue(kj::StringPtr(ID_VALUE).asBytes());
    }

    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> plan_tree_info_message() {
    capnp::MallocMessageBuilder builder;
    auto planTreeInfo = builder.initRoot<alica_msgs::PlanTreeInfo>();
    auto senderId = planTreeInfo.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto stateIds = planTreeInfo.initStateIds(STATE_ID_COUNT);
    for(int i = 0; i < STATE_ID_COUNT; i++) {
        stateIds.set(i, i);
    }
    auto succeededEps = planTreeInfo.initSucceededEps(SUCCEEDED_EPS_COUNT);
    for(int i = 0; i < SUCCEEDED_EPS_COUNT; i++) {
        succeededEps.set(i, i);
    }
    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> role_switch_message() {
    capnp::MallocMessageBuilder builder;
    auto roleSwitch = builder.initRoot<alica_msgs::RoleSwitch>();
    auto senderId = roleSwitch.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    roleSwitch.setRoleId(ROLE_ID);
    roleSwitch.setType(TYPE);
    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> solver_result_message() {
    capnp::MallocMessageBuilder builder;
    auto solverResult = builder.initRoot<alica_msgs::SolverResult>();
    auto senderId = solverResult.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto vars = solverResult.initVars(SOLVER_VAR_COUNT);
    for(auto var: vars) {
        var.setId(SOLVER_VAR_ID);
        auto solverVarReader = var.initValue(SOLVER_VAR_VALUE_SIZE);
        for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
            solverVarReader.set(i, i);
        }
    }

    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> solver_var_message() {
    capnp::MallocMessageBuilder builder;
    auto solverVar = builder.initRoot<alica_msgs::SolverVar>();
    solverVar.setId(SOLVER_VAR_ID);
    auto value = solverVar.initValue(SOLVER_VAR_VALUE_SIZE);
    for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
        value.set(i, i);
    }

    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> sync_ready_message() {
    capnp::MallocMessageBuilder builder;
    auto syncReady = builder.initRoot<alica_msgs::SyncReady>();
    auto senderId = syncReady.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    syncReady.setSynchronisationId(SYNC_ID);

    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> sync_talk_message() {
    capnp::MallocMessageBuilder builder;
    auto syncTalk = builder.initRoot<alica_msgs::SyncTalk>();
    auto senderId = syncTalk.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto syncData = syncTalk.initSyncData(SYNC_DATA_COUNT);
    for(auto entry: syncData) {
        auto robotId = entry.initRobotId();
        robotId.setValue(kj::StringPtr(ID_VALUE).asBytes());
        robotId.setType(ID_TYPE);
        entry.setAck(ACK);
        entry.setTransitionHolds(TRANSITION_HOLDS);
        entry.setTransitionId(TRANSITION_ID);
    }
    return capnp::messageToFlatArray(builder);
}

kj::Array<capnp::word> sync_data_message() {
    capnp::MallocMessageBuilder builder;
    auto syncData = builder.initRoot<alica_msgs::SyncData>();
    auto robotId = syncData.initRobotId();
    robotId.setType(ID_TYPE);
    robotId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    syncData.setTransitionId(TRANSITION_ID);
    syncData.setTransitionHolds(TRANSITION_HOLDS);
    syncData.setAck(ACK);

    return capnp::messageToFlatArray(builder);
}
