#include <gtest/gtest.h>
#include "../../helper/include/test_values_common.h"
#include <conversion.h>
#include <rapidjson/document.h>

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
    const std::string json = plan_tree_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(PlanTreeInfoToJson, it_contains_sender_id) {
    const std::string json = plan_tree_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(PlanTreeInfoToJson, it_contains_state_ids) {
    const std::string json = plan_tree_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["stateIds"].IsArray());
    EXPECT_EQ(doc["stateIds"].Size(), STATE_ID_COUNT);
}

TEST(PlanTreeInfoToJson, it_contains_succeeded_eps) {
    const std::string json = plan_tree_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["succeededEps"].IsArray());
    EXPECT_EQ(doc["succeededEps"].Size(), SUCCEEDED_EPS_COUNT);
}