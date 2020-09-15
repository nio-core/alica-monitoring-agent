#include <conversion/AlicaEngineInfo.h>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

AlicaEngineInfo AlicaEngineInfo::from(capnp::MessageReader &reader) {
    auto engineInfo = reader.getRoot<alica_msgs::AlicaEngineInfo>();
    if(!isValid(engineInfo)) {
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
    for(auto agentIdReader: engineInfo.getAgentIdsWithMe()) {
        agentIdsWithMe.emplace_back(capnzero::Id::from(agentIdReader));
    }

    return AlicaEngineInfo(senderId, masterPlan, currentPlan, currentState, currentRole, currentTask, agentIdsWithMe);
}

bool AlicaEngineInfo::isValid(alica_msgs::AlicaEngineInfo::Reader& reader) {
    return reader.hasSenderId() && reader.hasAgentIdsWithMe() && reader.hasCurrentPlan()
        && reader.hasCurrentRole() && reader.hasCurrentState() && reader.hasCurrentTask()
        && reader.hasMasterPlan();
}

AlicaEngineInfo::AlicaEngineInfo(const capnzero::Id &senderId, const std::string &masterPlan, const std::string &currentPlan,
                                 const std::string &currentState, const std::string &currentRole, const std::string &currentTask,
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

const std::string AlicaEngineInfo::toJson() const {
    rapidjson::Document engineInfo(rapidjson::kObjectType);
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value val;

    rapidjson::Document senderId;
    senderId.Parse(senderId_.toJson().c_str());
    engineInfo.AddMember("senderId", senderId.GetObject(), engineInfo.GetAllocator());

    val.SetString(currentPlan_.c_str(), currentPlan_.size());
    engineInfo.AddMember("currentPlan", val, engineInfo.GetAllocator());

    val.SetString(masterPlan_.c_str(), masterPlan_.size());
    engineInfo.AddMember("masterPlan", val, engineInfo.GetAllocator());

    val.SetString(currentState_.c_str(), currentState_.size());
    engineInfo.AddMember("currentState", val, engineInfo.GetAllocator());

    val.SetString(currentRole_.c_str(), currentRole_.size());
    engineInfo.AddMember("currentRole", val, engineInfo.GetAllocator());

    val.SetString(currentTask_.c_str(), currentTask_.size());
    engineInfo.AddMember("currentTask", val, engineInfo.GetAllocator());

    rapidjson::Document a;
    for(const auto& agent: agentIdsWithMe_) {
        a.Parse(agent.toJson().c_str());
        array.PushBack(a, engineInfo.GetAllocator());
    }
    engineInfo.AddMember("agentIdsWithMe", array, engineInfo.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    engineInfo.Accept(writer);

    return buffer.GetString();
}
