#include <gtest/gtest.h>
#include <AlicaEngineInfo.capnp.h>
#include <capnp/serialize.h>
#include <rapidjson/document.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <test_values_common.h>

#include <test_messages_common.h>
#include <model/AlicaEngineInfo.h>


TEST(AlicaEngineInfoFromCapnp, it_can_be_parsed_if_valid) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(model::AlicaEngineInfo::from(reader));
}

TEST(AlicaEngineInfoFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(model::AlicaEngineInfo::from(reader), std::runtime_error);
}

TEST(AlicaEngineInfoFromCapnp, other_messages_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(model::AlicaEngineInfo::from(reader), std::runtime_error);
}

TEST(AlicaEngineInfoFromCapnp, sender_id_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);
    auto senderId = engineInfo.getSenderId();

    EXPECT_EQ(senderId.getType(), ID_TYPE);
    EXPECT_EQ(senderId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(AlicaEngineInfoFromCapnp, master_plan_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getMasterPlan(), MASTER_PLAN);
}

TEST(AlicaEngineInfoFromCapnp, current_plan_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentPlan(), PLAN);
}

TEST(AlicaEngineInfoFromCapnp, current_state_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentState(), STATE);
}

TEST(AlicaEngineInfoFromCapnp, current_role_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentRole(), ROLE);
}

TEST(AlicaEngineInfoFromCapnp, current_task_is_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);

    EXPECT_EQ(engineInfo.getCurrentTask(), TASK);
}

TEST(AlicaEngineInfoFromCapnp, agent_ids_with_me_are_set_correctly) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto engineInfo = model::AlicaEngineInfo::from(reader);

    auto agentIdsWithMe = engineInfo.getAgentIdsWithMe();
    EXPECT_EQ(agentIdsWithMe.size(), AGENT_COUNT);
    for(auto agent: agentIdsWithMe) {
        EXPECT_EQ(agent.getType(), ID_TYPE);
        auto agentValue = agent.getValue();
        EXPECT_EQ(std::string(agentValue.begin(), agentValue.end()), ID_VALUE);
    }
}