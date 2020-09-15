#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <test_values_common.h>
#include <RoleSwitch.capnp.h>
#include <capnp/serialize.h>
#include <conversion.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <test_messages_common.h>


TEST(RoleSwtichFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::RoleSwitch>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(RoleSwitch::from(reader), std::runtime_error);
}

TEST(RoleSwtichFromCapnp, it_can_not_parse_other_message) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(RoleSwitch::from(reader), std::runtime_error);
}

TEST(RoleSwtichFromCapnp, it_can_be_parsed) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(RoleSwitch::from(reader));
}

TEST(RoleSwtichFromCapnp, it_contains_the_sender_id) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto roleSwitch = RoleSwitch::from(reader);
    auto senderId = roleSwitch.getSenderId();

    EXPECT_EQ(senderId.getType(), ID_TYPE);
    EXPECT_EQ(senderId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(RoleSwtichFromCapnp, it_contains_the_role_id) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto roleSwitch = RoleSwitch::from(reader);

    EXPECT_EQ(roleSwitch.getRoleId(), ROLE_ID);
}

