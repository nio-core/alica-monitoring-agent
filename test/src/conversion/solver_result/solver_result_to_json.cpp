#include <gtest/gtest.h>
#include <test_values_common.h>
#include <model/SolverResult.h>
#include <rapidjson/document.h>

SolverResult solver_result() {
    capnzero::Id senderId(ID_TYPE, std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    std::vector<SolverVar> vars;
    vars.reserve(SOLVER_VAR_COUNT);
    for(int i = 0; i < SOLVER_VAR_COUNT; i++) {
        std::vector<uint8_t> value;
        for(int j = 0; j < SOLVER_VAR_VALUE_SIZE; j++) {
            value.emplace_back(j);
        }
        vars.emplace_back(SOLVER_VAR_ID, value);
    }

    return {
            senderId,
            vars
    };
}

TEST(SolverResultCapnprotoToJson, it_is_an_object) {
    const std::string json = solver_result().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(SolverResultCapnprotoToJson, it_contains_sender_id) {
    const std::string json = solver_result().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["senderId"].IsObject());
    EXPECT_EQ(doc["senderId"]["type"].GetInt(), ID_TYPE);
    EXPECT_EQ(doc["senderId"]["value"].GetString(), ID_VALUE);
}

TEST(SolverResultCapnprotoToJson, it_contains_solver_vars) {
    const std::string json = solver_result().toJson();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["vars"].IsArray());
    EXPECT_EQ(doc["vars"].Size(), SOLVER_VAR_COUNT);
    for(auto& var : doc["vars"].GetArray()) {
        EXPECT_TRUE(var.IsObject());
        EXPECT_EQ(var["id"].GetInt(), SOLVER_VAR_ID);
        EXPECT_TRUE(var["value"].IsArray());
        EXPECT_EQ(var["value"].Size(), SOLVER_VAR_VALUE_SIZE);
        for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
            EXPECT_EQ(var["value"][i].GetUint(), i);
        }
    }
}