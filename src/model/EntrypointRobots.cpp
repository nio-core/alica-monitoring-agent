#include <model/EntrypointRobots.h>
#include <stdexcept>

namespace model {
    EntrypointRobots EntrypointRobots::from(capnp::MessageReader &reader) {
        auto entrypointRobots = reader.getRoot<alica_msgs::EntrypointRobots>();
        return from(entrypointRobots);
    }

    EntrypointRobots EntrypointRobots::from(alica_msgs::EntrypointRobots::Reader &reader) {
        if (!isValid(reader)) {
            throw std::runtime_error("Invalid entrypoint Robots");
        }

        std::vector<capnzero::Id> robots;
        for (auto robot: reader.getRobots()) {
            robots.emplace_back(capnzero::Id::from(robot));
        }

        return {
                reader.getEntrypoint(),
                robots
        };
    }

    bool EntrypointRobots::isValid(alica_msgs::EntrypointRobots::Reader &reader) {
        return reader.hasRobots();
    }

    EntrypointRobots::EntrypointRobots(int64_t entrypoint, std::vector<capnzero::Id> &robots)
            : entrypoint_(entrypoint), robots_(robots) {}

    int64_t EntrypointRobots::getEntrypoint() const {
        return entrypoint_;
    }

    std::vector<capnzero::Id> EntrypointRobots::getRobots() const {
        return robots_;
    }
}