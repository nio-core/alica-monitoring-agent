#pragma once

#include <capnp/serialize.h>
#include <capnzero/ID.capnp.h>
#include <vector>
#include <string>

namespace model {
    namespace capnzero {
        class Id {
        public:
            static Id from(capnp::MessageReader &reader);

            static Id from(::capnzero::ID::Reader &reader);

            static bool isValid(::capnzero::ID::Reader &reader);

        public:
            Id(uint8_t type, std::vector<uint8_t> value);

            uint8_t getType() const;

            std::vector<uint8_t> getValue() const;

        private:
            uint8_t type_;
            std::vector<uint8_t> value_;
        };
    }
}