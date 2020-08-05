#include <gtest/gtest.h>
#include <AlicaEngineInfo.capnp.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <rapidjson/document.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <test_values_common.h>
#include <model/AlicaEngineInfo.h>

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

TEST(AlicaEngineInfoFromCapnp, it_can_be_parsed_if_valid) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(AlicaEngineInfo::from(reader));
}

TEST(AlicaEngineInfoFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(AlicaEngineInfo::from(reader), std::runtime_error);
}

TEST(AlicaEngineInfoFromCapnp, other_messages_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(AlicaEngineInfo::from(reader), std::runtime_error);
}

TEST(AlicaEngineInfoFromCapnp, sender_id_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);
    auto senderIdType = engineInfo.getSenderId().getType();
    auto senderIdValue = engineInfo.getSenderId().getValue();

    EXPECT_EQ(senderIdType, ID_TYPE);
    EXPECT_EQ(std::string(senderIdValue.begin(), senderIdValue.end()), ID_VALUE);
}

TEST(AlicaEngineInfoFromCapnp, master_plan_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getMasterPlan(), MASTER_PLAN);
}

TEST(AlicaEngineInfoFromCapnp, current_plan_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentPlan(), PLAN);
}

TEST(AlicaEngineInfoFromCapnp, current_state_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentState(), STATE);
}

TEST(AlicaEngineInfoFromCapnp, current_role_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentRole(), ROLE);
}

TEST(AlicaEngineInfoFromCapnp, current_task_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentTask(), TASK);
}

TEST(AlicaEngineInfoFromCapnp, agent_ids_with_me_are_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = AlicaEngineInfo::from(reader);

    auto agentIdsWithMe = engineInfo.getAgentIdsWithMe();
    EXPECT_EQ(agentIdsWithMe.size(), AGENT_COUNT);
    for(auto agent: agentIdsWithMe) {
        EXPECT_EQ(agent.getType(), ID_TYPE);
        auto agentValue = agent.getValue();
        EXPECT_EQ(std::string(agentValue.begin(), agentValue.end()), ID_VALUE);
    }
}