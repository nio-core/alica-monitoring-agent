#include <AllocationAuthorityInfo.capnp.h>
#include <stdexcept>
#include <model/EntrypointRobots.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <rapidjson/writer.h>

EntrypointRobots::EntrypointRobots(int64_t entrypoint, std::vector<capnzero::Id> &robots)
        : entrypoint_(entrypoint), robots_(robots) {}


EntrypointRobots EntrypointRobots::from(capnp::MessageReader &reader) {
    auto entrypointRobots = reader.getRoot<alica_msgs::EntrypointRobots>();
    return from(entrypointRobots);
}

EntrypointRobots EntrypointRobots::from(alica_msgs::EntrypointRobots::Reader &entrypointRobots) {
    if(!entrypointRobots.hasRobots()) {
        throw std::runtime_error("Invalid entrypoint Robots");
    }

    std::vector<capnzero::Id> robots;
    for(auto robot: entrypointRobots.getRobots()) {
        robots.emplace_back(capnzero::Id::from(robot));
    }

    return {
            entrypointRobots.getEntrypoint(),
            robots
    };
}

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
    for(const auto& robot: robots_) {
        rapidjson::Document r;
        r.Parse(robot.toJson().c_str());
        robots.PushBack(r.GetObject(), entrypointRobots.GetAllocator());
    }
    entrypointRobots.AddMember("robots", robots, entrypointRobots.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    entrypointRobots.Accept(writer);

    return buffer.GetString();
}
