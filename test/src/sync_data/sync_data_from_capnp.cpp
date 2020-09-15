#include <gtest/gtest.h>
#include <capnp/message.h>
#include <SyncTalk.capnp.h>
#include <test_values_common.h>
#include <capnp/serialize.h>
#include <conversion.h>
#include <test_messages_common.h>


TEST(SyncDataFromCapnp, it_can_be_parsed) {
    auto message = sync_data_message();
    capnp::FlatArrayMessageReader reader(message);

    EXPECT_NO_THROW(SyncData::from(reader));
}

TEST(SyncDataFromCapnp, it_can_not_be_parsed_if_robot_id_is_missing) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncData>();
    auto message = capnp::messageToFlatArray(builder);
    capnp::FlatArrayMessageReader reader(message);

    EXPECT_THROW(SyncData::from(reader), std::runtime_error);
}

TEST(SyncDataFromCapnp, it_can_not_parse_other_message) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SyncTalk>();
    auto message = capnp::messageToFlatArray(builder);
    capnp::FlatArrayMessageReader reader(message);

    EXPECT_THROW(SyncData::from(reader), std::runtime_error);
}

TEST(SyncDataFromCapnp, it_contains_the_robot_id) {
    auto message = sync_data_message();
    capnp::FlatArrayMessageReader reader(message);

    auto syncData = SyncData::from(reader);
    auto robotId = syncData.getRobotId();

    EXPECT_EQ(robotId.getType(), ID_TYPE);
    EXPECT_EQ(robotId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(SyncDataFromCapnp, it_contains_the_transition_id) {
    auto message = sync_data_message();
    capnp::FlatArrayMessageReader reader(message);

    auto syncData = SyncData::from(reader);

    EXPECT_EQ(syncData.getTransitionId(), TRANSITION_ID);
}

TEST(SyncDataFromCapnp, it_contains_the_transition_hold_status) {
    auto message = sync_data_message();
    capnp::FlatArrayMessageReader reader(message);

    auto syncData = SyncData::from(reader);

    EXPECT_EQ(syncData.transition_holds(), TRANSITION_HOLDS);
}

TEST(SyncDataFromCapnp, it_contains_the_acknowledgement_status) {
    auto message = sync_data_message();
    capnp::FlatArrayMessageReader reader(message);

    auto syncData = SyncData::from(reader);

    EXPECT_EQ(syncData.ack(), ACK);
}