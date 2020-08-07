#include <gtest/gtest.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize.h>
#include <SolverResult.capnp.h>
#include <test_values_common.h>
#include <rapidjson/document.h>
#include <model/SolverResult.h>

kj::Array<capnp::word> solver_result_message() {
    capnp::MallocMessageBuilder builder;
    auto solverResult = builder.initRoot<alica_msgs::SolverResult>();
    auto senderId = solverResult.initSenderId();
    senderId.setType(ID_TYPE);
    senderId.setValue(kj::StringPtr(ID_VALUE).asBytes());
    auto vars = solverResult.initVars(SOLVER_VAR_COUNT);
    for(auto var: vars) {
        var.setId(SOLVER_VAR_ID);
        auto solverVarReader = var.initValue(SOLVER_VAR_VALUE_SIZE);
        for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
            solverVarReader.set(i, i);
        }
    }

    return capnp::messageToFlatArray(builder);
}

TEST(SolverResultFromCapnp, with_missing_fields_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SolverResult>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(SolverResult::from(reader), std::runtime_error);
}

TEST(SolverResultFromCapnp, it_can_not_parse_other_messages) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::SolverVar>();
    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(SolverResult::from(reader), std::runtime_error);
}

TEST(SolverResultFromCapnp, it_can_be_parsed) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(SolverResult::from(reader));
}

TEST(SolverResultFromCapnp, it_contains_the_sender_id) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto solverResult = SolverResult::from(reader);
    auto senderId = solverResult.getSenderId();

    EXPECT_EQ(senderId.getType(), ID_TYPE);
    EXPECT_EQ(senderId.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}

TEST(SolverResultFromCapnp, it_contains_the_vars) {
    auto message = solver_result_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto solverResult = SolverResult::from(reader);
    auto vars = solverResult.getVars();

    EXPECT_EQ(vars.size(), SOLVER_VAR_COUNT);
    for(const auto& var: vars) {
        EXPECT_EQ(var.getId(), SOLVER_VAR_ID);
        auto value = var.getValue();
        for(int i = 0; i < SOLVER_VAR_VALUE_SIZE; i++) {
            EXPECT_EQ(value[i], i);
        }
    }
}

