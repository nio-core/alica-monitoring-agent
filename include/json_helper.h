#pragma once

#include <rapidjson/pointer.h>
#include <capnzero/ID.capnp.h>

namespace helper {
    rapidjson::Value capnzero_id_to_json_value(capnzero::ID::Reader id, rapidjson::MemoryPoolAllocator<>& allocator);
}
