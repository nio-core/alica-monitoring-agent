#include <model/SolverResult.h>
#include <stdexcept>

namespace model {
    SolverResult SolverResult::from(capnp::MessageReader &reader) {
        auto solverResult = reader.getRoot<alica_msgs::SolverResult>();
        return from(solverResult);
    }

    SolverResult SolverResult::from(alica_msgs::SolverResult::Reader &reader) {
        if (!isValid(reader)) {
            throw std::runtime_error("Invalid Solver Result");
        }

        auto senderIdReader = reader.getSenderId();
        capnzero::Id senderId = capnzero::Id::from(senderIdReader);

        auto varsReader = reader.getVars();
        std::vector<SolverVar> vars;
        for (auto var: varsReader) {
            vars.emplace_back(SolverVar::from(var));
        }

        return {
                senderId,
                vars
        };
    }

    bool SolverResult::isValid(alica_msgs::SolverResult::Reader &reader) {
        return reader.hasSenderId() && reader.hasVars();
    }

    SolverResult::SolverResult(const capnzero::Id &senderId, std::vector<SolverVar> &vars)
            : senderId_(senderId), vars_(vars) {}


    capnzero::Id SolverResult::getSenderId() const {
        return senderId_;
    }

    std::vector<SolverVar> SolverResult::getVars() const {
        return vars_;
    }
}