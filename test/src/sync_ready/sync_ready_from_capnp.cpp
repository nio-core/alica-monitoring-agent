#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <SyncReady.capnp.h>
#include <test_values_common.h>
#include <capnp/serialize.h>
#include <rapidjson/document.h>
#include <SyncTalk.capnp.h>
#include <conversion.h>

kj::Array<capnp::word> sync_ready_message() {
    capnp::MallocMessageBuilder builder;
    auto syncReady = builder.initRoot<alica_msgs::SyncReady>();
    auto senderId = syncReady.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    syncReady.setSynchronisationId(SYNC_ID);

    return capnp::messageToFlatArray(builder);
}

TEST(SyncReadyFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncReady>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(SyncReady::from(reader), std::runtime_error);
}

TEST(SyncReadyFromCapnp, it_can_not_parse_other_messages) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncTalk>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(SyncReady::from(reader), std::runtime_error);
}

TEST(SyncReadyFromCapnp, it_can_be_parsed) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(SyncReady::from(reader));
}

TEST(SyncReadyFromCapnp, it_contains_the_sender_id) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto syncReady = SyncReady::from(reader);
    auto senderId = syncReady.getSenderId();

    EXPECT_EQ(senderId.getType(), ID_TYPE);
    EXPECT_EQ(senderId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(SyncReadyFromCapnp, it_contains_the_sync_id) {
    auto message = sync_ready_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto syncReady = SyncReady::from(reader);

    EXPECT_EQ(syncReady.getSyncId(), SYNC_ID);
}