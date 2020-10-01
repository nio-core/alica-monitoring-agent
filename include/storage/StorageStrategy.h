#pragma once

#include <model/capnzero/Id.h>

class StorageStrategy {
public:
    virtual ~StorageStrategy() = default;

    virtual void store(const model::capnzero::Id& agent, const std::string& messageType, const std::string& message) = 0;
};
