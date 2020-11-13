#pragma once

#include <capnp/message.h>
#include <SolverResult.capnp.h>
#include <model/capnzero/Id.h>
#include <model/SolverVar.h>

namespace model {
    class SolverResult {
    public:
        static SolverResult from(capnp::MessageReader &reader);

        static SolverResult from(alica_msgs::SolverResult::Reader &reader);

        static bool isValid(alica_msgs::SolverResult::Reader &reader);

    public:
        SolverResult(const capnzero::Id &senderId, std::vector<SolverVar> &vars);

        capnzero::Id getSenderId() const;

        std::vector<SolverVar> getVars() const;

    private:
        capnzero::Id senderId_;
        std::vector<SolverVar> vars_;
    };
}