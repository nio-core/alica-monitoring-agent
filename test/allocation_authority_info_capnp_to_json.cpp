#include <json_helper.h>
#include <processing.h>
#include <gtest/gtest.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <AlicaEngineInfo.capnp.h>
#include <test_values_common.h>

auto PARENT_STATE = 1;
auto PLAN_TYPE = 1;
auto PLAN_ID = 1;
auto ENTRY_POINT_COUNT = 3;
auto ENTRY_POINT = 1;
auto ROBOT_COUNT = 2;

kj::Array<capnp::word> prepare_allocation_authority_info_message() {
    capnp::MallocMessageBuilder builder;
    auto allocationAuthorityInformation = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    allocationAuthorityInformation.setParentState(PARENT_STATE);
    allocationAuthorityInformation.setPlanType(PLAN_TYPE);
    allocationAuthorityInformation.setPlanId(PLAN_ID);
    auto authority = allocationAuthorityInformation.initAuthority();
    authority.setType(ID_TYPE);
    authority.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto senderId = allocationAuthorityInformation.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto entryPoints = allocationAuthorityInformation.initEntrypointRobots(ENTRY_POINT_COUNT);
    for(auto entryPoint: entryPoints) {
        entryPoint.setEntrypoint(ENTRY_POINT);
        auto robots = entryPoint.initRobots(ROBOT_COUNT);
        for(auto robot: robots) {
            robot.setType(ID_TYPE);
            robot.setValue(kj::StringPtr(ID_VALUE).asBytes());
        }
    }
    return capnp::messageToFlatArray(builder);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_can_be_parsed) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::try_read_allocation_authority_information(reader));
}

TEST(AllocationAuthorityInfoCapnprotoToJson, other_messages_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AlicaEngineInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::try_read_allocation_authority_information(reader), std::runtime_error);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, with_missing_fields_can_not_be_Parsed) {
    capnp::MallocMessageBuilder builder;
    auto engineInfo = builder.initRoot<alica_msgs::AllocationAuthorityInfo>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::try_read_allocation_authority_information(reader), std::runtime_error);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_parent_state) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_allocation_authority_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    EXPECT_TRUE(doc.IsObject());
    EXPECT_EQ(doc["parentState"].GetInt(), PARENT_STATE);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_plan_type) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_allocation_authority_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    EXPECT_TRUE(doc.IsObject());
    EXPECT_EQ(doc["planType"].GetInt(), PLAN_TYPE);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_plan_id) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_allocation_authority_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    EXPECT_TRUE(doc.IsObject());
    EXPECT_EQ(doc["planId"].GetInt(), PLAN_ID);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_authority) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_allocation_authority_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["authority"].IsObject());
    EXPECT_EQ(doc["authority"]["type"].GetInt(), ID_TYPE);
    EXPECT_STREQ(doc["authority"]["value"].GetString(), ID_VALUE);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_sender_id) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_allocation_authority_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_STREQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_entry_point_robots) {
    auto message = prepare_allocation_authority_info_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::try_read_allocation_authority_information(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["entryPointRobots"].IsArray());
    EXPECT_EQ(doc["entryPointRobots"].Size(), ENTRY_POINT_COUNT);
    for(int i = 0; i < ENTRY_POINT_COUNT; i++) {
        EXPECT_EQ(doc["entryPointRobots"][i]["entryPoint"].GetInt(), ENTRY_POINT);
        EXPECT_TRUE(doc["entryPointRobots"][i]["robots"].IsArray());
        for(int j = 0; j < ROBOT_COUNT; j++) {
            EXPECT_EQ(doc["entryPointRobots"][i]["robots"][j]["type"].GetInt(), ID_TYPE);
            EXPECT_STREQ(doc["entryPointRobots"][i]["robots"][j]["value"].GetString(), ID_VALUE);
        }
    }
}