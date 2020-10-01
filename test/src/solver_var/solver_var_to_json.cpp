#include <gtest/gtest.h>
#include <rapidjson/document.h>

#include <test_values_common.h>
#include <serialization/JsonSerializationStrategy.h>

model::SolverVar solver_var() {
    std::vector<uint8_t> value;
    value.reserve(SOLVER_VAR_VALUE_SIZE);
    for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
        value.emplace_back(i);
    }
    return { SOLVER_VAR_ID, value };
}

TEST(SolverVarToJson, it_is_an_object) {
    auto solverVar = solver_var();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSolverVar(solverVar);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc.IsObject());
}

TEST(SolverVarToJson, it_contains_the_id) {
    auto solverVar = solver_var();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSolverVar(solverVar);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_EQ(doc["id"].GetInt(), SOLVER_VAR_ID);
}

TEST(SolverVarToJson, it_contains_the_value) {
    auto solverVar = solver_var();
    JsonSerializationStrategy serializationStrategy;
    const std::string json = serializationStrategy.serializeSolverVar(solverVar);

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    EXPECT_TRUE(doc["value"].IsArray());
    EXPECT_EQ(doc["value"].Size(), SOLVER_VAR_VALUE_SIZE);
    for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
        EXPECT_EQ(doc["value"][i].GetUint(), i);
    }
}