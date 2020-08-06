#pragma once

#include <capnp/serialize.h>
#include <vector>
#include <string>
#include <SolverResult.capnp.h>

class SolverVar {

public:
    SolverVar(int64_t id, std::vector<uint8_t> &value);

    static SolverVar from(capnp::MessageReader& reader);

    static SolverVar from(alica_msgs::SolverVar::Reader& reader);

    int64_t getId() const;

    std::vector<uint8_t> getValue() const;

    const std::string toJson() const;

private:
    int64_t id_;
    std::vector<uint8_t> value_;
};

