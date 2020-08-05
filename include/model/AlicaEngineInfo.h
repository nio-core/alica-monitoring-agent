#pragma once

#include <capnp/serialize.h>
#include <AlicaEngineInfo.capnp.h>
#include <model/capnzero/Id.h>

class AlicaEngineInfo {

public:
    AlicaEngineInfo(const capnzero::Id &senderId, const std::string &masterPlan, const std::string &currentPlan,
                    const std::string &currentState, const std::string &currentRole, const std::string &currentTask,
                    const std::vector<capnzero::Id> &agentIdsWithMe);

    static AlicaEngineInfo from(capnp::MessageReader& reader);

    static bool isValid(alica_msgs::AlicaEngineInfo::Reader reader);

    capnzero::Id getSenderId();

    std::string getMasterPlan();

    std::string getCurrentPlan();

    std::string getCurrentState();

    std::string getCurrentRole();

    std::string getCurrentTask();

    std::vector<capnzero::Id> getAgentIdsWithMe();

    const std::string toJson();

private:
    capnzero::Id senderId_;
    std::string masterPlan_;
    std::string currentPlan_;
    std::string currentState_;
    std::string currentRole_;
    std::string currentTask_;
    std::vector<capnzero::Id> agentIdsWithMe_;
};
