#include <model/capnzero/Id.h>
#include <stdexcept>
#include <vector>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

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

    std::string capnzero::Id::toJson() const {
        rapidjson::Document id(rapidjson::kObjectType);
        id.AddMember("type", type_, id.GetAllocator());
        auto stringValue = std::string(value_.begin(), value_.end());
        id.AddMember("value", rapidjson::Value(stringValue.c_str(), stringValue.size(), id.GetAllocator()), id.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        id.Accept(writer);
        return buffer.GetString();
    }
}