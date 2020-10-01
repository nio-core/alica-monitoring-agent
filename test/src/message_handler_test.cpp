#include <gtest/gtest.h>
#include <test_messages_common.h>
#include <serialization/JsonSerializationStrategy.h>
#include <handler/AllocationAuthorityInfoHandler.h>
#include <handler/AlicaEngineInfoHandler.h>
#include <handler/PlanTreeInfoHandler.h>
#include <handler/RoleSwitchHandler.h>
#include <handler/SolverResultHandler.h>
#include <handler/SyncReadyHandler.h>
#include <handler/SyncTalkHandler.h>
#include <mocks.h>


TEST(HandlingAllocationAuthorityInformation, it_emits_allocation_authority_information_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeAllocationAuthorityInfo(testing::An<model::AllocationAuthorityInfo&>()));
    AllocationAuthorityInfoHandler handler(serializationStrategy);

    auto message = allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

TEST(HandlingEngineInformation, it_emits_alica_engine_information_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeAlicaEngineInfo(testing::An<model::AlicaEngineInfo&>()));
    AlicaEngineInfoHandler handler(serializationStrategy);

    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

TEST(HandlingPlanTreeInfo, it_emits_plan_tree_info_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializePlanTreeInfo(testing::An<model::PlanTreeInfo&>()));
    PlanTreeInfoHandler handler(serializationStrategy);

    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

TEST(HandlingRoleSwitch, it_emits_role_switch_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeRoleSwitch(testing::An<model::RoleSwitch&>()));
    RoleSwitchHandler handler(serializationStrategy);

    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

TEST(HandlingSolverResult, it_emits_solver_result_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSolverResult(testing::An<model::SolverResult&>()));
    SolverResultHandler handler(serializationStrategy);

    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

TEST(HandlingSyncReady, it_emits_sync_ready_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSyncReady(testing::An<model::SyncReady&>()));
    SyncReadyHandler handler(serializationStrategy);

    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

TEST(HandlingSyncTalk, it_emits_sync_talk_json) {
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSyncTalk(testing::An<model::SyncTalk&>()));
    SyncTalkHandler handler(serializationStrategy);

    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
}

