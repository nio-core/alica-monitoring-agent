#include <gtest/gtest.h>
#include <conversion.h>
#include <test_values_common.h>
#include <rapidjson/document.h>

RoleSwitch role_switch() {
    capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));

    return RoleSwitch(senderId, ROLE_ID);
}

TEST(RoleSwtichToJson, it_is_an_object) {
    const std::string json = role_switch().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(RoleSwtichToJson, it_contains_sender_id) {
    const std::string json = role_switch().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(RoleSwtichToJson, it_contains_the_role_id) {
    const std::string json = role_switch().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["roleId"].GetInt(), ROLE_ID);
}
