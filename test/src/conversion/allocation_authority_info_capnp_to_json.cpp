//#include <gtest/gtest.h>
//
//TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_parent_state) {
//auto message = prepare_allocation_authority_info_message();
//auto reader = capnp::FlatArrayMessageReader(message);
//
//const std::string json = processing::allocation_authority_info_capnproto_to_json(reader);
//rapidjson::Document doc;
//doc.Parse(json.c_str());
//EXPECT_TRUE(doc.IsObject());
//EXPECT_EQ(doc["parentState"].GetInt(), PARENT_STATE);
//}
//
//TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_plan_type) {
//auto message = prepare_allocation_authority_info_message();
//auto reader = capnp::FlatArrayMessageReader(message);
//
//const std::string json = processing::allocation_authority_info_capnproto_to_json(reader);
//rapidjson::Document doc;
//doc.Parse(json.c_str());
//EXPECT_TRUE(doc.IsObject());
//EXPECT_EQ(doc["planType"].GetInt(), PLAN_TYPE);
//}
//
//TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_plan_id) {
//auto message = prepare_allocation_authority_info_message();
//auto reader = capnp::FlatArrayMessageReader(message);
//
//const std::string json = processing::allocation_authority_info_capnproto_to_json(reader);
//rapidjson::Document doc;
//doc.Parse(json.c_str());
//EXPECT_TRUE(doc.IsObject());
//EXPECT_EQ(doc["planId"].GetInt(), PLAN_ID);
//}
//
//TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_authority) {
//auto message = prepare_allocation_authority_info_message();
//auto reader = capnp::FlatArrayMessageReader(message);
//
//const std::string json = processing::allocation_authority_info_capnproto_to_json(reader);
//rapidjson::Document doc;
//doc.Parse(json.c_str());
//EXPECT_TRUE(doc.IsObject());
//EXPECT_TRUE(doc["authority"].IsObject());
//EXPECT_EQ(doc["authority"]["type"].GetInt(), ID_TYPE);
//EXPECT_STREQ(doc["authority"]["value"].GetString(), ID_VALUE);
//}
//
//TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_sender_id) {
//auto message = prepare_allocation_authority_info_message();
//auto reader = capnp::FlatArrayMessageReader(message);
//
//const std::string json = processing::allocation_authority_info_capnproto_to_json(reader);
//rapidjson::Document doc;
//doc.Parse(json.c_str());
//EXPECT_TRUE(doc.IsObject());
//EXPECT_TRUE(doc["senderId"].IsObject());
//EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
//EXPECT_STREQ(doc["senderId"]["value"].GetString(), ID_VALUE);
//}
//
//TEST(AllocationAuthorityInfoCapnprotoToJson, it_contains_entry_point_robots) {
//auto message = prepare_allocation_authority_info_message();
//auto reader = capnp::FlatArrayMessageReader(message);
//
//const std::string json = processing::allocation_authority_info_capnproto_to_json(reader);
//rapidjson::Document doc;
//doc.Parse(json.c_str());
//EXPECT_TRUE(doc.IsObject());
//EXPECT_TRUE(doc["entryPointRobots"].IsArray());
//EXPECT_EQ(doc["entryPointRobots"].Size(), ENTRY_POINT_COUNT);
//for(int i = 0; i < ENTRY_POINT_COUNT; i++) {
//EXPECT_EQ(doc["entryPointRobots"][i]["entryPoint"].GetInt(), ENTRY_POINT);
//EXPECT_TRUE(doc["entryPointRobots"][i]["robots"].IsArray());
//for(int j = 0; j < ROBOT_COUNT; j++) {
//EXPECT_EQ(doc["entryPointRobots"][i]["robots"][j]["type"].GetInt(), ID_TYPE);
//EXPECT_STREQ(doc["entryPointRobots"][i]["robots"][j]["value"].GetString(), ID_VALUE);
//}
//}
//}