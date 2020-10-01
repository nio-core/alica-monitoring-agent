#include <gtest/gtest.h>
#include <test_messages_common.h>
#include <handler.h>
#include <serialization/JsonSerializationStrategy.h>

CapnprotoMessageHandler* handler(SerializationStrategy* serializationStrategy) {
    auto alicaEngineInfoHandler = new AlicaEngineInfoHandler(serializationStrategy);
    auto allocationAuthorityInfoHandler = new AllocationAuthorityInfoHandler(serializationStrategy);
    auto planTreeInfoHandler = new PlanTreeInfoHandler(serializationStrategy);
    auto solverResultHandler = new SolverResultHandler(serializationStrategy);
    auto syncTalkHandler = new SyncTalkHandler(serializationStrategy);
    auto roleSwitchHandler = new RoleSwitchHandler(serializationStrategy);
    auto syncReadyHandler = new SyncReadyHandler(serializationStrategy);

    alicaEngineInfoHandler->chain(allocationAuthorityInfoHandler)
                          ->chain(planTreeInfoHandler)
                          ->chain(solverResultHandler)
                          ->chain(syncTalkHandler)
                          ->chain(roleSwitchHandler)
                          ->chain(syncReadyHandler);

    return alicaEngineInfoHandler;
}

TEST(FullChainTest, it_emits_allocation_authority_information_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}

TEST(FullChainTest, it_emits_alica_engine_information_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}

TEST(FullChainTest, it_emits_plan_tree_info_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}

TEST(FullChainTest, it_emits_role_switch_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}

TEST(FullChainTest, it_emits_solver_result_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}

TEST(FullChainTest, it_emits_sync_ready_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}

TEST(FullChainTest, it_emits_sync_talk_json) {
    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler(serializationStrategy);
    messageHandler->handle(reader);

    delete messageHandler;
    delete serializationStrategy;
}
