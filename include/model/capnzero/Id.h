#pragma once

#include <capnp/serialize.h>
#include <capnzero/ID.capnp.h>
#include <vector>
#include <string>

namespace capnzero {
    class Id {

    public:
        Id(uint8_t type, std::vector<uint8_t> value);

        static Id from(capnp::MessageReader& reader);
        static Id from(capnzero::ID::Reader& reader);

        uint8_t getType() const;

        std::vector<uint8_t>& getValue();

        std::string toJson() const;

    private:
        uint8_t type_;
        std::vector<uint8_t> value_;
    };
}
