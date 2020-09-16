#include <gtest/gtest.h>
#include <test_messages_common.h>
#include <handler.h>


TEST(HandlingAllocationAuthorityInformation, it_emits_allocation_authority_information_json) {
    AllocationAuthorityInfoHandler handler(nullptr);

    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

TEST(HandlingEngineInformation, it_emits_alica_engine_information_json) {
    AlicaEngineInfoHandler handler(nullptr);

    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

TEST(HandlingPlanTreeInfo, it_emits_plan_tree_info_json) {
    PlanTreeInfoHandler handler(nullptr);

    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

TEST(HandlingRoleSwitch, it_emits_role_switch_json) {
    RoleSwitchHandler handler(nullptr);

    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

TEST(HandlingSolverResult, it_emits_solver_result_json) {
    SolverResultHandler handler(nullptr);

    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

TEST(HandlingSyncReady, it_emits_sync_ready_json) {
    SyncReadyHandler handler(nullptr);

    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

TEST(HandlingSyncTalk, it_emits_sync_talk_json) {
    SyncTalkHandler handler(nullptr);

    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    handler.handle(reader);
}

