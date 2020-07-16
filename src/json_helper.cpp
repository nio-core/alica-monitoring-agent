#include <json_helper.h>

rapidjson::Value helper::capnzero_id_to_json_value(capnzero::ID::Reader id, rapidjson::MemoryPoolAllocator<>& allocator) {
    rapidjson::Value object(rapidjson::kObjectType);
    rapidjson::Value value;

    object.AddMember("type", id.getType(), allocator);
    auto val = std::string(id.getValue().begin(), id.getValue().end());
    value.SetString(val.c_str(), static_cast<rapidjson::SizeType>(val.size()), allocator);
    object.AddMember("value", value.Move(), allocator);

    return object;
}