#include <gtest/gtest.h>
#include <capnzero/ID.capnp.h>
#include <capnp/serialize.h>
#include <test_values_common.h>
#include <conversion.h>
#include <test_messages_common.h>


TEST(CapnzeroIDFromCapnp, it_can_not_be_parsed_if_value_is_missing) {
    capnp::MallocMessageBuilder builder;
    auto id = builder.initRoot<capnzero::ID>();

    auto message = capnp::messageToFlatArray(builder);
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_THROW(capnzero::Id::from(reader), std::runtime_error);
}

TEST(CapnzeroIDFromCapnp, it_can_be_parsed_if_value_is_set) {
    auto message = capnzero_id_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    EXPECT_NO_THROW(capnzero::Id::from(reader));
}

TEST(CapnzeroIDFromCapnp, it_contains_the_type) {
    auto message = capnzero_id_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto id = capnzero::Id::from(reader);

    EXPECT_EQ(id.getType(), ID_TYPE);
}


TEST(CapnzeroIDFromCapnp, it_contains_the_value) {
    auto message = capnzero_id_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto id = capnzero::Id::from(reader);

    EXPECT_EQ(id.getValue(), std::vector<uint8_t>(ID_VALUE.begin(), ID_VALUE.end()));
}