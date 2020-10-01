#include <gtest/gtest.h>

#include <test_values_common.h>
#include <rapidjson/document.h>
#include <serialization/JsonSerializationStrategy.h>

model::RoleSwitch role_switch() {
     model::capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));

    return { senderId, ROLE_ID, TYPE };
}

TEST(RoleSwtichToJson, it_is_an_object) {
    auto roleSwitch = role_switch();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeRoleSwitch(roleSwitch);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(RoleSwtichToJson, it_contains_sender_id) {
    auto roleSwitch = role_switch();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeRoleSwitch(roleSwitch);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(RoleSwtichToJson, it_contains_the_role_id) {
    auto roleSwitch = role_switch();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeRoleSwitch(roleSwitch);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["roleId"].GetInt(), ROLE_ID);
}
