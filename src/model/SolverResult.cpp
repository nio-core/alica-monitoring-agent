#include <model/SolverResult.h>
#include <SolverResult.capnp.h>
#include <stdexcept>
#include <model/SolverVar.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

SolverResult::SolverResult(const capnzero::Id &senderId, std::vector<SolverVar> &vars)
        : senderId_(senderId), vars_(vars) {}


SolverResult SolverResult::from(capnp::MessageReader &reader) {
    auto solverResult = reader.getRoot<alica_msgs::SolverResult>();
    return from(solverResult);
}

SolverResult SolverResult::from(alica_msgs::SolverResult::Reader &solverResult) {
    if(!isValid(solverResult)) {
        throw std::runtime_error("Invalid Solver Result");
    }

    auto senderIdReader = solverResult.getSenderId();
    capnzero::Id senderId = capnzero::Id::from(senderIdReader);

    auto varsReader = solverResult.getVars();
    std::vector<SolverVar> vars;
    for(auto var: varsReader) {
        vars.emplace_back(SolverVar::from(var));
    }

    return {
            senderId,
            vars
    };
}

bool SolverResult::isValid(alica_msgs::SolverResult::Reader &solverResult) {
    return solverResult.hasSenderId() && solverResult.hasVars();
}

capnzero::Id SolverResult::getSenderId() const {
    return senderId_;
}

std::vector<SolverVar> SolverResult::getVars() const {
    return vars_;
}

const std::string SolverResult::toJson() const {
    rapidjson::Document solverResult(rapidjson::kObjectType);

    rapidjson::Document senderId;
    senderId.Parse(senderId_.toJson().c_str());
    solverResult.AddMember("senderId", senderId.GetObject(), senderId.GetAllocator());

    rapidjson::Value vars(rapidjson::kArrayType);
    for(const auto& var: vars_) {
        rapidjson::Document v;
        v.Parse(var.toJson().c_str());
        vars.PushBack(v.GetObject(), solverResult.GetAllocator());
    }
    solverResult.AddMember("vars", vars, solverResult.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    solverResult.Accept(writer);

    return buffer.GetString();
}
