#pragma once

#include <storage/StorageStrategy.h>

class SawtoothCliBasedStorage : public StorageStrategy {
public:
    explicit SawtoothCliBasedStorage(const std::string &validatorAddress);

    void store(const model::capnzero::Id& agent, const std::string& messageType, const std::string& message) override;

private:
    std::string validatorAddress;
};
