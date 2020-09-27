#include <conversion/EntrypointRobots.h>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace conversion {


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

    std::string EntrypointRobots::toJson() const {
        rapidjson::Document entrypointRobots(rapidjson::kObjectType);
        entrypointRobots.AddMember("entrypoint", entrypoint_, entrypointRobots.GetAllocator());
        rapidjson::Value robots(rapidjson::kArrayType);
        robots.GetArray().Reserve(robots_.size(), entrypointRobots.GetAllocator());
        rapidjson::Document r;
        for (const auto &robot: robots_) {
            r.Parse(robot.toJson().c_str());
            robots.PushBack(r, entrypointRobots.GetAllocator());
        }
        entrypointRobots.AddMember("robots", robots, entrypointRobots.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        entrypointRobots.Accept(writer);

        return buffer.GetString();
    }
}