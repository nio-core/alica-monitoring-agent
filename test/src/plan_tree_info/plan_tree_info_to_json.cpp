#include <gtest/gtest.h>
#include <test_values_common.h>
#include <conversion.h>
#include <rapidjson/document.h>
#include <serialization/JsonSerializationStrategy.h>

conversion::PlanTreeInfo plan_tree_info() {
     conversion::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    std::vector<int64_t> stateIds;
    stateIds.reserve(STATE_ID_COUNT);
    for(int i = 0; i < STATE_ID_COUNT; i++) {
        stateIds.emplace_back(i);
    }
    std::vector<int64_t> succeededEps;
    succeededEps.reserve(SUCCEEDED_EPS_COUNT);
    for(int i = 0; i < SUCCEEDED_EPS_COUNT; i++) {
        succeededEps.emplace_back(i);
    }

    return { senderId, stateIds, succeededEps };
}

TEST(PlanTreeInfoToJson, it_is_an_object) {
    auto planTreeInfo = plan_tree_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializePlanTreeInfo(planTreeInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(PlanTreeInfoToJson, it_contains_sender_id) {
    auto planTreeInfo = plan_tree_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializePlanTreeInfo(planTreeInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(PlanTreeInfoToJson, it_contains_state_ids) {
    auto planTreeInfo = plan_tree_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializePlanTreeInfo(planTreeInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["stateIds"].IsArray());
    EXPECT_EQ(doc["stateIds"].Size(), STATE_ID_COUNT);
}

TEST(PlanTreeInfoToJson, it_contains_succeeded_eps) {
    auto planTreeInfo = plan_tree_info();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializePlanTreeInfo(planTreeInfo);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["succeededEps"].IsArray());
    EXPECT_EQ(doc["succeededEps"].Size(), SUCCEEDED_EPS_COUNT);
}