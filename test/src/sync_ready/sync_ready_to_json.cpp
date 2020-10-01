#include <gtest/gtest.h>
#include <test_values_common.h>
#include <rapidjson/document.h>

#include <serialization/JsonSerializationStrategy.h>

model::SyncReady sync_ready() {
     model::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    return { senderId, SYNC_ID };
}

TEST(SyncReadyToJson, it_is_an_object) {
    auto syncReady = sync_ready();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncReady(syncReady);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(SyncReadyToJson, it_contains_sender_id) {
    auto syncReady = sync_ready();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncReady(syncReady);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SyncReadyToJson, it_contains_sync_id) {
    auto syncReady = sync_ready();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSyncReady(syncReady);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["synchronisationId"].GetInt(), SYNC_ID);
}