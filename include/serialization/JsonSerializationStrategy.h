#pragma once

#include "SerializationStrategy.h"

class JsonSerializationStrategy : public SerializationStrategy {
public:
    std::string serializeCapnzeroId(model::capnzero::Id& id) const override;

    std::string serializeEntryPointRobots(model::EntrypointRobots& entrypointRobots) const override;

    std::string serializeSolverVar(model::SolverVar& solverVar) const override;

    std::string serializeSyncData(model::SyncData& syncData) const override;

    std::string serializeAlicaEngineInfo(model::AlicaEngineInfo& alicaEngineInfo) const override;

    std::string serializeAllocationAuthorityInfo(model::AllocationAuthorityInfo& allocationAuthorityInfo) const override;

    std::string serializePlanTreeInfo(model::PlanTreeInfo& planTreeInfo) const override;

    std::string serializeRoleSwitch(model::RoleSwitch& roleSwitch) const override;

    std::string serializeSolverResult(model::SolverResult& solverResult) const override;

    std::string serializeSyncReady(model::SyncReady& syncReady) const override;

    std::string serializeSyncTalk(model::SyncTalk& syncTalk) const override;
};
