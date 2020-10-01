#include <gtest/gtest.h>
#include <capnp/serialize.h>
#include <test_values_common.h>
#include <AllocationAuthorityInfo.capnp.h>

#include <test_messages_common.h>
#include <model/EntrypointRobots.h>


TEST(EntryPointRobotsFromCapnp, it_can_not_be_parsed_if_robots_are_missing) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::AllocationAuthorityInfo>();

    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(model::EntrypointRobots::from(reader), std::runtime_error);
}

TEST(EntryPointRobotsFromCapnp, other_messages_can_not_be_parsed) {
    capnp::MallocMessageBuilder builder;
    builder.initRoot<alica_msgs::EntrypointRobots>();

    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(model::EntrypointRobots::from(reader), std::runtime_error);
}

TEST(EntryPointRobotsFromCapnp, it_can_be_parsed_if_robots_are_set) {
    auto message = entrypoint_robots_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(model::EntrypointRobots::from(reader));
}

TEST(EntryPointRobotsFromCapnp, entrypoint_is_set) {
    auto message = entrypoint_robots_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto entrypointRobots = model::EntrypointRobots::from(reader);

    EXPECT_EQ(entrypointRobots.getEntrypoint(), ENTRY_POINT);
}

TEST(EntryPointRobotsFromCapnp, robots_are_set) {
    auto message = entrypoint_robots_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto entrypointRobots = model::EntrypointRobots::from(reader);
    auto robots = entrypointRobots.getRobots();

    EXPECT_EQ(robots.size(), ROBOT_COUNT);
    for(auto robot: robots) {

        EXPECT_EQ(robot.getType(), ID_TYPE);
        EXPECT_EQ(robot.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
    }
}
