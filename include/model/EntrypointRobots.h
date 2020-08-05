#pragma once

#include <capnp/serialize.h>
#include <vector>
#include <model/capnzero/Id.h>
#include <AllocationAuthorityInfo.capnp.h>

class EntrypointRobots {

public:
    EntrypointRobots(int64_t entrypoint, std::vector<capnzero::Id> &robots);

    static EntrypointRobots from(capnp::MessageReader& reader);
    static EntrypointRobots from(alica_msgs::EntrypointRobots::Reader& reader);

    int64_t getEntrypoint() const;

    std::vector<capnzero::Id> getRobots() const;

    std::string toJson() const;

private:
    int64_t entrypoint_;
    std::vector<capnzero::Id> robots_;
};
