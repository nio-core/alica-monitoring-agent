#include <gtest/gtest.h>
#include <AlicaEngineInfo.capnp.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <rapidjson/document.h>

TEST(CapnprotoToJson, alica_engine_info_can_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::try_read_alica_engine_info(reader));
}

TEST(CapnprotoToJson, alica_engine_info_contains_master_plan ) {
    auto masterPlan = "MASTER_PLAN";

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    engineInfo.setMasterPlan(masterPlan);
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["masterPlan"].GetString(), masterPlan);
}

TEST(CapnprotoToJson, alica_engine_info_contains_current_plan ) {
    auto plan = "PLAN";

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    engineInfo.setCurrentPlan(plan);
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentPlan"].GetString(), plan);
}

TEST(CapnprotoToJson, alica_engine_info_contains_current_state ) {
    auto state = "STATE";

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    engineInfo.setCurrentState(state);
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentState"].GetString(), state);
}

TEST(CapnprotoToJson, alica_engine_info_contains_current_role ) {
    auto role = "ROLE";

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    engineInfo.setCurrentRole(role);
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentRole"].GetString(), role);
}

TEST(CapnprotoToJson, alica_engine_info_contains_current_task ) {
    auto task = "TASK";

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    engineInfo.setCurrentTask(task);
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_STREQ(doc["currentTask"].GetString(), task);
}

TEST(CapnprotoToJson, alica_engine_info_contains_sender_id ) {
    auto type = 1;
    auto value = "id";

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto senderId = engineInfo.initSenderId();
    senderId.setType(type);
    senderId.setValue(kj::StringPtr(value).asBytes());
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), type);
    EXPECT_STREQ(doc["senderId"]["value"].GetString(), value);
}


TEST(CapnprotoToJson, alica_engine_info_contains_additional_agents ) {
    auto type = 1;
    auto value = "id";
    auto agentCount = 3;

    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto agentsWithMe = engineInfo.initAgentIdsWithMe(agentCount);
    for(int i = 0; i < agentCount; i++) {
        agentsWithMe[i].setType(type);
        agentsWithMe[i].setValue(kj::StringPtr(value).asBytes());
    }
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_alica_engine_info(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["agentsWithMe"].IsArray());
    EXPECT_EQ(doc["agentsWithMe"].Size(), 3);
    for(int i = 0; i < agentCount; i++) {
        EXPECT_EQ(doc["agentsWithMe"][i]["type"].GetInt(), type);
        EXPECT_STREQ(doc["agentsWithMe"][i]["value"].GetString(), value);
    }
}