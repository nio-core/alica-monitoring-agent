#include <gtest/gtest.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <AlicaEngineInfo.capnp.h>
#include <test_values_common.h>
#include <test_messages_common.h>
#include <conversion.h>

TEST(AllocationAuthorityInfoFromCapnp, it_can_be_parsed_if_valid) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(AllocationAuthorityInfo::from(reader));
}

TEST(AllocationAuthorityInfoFromCapnp, other_messages_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(AllocationAuthorityInfo::from(reader), std::runtime_error);
}

TEST(AllocationAuthorityInfoFromCapnp, with_missing_fields_can_not_be_Parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(AllocationAuthorityInfo::from(reader), std::runtime_error);
}

TEST(AllocationAuthorityInfoFromCapnp, sender_id_is_set_properly) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto allocationAuthorityInfo = AllocationAuthorityInfo::from(reader);
    auto senderIdType = allocationAuthorityInfo.getSenderId().getType();
    auto senderIdValue = allocationAuthorityInfo.getSenderId().getValue();

    EXPECT_EQ(senderIdType, ID_TYPE);
    EXPECT_EQ(std::string(senderIdValue.begin(), senderIdValue.end()), ID_VALUE);
}

TEST(AllocationAuthorityInfoFromCapnp, plan_id_is_set_properly) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto allocationAuthorityInfo = AllocationAuthorityInfo::from(reader);

    EXPECT_EQ(allocationAuthorityInfo.getPlanId(), PLAN_ID);
}

TEST(AllocationAuthorityInfoFromCapnp, parent_state_is_set_properly) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto allocationAuthorityInfo = AllocationAuthorityInfo::from(reader);

    EXPECT_EQ(allocationAuthorityInfo.getParentState(), PARENT_STATE);
}

TEST(AllocationAuthorityInfoFromCapnp, plan_type_is_set_properly) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto allocationAuthorityInfo = AllocationAuthorityInfo::from(reader);

    EXPECT_EQ(allocationAuthorityInfo.getPlanType(), PLAN_TYPE);
}

TEST(AllocationAuthorityInfoFromCapnp, authority_is_set_properly) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto allocationAuthorityInfo = AllocationAuthorityInfo::from(reader);
    auto authorityType = allocationAuthorityInfo.getAuthority().getType();
    auto authorityValue = allocationAuthorityInfo.getAuthority().getValue();

    EXPECT_EQ(authorityType, ID_TYPE);
    EXPECT_EQ(std::string(authorityValue.begin(), authorityValue.end()), ID_VALUE);
}

TEST(AllocationAuthorityInfoFromCapnp, entrypoint_robots_is_set_properly) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto allocationAuthorityInfo = AllocationAuthorityInfo::from(reader);
    auto entrypointRobots = allocationAuthorityInfo.getEntrypointRobots();
    EXPECT_EQ(entrypointRobots.size(), ENTRY_POINT_COUNT);
    for(const auto& entrypoint: entrypointRobots) {
        EXPECT_EQ(entrypoint.getEntrypoint(), ENTRY_POINT);
        auto robots = entrypoint.getRobots();
        EXPECT_EQ(robots.size(), ROBOT_COUNT);
        for(auto robot: robots) {
            EXPECT_EQ(robot.getType(), ID_TYPE);
            auto robotValue = robot.getValue();
            EXPECT_EQ(std::string(robotValue.begin(), robotValue.end()), ID_VALUE);
        }
    }
}
