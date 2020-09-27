#include <gtest/gtest.h>
#include <rapidjson/document.h>
#include <conversion.h>
#include "../../helper/include/test_values_common.h"

conversion::AllocationAuthorityInfo allocation_authority_info() {
    conversion::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    conversion::capnzero::Id authority(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    std::vector<conversion::EntrypointRobots> entrypointRobots;
    entrypointRobots.reserve(ENTRY_POINT_COUNT);
    for(int i = 0; i < ENTRY_POINT_COUNT; i++) {
        std::vector<conversion::capnzero::Id> robots;
        robots.reserve(ROBOT_COUNT);
        for(int j = 0; j < ROBOT_COUNT; j++) {
            robots.emplace_back(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
        }
        entrypointRobots.emplace_back(ENTRY_POINT, robots);
    }

    return {senderId, PLAN_ID, PARENT_STATE, PLAN_TYPE, authority, entrypointRobots };
}

TEST(AllocationAuthorityInfoToJson, it_is_an_object) {
    const std::string json = allocation_authority_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(AllocationAuthorityInfoToJson, it_contains_parent_state) {
    const std::string json = allocation_authority_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["parentState"].GetInt(), PARENT_STATE);
}

TEST(AllocationAuthorityInfoToJson, it_contains_plan_type) {
    const std::string json = allocation_authority_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["planType"].GetInt(), PLAN_TYPE);
}

TEST(AllocationAuthorityInfoToJson, it_contains_plan_id) {
    const std::string json = allocation_authority_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["planId"].GetInt(), PLAN_ID);
}

TEST(AllocationAuthorityInfoToJson, it_contains_authority) {
    const std::string json = allocation_authority_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["authority"].IsObject());
    EXPECT_EQ(doc["authority"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["authority"]["value"].GetString(), ID_VALUE);
}

TEST(AllocationAuthorityInfoToJson, it_contains_sender_id) {
    const std::string json = allocation_authority_info().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(AllocationAuthorityInfoToJson, it_contains_entry_point_robots) {
    const std::string json = allocation_authority_info().toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["entrypointRobots"].IsArray());
    EXPECT_EQ(doc["entrypointRobots"].Size(), ENTRY_POINT_COUNT);
    for(int i = 0; i < ENTRY_POINT_COUNT; i++) {
        EXPECT_EQ(doc["entrypointRobots"][i]["entrypoint"].GetInt(), ENTRY_POINT);
        EXPECT_TRUE(doc["entrypointRobots"][i]["robots"].IsArray());
        EXPECT_EQ(doc["entrypointRobots"][i]["robots"].Size(), ROBOT_COUNT);
        for(int j = 0; j < ROBOT_COUNT; j++) {
            EXPECT_EQ(doc["entrypointRobots"][i]["robots"][j]["type"].GetInt(), ID_TYPE);
            EXPECT_EQ(doc["entrypointRobots"][i]["robots"][j]["value"].GetString(), ID_VALUE);
        }
    }
}