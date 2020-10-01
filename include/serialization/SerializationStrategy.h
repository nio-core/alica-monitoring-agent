#pragma once

#include <string>
#include <model/capnzero/Id.h>
#include <model/EntrypointRobots.h>
#include <model/SolverVar.h>
#include <model/SyncData.h>
#include <model/AlicaEngineInfo.h>
#include <model/AllocationAuthorityInfo.h>
#include <model/PlanTreeInfo.h>
#include <model/RoleSwitch.h>
#include <model/SolverResult.h>
#include <model/SyncReady.h>
#include <model/SyncTalk.h>

class SerializationStrategy {
public:
    virtual ~SerializationStrategy() = default;

    virtual std::string serializeCapnzeroId(model::capnzero::Id& id) const = 0;

    virtual std::string serializeEntryPointRobots(model::EntrypointRobots& entrypointRobots) const = 0;

    virtual std::string serializeSolverVar(model::SolverVar& solverVar) const = 0;

    virtual std::string serializeSyncData(model::SyncData& syncData) const = 0;

    virtual std::string serializeAlicaEngineInfo(model::AlicaEngineInfo& alicaEngineInfo) const = 0;

    virtual std::string serializeAllocationAuthorityInfo(model::AllocationAuthorityInfo& allocationAuthorityInfo) const = 0;

    virtual std::string serializePlanTreeInfo(model::PlanTreeInfo& planTreeInfo) const = 0;

    virtual std::string serializeRoleSwitch(model::RoleSwitch& roleSwitch) const = 0;

    virtual std::string serializeSolverResult(model::SolverResult& solverResult) const = 0;

    virtual std::string serializeSyncReady(model::SyncReady& syncReady) const = 0;

    virtual std::string serializeSyncTalk(model::SyncTalk& syncTalk) const = 0;
};
