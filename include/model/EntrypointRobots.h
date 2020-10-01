#pragma once

#include <capnp/serialize.h>
#include <vector>
#include <model/capnzero/Id.h>
#include <AllocationAuthorityInfo.capnp.h>

namespace model {
    class EntrypointRobots {
    public:
        static EntrypointRobots from(capnp::MessageReader &reader);

        static EntrypointRobots from(alica_msgs::EntrypointRobots::Reader &reader);

        static bool isValid(alica_msgs::EntrypointRobots::Reader &reader);

    public:
        EntrypointRobots(int64_t entrypoint, std::vector<capnzero::Id> &robots);

        int64_t getEntrypoint() const;

        std::vector<capnzero::Id> getRobots() const;

        std::string toJson() const;

    private:
        int64_t entrypoint_;
        std::vector<capnzero::Id> robots_;
    };
}