#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <SyncTalk.capnp.h>
#include <test_values_common.h>
#include <capnp/serialize.h>
#include <rapidjson/document.h>
#include <conversion.h>
#include <test_messages_common.h>


TEST(SyncTalkFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncTalk>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(SyncTalk::from(reader), std::runtime_error);
}

TEST(SyncTalkFromCapnp, it_can_not_parse_other_messages) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncData>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(SyncTalk::from(reader), std::runtime_error);
}

TEST(SyncTalkFromCapnp, it_can_be_parsed) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(SyncTalk::from(reader));
}

TEST(SyncTalkFromCapnp, it_contains_the_sender_id) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto syncTalk = SyncTalk::from(reader);
    auto senderId = syncTalk.getSenderId();

    EXPECT_EQ(senderId.getType(), ID_TYPE);
    EXPECT_EQ(senderId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(SyncTalkFromCapnp, it_contains_the_syn_data) {
    auto message = sync_talk_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto syncTalk = SyncTalk::from(reader);
    auto syncData = syncTalk.getSyncData();

    EXPECT_EQ(syncData.size(), SYNC_DATA_COUNT);
    for(const auto& data: syncData) {
        auto robotId = data.getRobotId();
        EXPECT_EQ(robotId.getType(), ID_TYPE);
        EXPECT_EQ(robotId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
        EXPECT_EQ(data.getTransitionId(), TRANSITION_ID);
        EXPECT_EQ(data.transition_holds(), TRANSITION_HOLDS);
        EXPECT_EQ(data.ack(), ACK);
    }
}

