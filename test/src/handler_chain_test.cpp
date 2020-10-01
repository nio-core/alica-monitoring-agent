#include <gtest/gtest.h>
#include <test_messages_common.h>
#include <serialization/JsonSerializationStrategy.h>
#include <handler/CapnprotoMessageHandler.h>
#include <handler/AlicaEngineInfoHandler.h>
#include <handler/AllocationAuthorityInfoHandler.h>
#include <handler/PlanTreeInfoHandler.h>
#include <handler/SolverResultHandler.h>
#include <handler/SyncTalkHandler.h>
#include <handler/RoleSwitchHandler.h>
#include <handler/SyncReadyHandler.h>
#include <mocks.h>

CapnprotoMessageHandler* handler(SerializationStrategy* serializationStrategy, StorageStrategy* storageStrategy) {
    auto alicaEngineInfoHandler = new AlicaEngineInfoHandler(serializationStrategy, storageStrategy);
    auto allocationAuthorityInfoHandler = new AllocationAuthorityInfoHandler(serializationStrategy, storageStrategy);
    auto planTreeInfoHandler = new PlanTreeInfoHandler(serializationStrategy, storageStrategy);
    auto solverResultHandler = new SolverResultHandler(serializationStrategy, storageStrategy);
    auto syncTalkHandler = new SyncTalkHandler(serializationStrategy, storageStrategy);
    auto roleSwitchHandler = new RoleSwitchHandler(serializationStrategy, storageStrategy);
    auto syncReadyHandler = new SyncReadyHandler(serializationStrategy, storageStrategy);

    alicaEngineInfoHandler->chain(allocationAuthorityInfoHandler)
                          ->chain(planTreeInfoHandler)
                          ->chain(solverResultHandler)
                          ->chain(syncTalkHandler)
                          ->chain(roleSwitchHandler)
                          ->chain(syncReadyHandler);

    return alicaEngineInfoHandler;
}

TEST(FullChainTest, it_emits_allocation_authority_information_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("ALLOCATION_AUTHORITY_INFO"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeAllocationAuthorityInfo(testing::An<model::AllocationAuthorityInfo&>()));

    auto message = allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}

TEST(FullChainTest, it_emits_alica_engine_information_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("ALICA_ENGINE_INFO"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeAlicaEngineInfo(testing::An<model::AlicaEngineInfo&>()));
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}

TEST(FullChainTest, it_emits_plan_tree_info_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("PLAN_TREE_INFO"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializePlanTreeInfo(testing::An<model::PlanTreeInfo&>()));
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}

TEST(FullChainTest, it_emits_role_switch_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("ROLE_SWITCH"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeRoleSwitch(testing::An<model::RoleSwitch&>()));
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}

TEST(FullChainTest, it_emits_solver_result_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("SOLVER_RESULT"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSolverResult(testing::An<model::SolverResult&>()));
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}

TEST(FullChainTest, it_emits_sync_ready_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("SYNC_READY"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSyncReady(testing::An<model::SyncReady&>()));
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}

TEST(FullChainTest, it_emits_sync_talk_json) {
    auto storageStrategy = new MockStorageStrategy();
    EXPECT_CALL(*storageStrategy, store(testing::An<const model::capnzero::Id&>(),
            testing::StrEq("SYNC_TALK"), testing::An<const std::string&>()));
    auto serializationStrategy = new MockSerializationStrategy();
    EXPECT_CALL(*serializationStrategy, serializeSyncTalk(testing::An<model::SyncTalk&>()));
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy, storageStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
    delete storageStrategy;
}
