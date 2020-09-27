#include <gtest/gtest.h>
#include <conversion.h>
#include <rapidjson/document.h>

TEST(CapnzeroIDToJson, it_creates_an_object) {
    uint8_t type { 0 };
    std::string value { "value" };
    conversion::capnzero::Id id(type, std::vector<uint8_t>(value.begin(), value.end()));

    std::string json = id.toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(CapnzeroIDToJson, it_contains_the_type) {
    uint8_t type { 0 };
    std::string value { "value" };
    conversion::capnzero::Id id(type, std::vector<uint8_t>(value.begin(), value.end()));

    std::string json = id.toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["type"].GetInt(), type);
}

TEST(CapnzeroIDToJson, it_contains_the_value) {
    uint8_t type { 0 };
    std::string value { "value" };
    conversion::capnzero::Id id(type, std::vector<uint8_t>(value.begin(), value.end()));

    std::string json = id.toJson();

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["value"].GetString(), value);
}