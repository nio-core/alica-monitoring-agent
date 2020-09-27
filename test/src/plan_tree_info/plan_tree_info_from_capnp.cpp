
#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/serialize.h>
#include <PlanTreeInfo.capnp.h>
#include <conversion.h>
#include <test_values_common.h>
#include <rapidjson/document.h>
#include <test_messages_common.h>


TEST(PlanTreeInfoFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::PlanTreeInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(conversion::PlanTreeInfo::from(reader), std::runtime_error);
}

TEST(PlanTreeInfoFromCapnp, it_can_not_parse_other_messages_than_plan_tree_info) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(conversion::PlanTreeInfo::from(reader), std::runtime_error);
}

TEST(PlanTreeInfoFromCapnp, it_can_be_parsed) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(conversion::PlanTreeInfo::from(reader));
}

TEST(PlanTreeInfoFromCapnp, it_contains_the_sender_id) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto planTreeInfo = conversion::PlanTreeInfo::from(reader);
    auto senderId = planTreeInfo.getSenderId();

    EXPECT_EQ(senderId.getType(), ID_TYPE);
    EXPECT_EQ(senderId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(PlanTreeInfoFromCapnp, it_contains_the_state_ids) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto planTreeInfo = conversion::PlanTreeInfo::from(reader);

    auto stateIds = planTreeInfo.getStateIds();
    EXPECT_EQ(stateIds.size(), STATE_ID_COUNT);
    for(int i = 0; i < STATE_ID_COUNT; i++) {
        EXPECT_EQ(stateIds[i], i);
    }
}

TEST(PlanTreeInfoFromCapnp, it_contains_the_succeeded_eps) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto planTreeInfo = conversion::PlanTreeInfo::from(reader);

    auto succeededEps = planTreeInfo.getSucceededEps();
    EXPECT_EQ(succeededEps.size(), SUCCEEDED_EPS_COUNT);
    for(int i = 0; i < STATE_ID_COUNT; i++) {
        EXPECT_EQ(succeededEps[i], i);
    }
}