#pragma once

#include <string>
#include <conversion.h>

class SerializationStrategy {
public:
    virtual ~SerializationStrategy() = default;

    virtual std::string serializeCapnzeroId(conversion::capnzero::Id& id) const = 0;

    virtual std::string serializeEntryPointRobots(conversion::EntrypointRobots& entrypointRobots) const = 0;

    virtual std::string serializeSolverVar(conversion::SolverVar& solverVar) const = 0;

    virtual std::string serializeSyncData(conversion::SyncData& syncData) const = 0;

    virtual std::string serializeAlicaEngineInfo(conversion::AlicaEngineInfo& alicaEngineInfo) const = 0;

    virtual std::string serializeAllocationAuthorityInfo(conversion::AllocationAuthorityInfo& allocationAuthorityInfo) const = 0;

    virtual std::string serializePlanTreeInfo(conversion::PlanTreeInfo& planTreeInfo) const = 0;

    virtual std::string serializeRoleSwitch(conversion::RoleSwitch& roleSwitch) const = 0;

    virtual std::string serializeSolverResult(conversion::SolverResult& solverResult) const = 0;

    virtual std::string serializeSyncReady(conversion::SyncReady& syncReady) const = 0;

    virtual std::string serializeSyncTalk(conversion::SyncTalk& syncTalk) const = 0;
};
