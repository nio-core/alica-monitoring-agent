#include <gtest/gtest.h>
#include <AlicaEngineInfo.capnp.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <rapidjson/document.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <test_values_common.h>

auto MASTER_PLAN = "MASTER_PLAN";
auto PLAN = "PLAN";
auto STATE = "STATE";
auto ROLE = "ROLE";
auto TASK = "TASK";
auto AGENT_COUNT = 3;

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

TEST(AlicaEngineInfoCapnprotoToJson, it_can_be_parsed) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::try_read_alica_engine_info(reader));
}

TEST(AlicaEngineInfoCapnprotoToJson, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::try_read_alica_engine_info(reader), std::runtime_error);
}

TEST(AlicaEngineInfoCapnprotoToJson, other_messages_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::try_read_alica_engine_info(reader), std::runtime_error);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_master_plan ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["masterPlan"].GetString(), MASTER_PLAN);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_plan ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentPlan"].GetString(), PLAN);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_state ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentState"].GetString(), STATE);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_role ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentRole"].GetString(), ROLE);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_task ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentTask"].GetString(), TASK);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_sender_id ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);


    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_STREQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}


TEST(AlicaEngineInfoCapnprotoToJson, it_contains_additional_agents ) {
    auto message = alica_engine_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["agentsWithMe"].IsArray());
    EXPECT_EQ(doc["agentsWithMe"].Size(), AGENT_COUNT);
    for(int i = 0; i < AGENT_COUNT; i++) {
        EXPECT_EQ(doc["agentsWithMe"][i]["type"].GetInt(), ID_TYPE);
        EXPECT_STREQ(doc["agentsWithMe"][i]["value"].GetString(), ID_VALUE);
    }
}