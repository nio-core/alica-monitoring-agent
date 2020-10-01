#include <gtest/gtest.h>
#include <test_messages_common.h>
#include <handler.h>

CapnprotoMessageHandler* handler() {
    auto alicaEngineInfoHandler = new AlicaEngineInfoHandler();
    auto allocationAuthorityInfoHandler = new AllocationAuthorityInfoHandler();
    auto planTreeInfoHandler = new PlanTreeInfoHandler();
    auto solverResultHandler = new SolverResultHandler();
    auto syncTalkHandler = new SyncTalkHandler();
    auto roleSwitchHandler = new RoleSwitchHandler();
    auto syncReadyHandler = new SyncReadyHandler();

    alicaEngineInfoHandler->chain(allocationAuthorityInfoHandler)
                          ->chain(planTreeInfoHandler)
                          ->chain(solverResultHandler)
                          ->chain(syncTalkHandler)
                          ->chain(roleSwitchHandler)
                          ->chain(syncReadyHandler);

    return alicaEngineInfoHandler;
}

TEST(FullChainTest, it_emits_allocation_authority_information_json) {
    auto message = allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}

TEST(FullChainTest, it_emits_alica_engine_information_json) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}

TEST(FullChainTest, it_emits_plan_tree_info_json) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}

TEST(FullChainTest, it_emits_role_switch_json) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}

TEST(FullChainTest, it_emits_solver_result_json) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}

TEST(FullChainTest, it_emits_sync_ready_json) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}

TEST(FullChainTest, it_emits_sync_talk_json) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto messageHandler = handler();
    messageHandler->handle(reader);

    delete messageHandler;
}
