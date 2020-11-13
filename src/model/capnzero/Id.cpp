#include <model/capnzero/Id.h>
#include <stdexcept>
#include <vector>

namespace model {
    capnzero::Id capnzero::Id::from(capnp::MessageReader& reader) {
        auto idReader = reader.getRoot<::capnzero::ID>();
        return from(idReader);
    }

    capnzero::Id capnzero::Id::from(::capnzero::ID::Reader& reader) {
        if(!isValid(reader)) {
            throw std::runtime_error("Invalid Capnzero ID");
        }

        auto type = reader.getType();
        auto value = reader.getValue();

        return capnzero::Id(type, std::vector<uint8_t>(value.begin(), value.end()));
    }

    bool capnzero::Id::isValid(::capnzero::ID::Reader &reader) {
        return reader.hasValue();
    }

    capnzero::Id::Id(uint8_t type, std::vector<uint8_t> value): type_ {type}, value_ {std::move(value)} {}

    uint8_t capnzero::Id::getType() const {
        return type_;
    }

    std::vector<uint8_t> capnzero::Id::getValue() const {
        return value_;
    }
}