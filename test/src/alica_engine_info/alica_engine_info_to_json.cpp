#include <gtest/gtest.h>
#include <conversion.h>
#include <test_values_common.h>
#include <rapidjson/document.h>
#include <serialization/JsonSerializationStrategy.h>

conversion::AlicaEngineInfo alica_engine_info() {
    auto valueString = std::string(ID_VALUE);
    std::vector< conversion::capnzero::Id> agentIdsWithMe;
    agentIdsWithMe.reserve(AGENT_COUNT);
    for(int i = 0; i < AGENT_COUNT; i++) {
        agentIdsWithMe.emplace_back(ID_TYPE, std::vector<uint8_t>(valueString.begin(), valueString.end()));
    }

    std::string idValue {ID_VALUE};
     conversion::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(idValue.begin(), idValue.end()));

    return { senderId, MASTER_PLAN, PLAN, STATE, ROLE, TASK, agentIdsWithMe };
}

TEST(AlicaEngineInfoToJson, it_contains_master_plan ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["masterPlan"].GetString(), MASTER_PLAN);
}

TEST(AlicaEngineInfoToJson, it_contains_current_plan ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentPlan"].GetString(), PLAN);
}

TEST(AlicaEngineInfoToJson, it_contains_current_state ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentState"].GetString(), STATE);
}

TEST(AlicaEngineInfoToJson, it_contains_current_role ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentRole"].GetString(), ROLE);
}

TEST(AlicaEngineInfoToJson, it_contains_current_task ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["currentTask"].GetString(), TASK);
}

TEST(AlicaEngineInfoToJson, it_contains_sender_id ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}


TEST(AlicaEngineInfoToJson, it_contains_additional_agents ) {
    auto alicaEngineInfo = alica_engine_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeAlicaEngineInfo(alicaEngineInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["agentIdsWithMe"].IsArray());
    EXPECT_EQ(doc["agentIdsWithMe"].Size(), AGENT_COUNT);
    for(int i = 0; i < AGENT_COUNT; i++) {
        EXPECT_EQ(doc["agentIdsWithMe"][i]["type"].GetInt(), ID_TYPE);
        EXPECT_EQ(doc["agentIdsWithMe"][i]["value"].GetString(), ID_VALUE);
    }
}