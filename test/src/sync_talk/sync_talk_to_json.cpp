#include <gtest/gtest.h>
#include <test_values_common.h>
#include <rapidjson/document.h>

#include <serialization/JsonSerializationStrategy.h>

model::SyncTalk sync_talk() {
     model::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    std::vector<model::SyncData> data;
    data.reserve(SYNC_DATA_COUNT);
    for(int i = 0; i < SYNC_DATA_COUNT; i++) {
         model::capnzero::Id robotId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
        data.emplace_back(robotId, TRANSITION_ID, TRANSITION_HOLDS, ACK);
    }

    return { senderId,data };
}

TEST(SyncTalkToJson, it_is_an_object ) {
    auto syncTalk = sync_talk();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncTalk(syncTalk);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(SyncTalkToJson, it_contains_sender_id ) {
    auto syncTalk = sync_talk();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncTalk(syncTalk);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SyncTalkToJson, it_contains_sync_data ) {
    auto syncTalk = sync_talk();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncTalk(syncTalk);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["syncData"].IsArray());
    EXPECT_EQ(doc["syncData"].Size(), SYNC_DATA_COUNT);
    for(auto& entry: doc["syncData"].GetArray()) {
        EXPECT_TRUE(entry.IsObject());
        EXPECT_TRUE(entry["robotId"].IsObject());
        EXPECT_EQ(entry["robotId"]["type"].GetInt(), ID_TYPE);
        EXPECT_EQ(entry["robotId"]["value"].GetString(), ID_VALUE);
        EXPECT_EQ(entry["transitionId"].GetInt(), TRANSITION_ID);
        EXPECT_EQ(entry["transitionHolds"].GetBool(), TRANSITION_HOLDS);
        EXPECT_EQ(entry["ack"].GetBool(), ACK);
    }
}