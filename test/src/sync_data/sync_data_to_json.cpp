#include <gtest/gtest.h>
#include <rapidjson/document.h>

#include <test_values_common.h>
#include <serialization/JsonSerializationStrategy.h>

model::SyncData sync_data() {
     model::capnzero::Id robotId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    return { robotId, TRANSITION_ID, TRANSITION_HOLDS, ACK };
}

TEST(SyncDataToJson, it_is_an_object)
{
    auto syncData = sync_data();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncData(syncData);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(SyncDataToJson, it_contains_the_robot_id)
{
    auto syncData = sync_data();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncData(syncData);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["robotId"].IsObject());
    EXPECT_EQ(doc["robotId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["robotId"]["value"].GetString(), ID_VALUE);
}

TEST(SyncDataToJson, it_contains_the_transition_id)
{
    auto syncData = sync_data();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncData(syncData);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["transitionId"].GetInt64(), TRANSITION_ID);
}

TEST(SyncDataToJson, it_contains_the_transition_hold_status)
{
    auto syncData = sync_data();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncData(syncData);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["transitionHolds"].GetBool(), TRANSITION_HOLDS);
}

TEST(SyncDataToJson, it_contains_the_acknowledgement_status)
{
    auto syncData = sync_data();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncData(syncData);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["ack"].GetBool(), ACK);
}