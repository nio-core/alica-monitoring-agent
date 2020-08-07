#pragma once

#include <capnp/message.h>
#include <SolverResult.capnp.h>
#include <model/capnzero/Id.h>
#include <model/SolverVar.h>

class SolverResult {

public:
    SolverResult(const capnzero::Id &senderId, std::vector<SolverVar> &vars);

    static SolverResult from(capnp::MessageReader &reader);

    static SolverResult from(alica_msgs::SolverResult::Reader &reader);

    static bool isValid(alica_msgs::SolverResult::Reader &reader);

    capnzero::Id getSenderId() const;

    std::vector<SolverVar> getVars() const;

    const std::string toJson() const;

private:
    capnzero::Id senderId_;
    std::vector<SolverVar> vars_;
};