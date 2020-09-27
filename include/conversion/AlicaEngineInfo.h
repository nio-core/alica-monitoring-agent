#pragma once

#include <capnp/serialize.h>
#include <AlicaEngineInfo.capnp.h>
#include <conversion/capnzero/Id.h>

namespace conversion {
    class AlicaEngineInfo {
    public:
        static AlicaEngineInfo from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::AlicaEngineInfo::Reader &reader);

    public:
        AlicaEngineInfo(const capnzero::Id &senderId, const std::string &masterPlan, const std::string &currentPlan,
                        const std::string &currentState, const std::string &currentRole, const std::string &currentTask,
                        const std::vector<capnzero::Id> &agentIdsWithMe);

        capnzero::Id getSenderId() const;

        std::string getMasterPlan() const;

        std::string getCurrentPlan() const;

        std::string getCurrentState() const;

        std::string getCurrentRole() const;

        std::string getCurrentTask() const;

        std::vector<capnzero::Id> getAgentIdsWithMe() const;

        const std::string toJson() const;

    private:
        capnzero::Id senderId_;
        std::string masterPlan_;
        std::string currentPlan_;
        std::string currentState_;
        std::string currentRole_;
        std::string currentTask_;
        std::vector<capnzero::Id> agentIdsWithMe_;
    };
}