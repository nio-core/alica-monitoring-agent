#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <PlanTreeInfo.capnp.h>
#include <test_values_common.h>
#include <rapidjson/document.h>

auto STATE_ID_COUNT = 3;
auto SUCCEEDED_EPS_COUNT = 3;

kj::Array<capnp::word> plan_tree_info_message() {
    capnp::MallocMessageBuilder builder;
    auto planTreeInfo = builder.initRoot<alica_msgs::PlanTreeInfo>();
    auto senderId = planTreeInfo.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    planTreeInfo.setStateIds({1, 2, 3});
    planTreeInfo.setSucceededEps({1, 2, 3});
    return capnp::messageToFlatArray(builder);
}

TEST(PlanTreeInfoCapnprotoToJson, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::PlanTreeInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::try_read_plan_tree_information(reader), std::runtime_error);
}

TEST(PlanTreeInfoCapnprotoToJson, it_can_be_parsed) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::try_read_plan_tree_information(reader));
}

TEST(PlanTreeInfoCapnprotoToJson, it_contains_sender_id) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_plan_tree_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_STREQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(PlanTreeInfoCapnprotoToJson, it_contains_state_ids) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_plan_tree_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["stateIds"].IsArray());
    EXPECT_EQ(doc["stateIds"].Size(), STATE_ID_COUNT);
}

TEST(PlanTreeInfoCapnprotoToJson, it_contains_succeeded_eps) {
    auto message = plan_tree_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_plan_tree_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["succeededEps"].IsArray());
    EXPECT_EQ(doc["succeededEps"].Size(), SUCCEEDED_EPS_COUNT);
}