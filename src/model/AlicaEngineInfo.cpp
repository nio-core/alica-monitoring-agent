#include <model/AlicaEngineInfo.h>
#include <stdexcept>

namespace model {
    AlicaEngineInfo AlicaEngineInfo::from(capnp::MessageReader &reader) {
        auto engineInfo = reader.getRoot<alica_msgs::AlicaEngineInfo>();
        if (!isValid(engineInfo)) {
            throw std::runtime_error("Invalid Alica Engine Info");
        }

        auto senderIdReader = engineInfo.getSenderId();
        capnzero::Id senderId = capnzero::Id::from(senderIdReader);
        std::string masterPlan = engineInfo.getMasterPlan();
        std::string currentPlan = engineInfo.getCurrentPlan();
        std::string currentState = engineInfo.getCurrentState();
        std::string currentRole = engineInfo.getCurrentRole();
        std::string currentTask = engineInfo.getCurrentTask();
        std::vector<capnzero::Id> agentIdsWithMe;
        for (auto agentIdReader: engineInfo.getAgentIdsWithMe()) {
            agentIdsWithMe.emplace_back(capnzero::Id::from(agentIdReader));
        }

        return AlicaEngineInfo(senderId, masterPlan, currentPlan, currentState, currentRole, currentTask,
                               agentIdsWithMe);
    }

    bool AlicaEngineInfo::isValid(alica_msgs::AlicaEngineInfo::Reader &reader) {
        return reader.hasSenderId() && reader.hasAgentIdsWithMe() && reader.hasCurrentPlan()
               && reader.hasCurrentRole() && reader.hasCurrentState() && reader.hasCurrentTask()
               && reader.hasMasterPlan();
    }

    AlicaEngineInfo::AlicaEngineInfo(const capnzero::Id &senderId, const std::string &masterPlan,
                                                 const std::string &currentPlan,
                                                 const std::string &currentState, const std::string &currentRole,
                                                 const std::string &currentTask,
                                                 const std::vector<capnzero::Id> &agentIdsWithMe)
            : senderId_(senderId), masterPlan_(masterPlan), currentPlan_(currentPlan),
              currentState_(currentState), currentRole_(currentRole), currentTask_(currentTask),
              agentIdsWithMe_(agentIdsWithMe) {

    }


    capnzero::Id AlicaEngineInfo::getSenderId() const {
        return senderId_;
    }

    std::string AlicaEngineInfo::getMasterPlan() const {
        return masterPlan_;
    }

    std::string AlicaEngineInfo::getCurrentPlan() const {
        return currentPlan_;
    }

    std::string AlicaEngineInfo::getCurrentState() const {
        return currentState_;
    }

    std::string AlicaEngineInfo::getCurrentRole() const {
        return currentRole_;
    }

    std::string AlicaEngineInfo::getCurrentTask() const {
        return currentTask_;
    }

    std::vector<capnzero::Id> AlicaEngineInfo::getAgentIdsWithMe() const {
        return agentIdsWithMe_;
    }
}