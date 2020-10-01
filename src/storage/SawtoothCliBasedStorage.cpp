#include <storage/SawtoothCliBasedStorage.h>
#include <sstream>
#include <iostream>
#include <chrono>
#include "exception/StorageException.h"

SawtoothCliBasedStorage::SawtoothCliBasedStorage(const std::string &validatorAddress)
: validatorAddress(validatorAddress) {}

void SawtoothCliBasedStorage::store(const model::capnzero::Id &agent, const std::string &messageType,
                                    const std::string &message) {
    auto agentIdValue = agent.getValue();
    auto agentId = std::string(agentIdValue.begin(), agentIdValue.end());
    auto secondsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

    std::stringstream command;
    command << "alica-messages-client"
            << " --connect " << validatorAddress
            << " new"
            << " --id " << agentId
            << " --type" << messageType
            << " --message " << message
            << " --timestamp " << secondsSinceEpoch;

    const std::string finalCommand = command.str();
    std::cout << finalCommand << std::endl;

    auto returnCode = system(finalCommand.c_str());
    if(returnCode != 0) {
        std::stringstream errorMessage;
        errorMessage << "Command exited with code " << returnCode;
        throw StorageException(errorMessage.str().c_str());
    }
}
