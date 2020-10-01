#include <model/SolverVar.h>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace model {
    SolverVar SolverVar::from(capnp::MessageReader &reader) {
        auto solverVar = reader.getRoot<alica_msgs::SolverVar>();
        return from(solverVar);
    }

    SolverVar SolverVar::from(alica_msgs::SolverVar::Reader &reader) {
        if (!isValid(reader)) {
            throw std::runtime_error("Invalid Solver Var");
        }

        auto valueReader = reader.getValue();
        std::vector<uint8_t> value;
        value.reserve(valueReader.size());
        for (auto v: valueReader) {
            value.emplace_back(v);
        }

        return {
                reader.getId(),
                value
        };
    }

    bool SolverVar::isValid(alica_msgs::SolverVar::Reader &reader) {
        return reader.hasValue();
    }

    SolverVar::SolverVar(int64_t id, std::vector<uint8_t> &value) : id_(id), value_(value) {}

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
        for (auto v: value_) {
            value.PushBack(v, solverVar.GetAllocator());
        }
        solverVar.AddMember("value", value, solverVar.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        solverVar.Accept(writer);

        return buffer.GetString();
    }
}