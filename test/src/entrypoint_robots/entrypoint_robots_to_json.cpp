#include <gtest/gtest.h>
#include <rapidjson/document.h>
#include <conversion.h>
#include <test_values_common.h>
#include <serialization/JsonSerializationStrategy.h>

conversion::EntrypointRobots entrypoint_robots() {
    std::vector< conversion::capnzero::Id> robots;
    robots.reserve(ROBOT_COUNT);
    for(int i = 0; i < ROBOT_COUNT; i++) {
        robots.emplace_back(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    }
    return { ENTRY_POINT, robots };
}

TEST(EntrypointRobotsToJson, it_creates_an_object) {
    auto entrypointRobots = entrypoint_robots();
    JsonSerializationStrategy serializationStrategy;
    std::string json = serializationStrategy.serializeEntryPointRobots(entrypointRobots);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(EntrypointRobotsToJson, it_contains_the_entrypoint) {
    auto entrypointRobots = entrypoint_robots();
    JsonSerializationStrategy serializationStrategy;
    std::string json = serializationStrategy.serializeEntryPointRobots(entrypointRobots);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["entrypoint"].GetInt(), ENTRY_POINT);
}

TEST(EntrypointRobotsToJson, it_contains_the_robots) {
    auto entrypointRobots = entrypoint_robots();
    JsonSerializationStrategy serializationStrategy;
    std::string json = serializationStrategy.serializeEntryPointRobots(entrypointRobots);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["robots"].IsArray());
    EXPECT_EQ(doc["robots"].Size(), ROBOT_COUNT);
    for(int i = 0; i < ROBOT_COUNT; i++) {
        EXPECT_EQ(doc["robots"][i]["type"].GetUint(), ID_TYPE);
        EXPECT_EQ(doc["robots"][i]["value"].GetString(), ID_VALUE);
    }
}