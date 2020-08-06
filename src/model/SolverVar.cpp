#include <model/SolverVar.h>
#include <SolverResult.capnp.h>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

SolverVar::SolverVar(int64_t id, std::vector<uint8_t> &value) : id_(id), value_(value) {}

SolverVar SolverVar::from(capnp::MessageReader &reader) {
    auto solverVar = reader.getRoot<alica_msgs::SolverVar>();
    return from(solverVar);
}

SolverVar SolverVar::from(alica_msgs::SolverVar::Reader &solverVar) {
    if(!solverVar.hasValue()) {
        throw std::runtime_error("Invalid Solver Var");
    }

    auto valueReader = solverVar.getValue();
    std::vector<uint8_t> value;
    value.reserve(valueReader.size());
    for(auto v: valueReader) {
        value.emplace_back(v);
    }

    return {
            solverVar.getId(),
            value
    };
}

int64_t SolverVar::getId() const {
    return id_;
}

std::vector<uint8_t> SolverVar::getValue() const {
    return value_;
}

const std::string SolverVar::toJson() const {
    rapidjson::Document solverVar(rapidjson::kObjectType);
    solverVar.AddMember("id", id_, solverVar.GetAllocator());
    rapidjson::Value value(rapidjson::kArrayType);
    for(auto v: value_) {
        value.PushBack(v, solverVar.GetAllocator());
    }
    solverVar.AddMember("value", value, solverVar.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    solverVar.Accept(writer);

    return buffer.GetString();
}
