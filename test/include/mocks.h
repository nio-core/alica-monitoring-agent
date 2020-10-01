#pragma once

#include <gmock/gmock.h>
#include <serialization/SerializationStrategy.h>
#include <model/capnzero/Id.h>
#include <storage/StorageStrategy.h>

class MockSerializationStrategy : public SerializationStrategy {
public:
    MOCK_CONST_METHOD1(serializeCapnzeroId, std::string(model::capnzero::Id& id));
    MOCK_CONST_METHOD1(serializeEntryPointRobots, std::string(model::EntrypointRobots& entryPointRobots));
    MOCK_CONST_METHOD1(serializeSolverVar, std::string(model::SolverVar& solverVar));
    MOCK_CONST_METHOD1(serializeSyncData, std::string(model::SyncData& syncData));
    MOCK_CONST_METHOD1(serializeAlicaEngineInfo, std::string(model::AlicaEngineInfo& engineInfo));
    MOCK_CONST_METHOD1(serializeAllocationAuthorityInfo, std::string(model::AllocationAuthorityInfo& allocationAuthorityInfo));
    MOCK_CONST_METHOD1(serializePlanTreeInfo, std::string(model::PlanTreeInfo& planTreeInfo));
    MOCK_CONST_METHOD1(serializeRoleSwitch, std::string(model::RoleSwitch& roleSwitch));
    MOCK_CONST_METHOD1(serializeSolverResult, std::string(model::SolverResult& solverResult));
    MOCK_CONST_METHOD1(serializeSyncReady, std::string(model::SyncReady& syncReady));
    MOCK_CONST_METHOD1(serializeSyncTalk, std::string(model::SyncTalk& syncTalk));
};

class MockStorageStrategy : public StorageStrategy {
public:
    MOCK_METHOD3(store, void(const model::capnzero::Id& id, const std::string& messageType, const std::string& message));
};