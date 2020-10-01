#pragma once

#include "SerializationStrategy.h"

class JsonSerializationStrategy : public SerializationStrategy {
public:
    std::string serializeCapnzeroId(conversion::capnzero::Id& id) const override;

    std::string serializeEntryPointRobots(conversion::EntrypointRobots& entrypointRobots) const override;

    std::string serializeSolverVar(conversion::SolverVar& solverVar) const override;

    std::string serializeSyncData(conversion::SyncData& syncData) const override;

    std::string serializeAlicaEngineInfo(conversion::AlicaEngineInfo& alicaEngineInfo) const override;

    std::string serializeAllocationAuthorityInfo(conversion::AllocationAuthorityInfo& allocationAuthorityInfo) const override;

    std::string serializePlanTreeInfo(conversion::PlanTreeInfo& planTreeInfo) const override;

    std::string serializeRoleSwitch(conversion::RoleSwitch& roleSwitch) const override;

    std::string serializeSolverResult(conversion::SolverResult& solverResult) const override;

    std::string serializeSyncReady(conversion::SyncReady& syncReady) const override;

    std::string serializeSyncTalk(conversion::SyncTalk& syncTalk) const override;
};
