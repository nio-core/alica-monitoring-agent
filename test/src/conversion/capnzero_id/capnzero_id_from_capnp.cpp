#include <gtest/gtest.h>
#include <capnzero/ID.capnp.h>
#include <capnp/serialize.h>
#include <model/capnzero/Id.h>
#include <test_values_common.h>

kj::Array<capnp::word> capnzero_id_message() {
    capnp::MallocMessageBuilder builder;
    auto id = builder.initRoot<capnzero::ID>();
    id.setValue(kj::StringPtr(ID_VALUE).asBytes());
    id.setType(ID_TYPE);

    return capnp::messageToFlatArray(builder);
}

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

TEST(CapnzeroIDFromCapnp, fields_are_set_correctly) {
    auto message = capnzero_id_message();
    auto reader = capnp::FlatArrayMessageReader(message);

    auto id = capnzero::Id::from(reader);
    auto type = id.getType();
    auto value = id.getValue();

    EXPECT_EQ(type, ID_TYPE);
    EXPECT_EQ(std::string(value.begin(), value.end()), ID_VALUE);
}