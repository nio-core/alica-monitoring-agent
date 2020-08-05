#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <SyncTalk.capnp.h>
#include <test_values_common.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <rapidjson/document.h>

auto TRANSITION_ID = 1;
auto SYNC_DATA_COUNT = 3;
auto TRANSITION_HOLDS = true;
auto ACK = true;

kj::Array<capnp::word> sync_talk_message() {
    capnp::MallocMessageBuilder builder;
    auto syncTalk = builder.initRoot<alica_msgs::SyncTalk>();
    auto senderId = syncTalk.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto syncData = syncTalk.initSyncData(SYNC_DATA_COUNT);
    for(auto entry: syncData) {
        auto robotId = entry.initRobotId();
        robotId.setValue(kj::StringPtr(ID_VALUE).asBytes());
        robotId.setType(ID_TYPE);
        entry.setAck(ACK);
        entry.setTransitionHolds(TRANSITION_HOLDS);
        entry.setTransitionId(TRANSITION_ID);
    }
    return capnp::messageToFlatArray(builder);
}

TEST(SyncTalkCapnprotoToJson, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncTalk>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::sync_ready_capnproto_to_json(reader), std::runtime_error);
}

TEST(SyncTalkCapnprotoToJson, it_can_be_parsed) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::sync_ready_capnproto_to_json(reader));
}

TEST(SyncTalkCapnprotoToJson, it_contains_sender_id ) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::sync_talk_capnproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SyncTalkCapnprotoToJson, it_contains_sync_data ) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::sync_talk_capnproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
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