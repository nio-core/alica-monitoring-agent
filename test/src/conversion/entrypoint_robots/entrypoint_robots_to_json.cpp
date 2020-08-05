#include <gtest/gtest.h>
#include <rapidjson/document.h>
#include <model/EntrypointRobots.h>
#include <test_values_common.h>

EntrypointRobots entrypoint_robots() {
    std::vector<capnzero::Id> robots;
    for(int i = 0; i < ROBOT_COUNT; i++) {
        robots.emplace_back(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    }
    return EntrypointRobots(ENTRY_POINT, robots);
}

TEST(EntrypointRobotsToJson, it_creates_an_object) {
    std::string json = entrypoint_robots().toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(EntrypointRobotsToJson, it_contains_the_entrypoint) {
    std::string json = entrypoint_robots().toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["entrypoint"].GetInt(), ENTRY_POINT);
}

TEST(EntrypointRobotsToJson, it_contains_the_robots) {
    std::string json = entrypoint_robots().toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["robots"].IsArray());
    EXPECT_EQ(doc["robots"].Size(), ROBOT_COUNT);
    for(int i = 0; i < ROBOT_COUNT; i++) {
        EXPECT_EQ(doc["robots"][i]["type"].GetInt(), ID_TYPE);
        EXPECT_EQ(doc["robots"][i]["value"].GetString(), ID_VALUE);
    }
}