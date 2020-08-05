#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <test_values_common.h>
#include <RoleSwitch.capnp.h>
#include <capnp/serialize.h>
#include <processing.h>
#include <rapidjson/document.h>

auto ROLE_ID = 1;

kj::Array<capnp::word> role_switch_message() {
    capnp::MallocMessageBuilder builder;
    auto roleSwitch = builder.initRoot<alica_msgs::RoleSwitch>();
    auto senderId = roleSwitch.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    roleSwitch.setRoleId(ROLE_ID);
    return capnp::messageToFlatArray(builder);
}

TEST(RoleSwtichCapnprotoToJson, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::RoleSwitch>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::role_switch_capnproto_to_json(reader), std::runtime_error);
}

TEST(RoleSwtichCapnprotoToJson, it_can_be_parsed) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::role_switch_capnproto_to_json(reader));
}

TEST(RoleSwtichCapnprotoToJson, it_contains_sender_id) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::role_switch_capnproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(RoleSwtichCapnprotoToJson, it_role_id) {
    auto message = role_switch_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::role_switch_capnproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_EQ(doc["roleId"].GetInt(), ROLE_ID);
}
