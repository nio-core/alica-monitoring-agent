#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <SyncReady.capnp.h>
#include <test_values_common.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <rapidjson/document.h>

auto SYNC_ID = 1;

kj::Array<capnp::word> sync_ready_message() {
    capnp::MallocMessageBuilder builder;
    auto syncReady = builder.initRoot<alica_msgs::SyncReady>();
    auto senderId = syncReady.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    syncReady.setSynchronisationId(SYNC_ID);

    return capnp::messageToFlatArray(builder);
}

TEST(SyncReadyCapnprotoToJson, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncReady>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::sync_ready_capnproto_to_json(reader), std::runtime_error);
}

TEST(SyncReadyCapnprotoToJson, it_can_be_parsed) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::sync_ready_capnproto_to_json(reader));
}

TEST(SyncReadyCapnprotoToJson, it_contains_sender_id) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::sync_ready_capnproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SyncReadyCapnprotoToJson, it_contains_sync_id) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::sync_ready_capnproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_EQ(doc["synchronisationId"].GetInt(), SYNC_ID);
}