#pragma once

#include <conversion.h>

class SerializingVisitor {
public:
    virtual ~SerializingVisitor() = default;

    virtual void visitAlicaEngineInfo(conversion::AlicaEngineInfo* engineInfo) = 0;

    virtual void visitAllocationAuthorityInfo(conversion::AllocationAuthorityInfo* allocationAuthorityInfo) = 0;

    virtual void visitEntryPointRobots(conversion::EntrypointRobots* entrypointRobots) = 0;

    virtual void visitPlanTreeInfo(conversion::PlanTreeInfo* planTreeInfo) = 0;

    virtual void visitRoleSwitch(conversion::RoleSwitch* roleSwitch) = 0;

    virtual void visitSolverResult(conversion::SolverResult* solverResult) = 0;

    virtual void visitSolverVar(conversion::SolverVar* solverVar) = 0;

    virtual void visitSyncData(conversion::SyncData* syncData) = 0;

    virtual void visitSyncReady(conversion::SyncReady* syncReady) = 0;

    virtual void visitSyncTalk(conversion::SyncTalk* syncTalk) = 0;

    virtual std::string getString() const = 0;
};
