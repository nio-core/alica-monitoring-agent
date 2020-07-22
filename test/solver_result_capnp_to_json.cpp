#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize.h>
#include <SolverResult.capnp.h>
#include <test_values_common.h>
#include <processing.h>
#include <rapidjson/document.h>

auto VAR_COUNT = 3;
auto SOLVER_VAR_ID = 1;
auto SOLVER_VAR_VALUE_COUNT = 3;

kj::Array<capnp::word> solver_result_message() {
    capnp::MallocMessageBuilder builder;
    auto solverResult = builder.initRoot<alica_msgs::SolverResult>();
    auto senderId = solverResult.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto vars = solverResult.initVars(VAR_COUNT);
    for(auto var: vars) {
        var.setId(SOLVER_VAR_ID);
        var.setValue({1, 2, 3});
    }

    return capnp::messageToFlatArray(builder);
}

TEST(SolverResultCapnprotoToJson, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SolverResult>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(processing::solver_result_canproto_to_json(reader), std::runtime_error);
}

TEST(SolverResultCapnprotoToJson, it_can_be_parsed) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(processing::solver_result_canproto_to_json(reader));
}

TEST(SolverResultCapnprotoToJson, it_contains_sender_id) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::solver_result_canproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_STREQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SolverResultCapnprotoToJson, it_contains_solver_vars) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    const std::string json = processing::solver_result_canproto_to_json(reader);
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
    EXPECT_TRUE(doc["vars"].IsArray());
    EXPECT_EQ(doc["vars"].Size(), VAR_COUNT);
    for(auto& var : doc["vars"].GetArray()) {
        EXPECT_TRUE(var.IsObject());
        EXPECT_EQ(var["id"], SOLVER_VAR_ID);
        EXPECT_TRUE(var["value"].IsArray());
        EXPECT_EQ(var["value"].Size(), SOLVER_VAR_VALUE_COUNT);
    }
}