#pragma once

#include <conversion.h>

class StringificationVisitor {
public:
    virtual ~StringificationVisitor() = default;

    virtual void visitAlicaEngineInfo(AlicaEngineInfo* engineInfo) = 0;

    virtual void visitAllocationAuthorityInfo(AllocationAuthorityInfo* allocationAuthorityInfo) = 0;

    virtual void visitEntryPointRobots(EntrypointRobots* entrypointRobots) = 0;

    virtual void visitPlanTreeInfo(PlanTreeInfo* planTreeInfo) = 0;

    virtual void visitRoleSwitch(RoleSwitch* roleSwitch) = 0;

    virtual void visitSolverResult(SolverResult* solverResult) = 0;

    virtual void visitSolverVar(SolverVar* solverVar) = 0;

    virtual void visitSyncData(SyncData* syncData) = 0;

    virtual void visitSyncReady(SyncReady* syncReady) = 0;

    virtual void visitSyncTalk(SyncTalk* syncTalk) = 0;

    virtual std::string getString() const = 0;
};
