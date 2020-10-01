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


TEST(HandlingAllocationAuthorityInformation, it_handles_allocation_authority_info_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("ALLOCATION_AUTHORITY_INFO"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeAllocationAuthorityInfo(testing::An<model::AllocationAuthorityInfo&>()));
    AllocationAuthorityInfoHandler handler(serializationStrategy, storageStrategy);

    auto message = allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

TEST(HandlingEngineInformation, it_handles_alica_engine_info_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("ALICA_ENGINE_INFO"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeAlicaEngineInfo(testing::An<model::AlicaEngineInfo&>()));
    AlicaEngineInfoHandler handler(serializationStrategy, storageStrategy);

    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

TEST(HandlingPlanTreeInfo, it_handles_plan_tree_info_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("PLAN_TREE_INFO"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializePlanTreeInfo(testing::An<model::PlanTreeInfo&>()));
    PlanTreeInfoHandler handler(serializationStrategy, storageStrategy);

    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

TEST(HandlingRoleSwitch, it_handles_role_switch_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("ROLE_SWITCH"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeRoleSwitch(testing::An<model::RoleSwitch&>()));
    RoleSwitchHandler handler(serializationStrategy, storageStrategy);

    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

TEST(HandlingSolverResult, it_handles_solver_result_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("SOLVER_RESULT"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSolverResult(testing::An<model::SolverResult&>()));
    SolverResultHandler handler(serializationStrategy, storageStrategy);

    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

TEST(HandlingSyncReady, it_handles_sync_ready_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("SYNC_READY"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSyncReady(testing::An<model::SyncReady&>()));
    SyncReadyHandler handler(serializationStrategy, storageStrategy);

    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

TEST(HandlingSyncTalk, it_handles_sync_talk_messages) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("SYNC_TALK"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSyncTalk(testing::An<model::SyncTalk&>()));
    SyncTalkHandler handler(serializationStrategy, storageStrategy);

    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);

    delete serializationStrategy;
    delete storageStrategy;
}

