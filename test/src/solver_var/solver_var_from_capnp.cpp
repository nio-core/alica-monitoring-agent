#include <gtest/gtest.h>
#include <capnp/message.h>
#include <SolverResult.capnp.h>
#include <capnp/serialize.h>
#include <conversion.h>
#include <test_values_common.h>

kj::Array<capnp::word> solver_var_message() {
    capnp::MallocMessageBuilder builder;
    auto solverVar = builder.initRoot<alica_msgs::SolverVar>();
    solverVar.setId(SOLVER_VAR_ID);
    auto value = solverVar.initValue(SOLVER_VAR_VALUE_SIZE);
    for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
        value.set(i, i);
    }

    return capnp::messageToFlatArray(builder);
}

TEST(SolverVarFromCapnp, it_can_be_parsed) {
    auto message = solver_var_message();
    capnp::FlatArrayMessageReader reader(message);

    EXPECT_NO_THROW(SolverVar::from(reader));
}

TEST(SolverVarFromCapnp, it_can_no_be_parsed_if_value_is_missing) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SolverVar>();
    auto message = capnp::messageToFlatArray(builder);
    capnp::FlatArrayMessageReader reader(message);

    EXPECT_THROW(SolverVar::from(reader), std::runtime_error);
}

TEST(SolverVarFromCapnp, it_can_not_parse_other_messages) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SolverResult>();
    auto message = capnp::messageToFlatArray(builder);
    capnp::FlatArrayMessageReader reader(message);

    EXPECT_THROW(SolverVar::from(reader), std::runtime_error);
}

TEST(SolverVarFromCapnp, it_contains_the_id) {
    auto message = solver_var_message();
    capnp::FlatArrayMessageReader reader(message);

    auto solverVar = SolverVar::from(reader);

    EXPECT_EQ(solverVar.getId(), SOLVER_VAR_ID);
}

TEST(SolverVarFromCapnp, it_contains_the_value) {
    auto message = solver_var_message();
    capnp::FlatArrayMessageReader reader(message);

    auto solverVar = SolverVar::from(reader);
    auto solverVarValue = solverVar.getValue();

    EXPECT_EQ(solverVarValue.size(), SOLVER_VAR_VALUE_SIZE);
    for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
        EXPECT_EQ(solverVarValue[i], i);
    }
}