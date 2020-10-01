#include <gtest/gtest.h>
#include <test_values_common.h>
#include <rapidjson/document.h>
#include <conversion.h>

conversion::SyncReady sync_ready() {
     conversion::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    return { senderId, SYNC_ID };
}

TEST(SyncReadyToJson, it_is_an_object) {
    const std::string json = sync_ready().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(SyncReadyToJson, it_contains_sender_id) {
    const std::string json = sync_ready().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SyncReadyToJson, it_contains_sync_id) {
    const std::string json = sync_ready().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["synchronisationId"].GetInt(), SYNC_ID);
}