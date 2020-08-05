#include <gtest/gtest.h>
#include <model/AlicaEngineInfo.h>
#include <model/capnzero/Id.h>
#include <test_values_common.h>
#include <rapidjson/document.h>

AlicaEngineInfo alica_engine_info() {
    auto valueString = std::string(ID_VALUE);
    std::vector<capnzero::Id> agentIdsWithMe;
    agentIdsWithMe.reserve(AGENT_COUNT);
    for(int i = 0; i < AGENT_COUNT; i++) {
        agentIdsWithMe.emplace_back(ID_TYPE, std::vector<uint8_t>(valueString.begin(), valueString.end()));
    }

    std::string idValue {ID_VALUE};
    capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(idValue.begin(), idValue.end()));

    return AlicaEngineInfo(senderId, MASTER_PLAN, PLAN, STATE, ROLE, TASK, agentIdsWithMe);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_master_plan ) {
    const std::string json = alica_engine_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["masterPlan"].GetString(), MASTER_PLAN);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_plan ) {
    const std::string json = alica_engine_info().toJson();;
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentPlan"].GetString(), PLAN);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_state ) {
    const std::string json = alica_engine_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentState"].GetString(), STATE);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_role ) {
    const std::string json = alica_engine_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentRole"].GetString(), ROLE);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_current_task ) {
    const std::string json = alica_engine_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentTask"].GetString(), TASK);
}

TEST(AlicaEngineInfoCapnprotoToJson, it_contains_sender_id ) {
    const std::string json = alica_engine_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_STREQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}


TEST(AlicaEngineInfoCapnprotoToJson, it_contains_additional_agents ) {
    const std::string json = alica_engine_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["agentIdsWithMe"].IsArray());
    EXPECT_EQ(doc["agentIdsWithMe"].Size(), AGENT_COUNT);
    for(int i = 0; i < AGENT_COUNT; i++) {
        EXPECT_EQ(doc["agentIdsWithMe"][i]["type"].GetInt(), ID_TYPE);
        EXPECT_STREQ(doc["agentIdsWithMe"][i]["value"].GetString(), ID_VALUE);
    }
}