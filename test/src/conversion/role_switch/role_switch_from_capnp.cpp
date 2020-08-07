#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <test_values_common.h>
#include <RoleSwitch.capnp.h>
#include <capnp/serialize.h>
#include <model/RoleSwitch.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <search.h>

kj::Array<capnp::word> role_switch_message() {
    capnp::MallocMessageBuilder builder;
    auto roleSwitch = builder.initRoot<alica_msgs::RoleSwitch>();
    auto senderId = roleSwitch.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    roleSwitch.setRoleId(ROLE_ID);
    return capnp::messageToFlatArray(builder);
}

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
    auto senderIdType = roleSwitch.getSenderId().getType();
    auto senderIdValue = roleSwitch.getSenderId().getValue();

    EXPECT_EQ(senderIdType, ID_TYPE);
    EXPECT_EQ(senderIdValue, std::vector<uint8_t>(senderIdValue.begin(), senderIdValue.end()));
}

TEST(RoleSwtichFromCapnp, it_contains_the_role_id) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto roleSwitch = RoleSwitch::from(reader);

    EXPECT_EQ(roleSwitch.getRoleId(), ROLE_ID);
}

