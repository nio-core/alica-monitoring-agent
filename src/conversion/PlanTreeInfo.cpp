#include <conversion/PlanTreeInfo.h>
#include <stdexcept>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

PlanTreeInfo PlanTreeInfo::from(capnp::MessageReader &reader) {
    auto planTreeInfo = reader.getRoot<alica_msgs::PlanTreeInfo>();
    if(!isValid(planTreeInfo)) {
        throw std::runtime_error("Invalid Plan Tree Info");
    }

    auto senderIdReader = planTreeInfo.getSenderId();
    auto senderId = capnzero::Id::from(senderIdReader);

    auto stateIdsReader = planTreeInfo.getStateIds();
    std::vector<int64_t> stateIds;
    stateIds.reserve(stateIdsReader.size());
    for(auto stateId: stateIdsReader) {
        stateIds.emplace_back(stateId);
    }

    auto succeededEpsReader = planTreeInfo.getSucceededEps();
    std::vector<int64_t> succeededEps;
    succeededEps.reserve(succeededEpsReader.size());
    for(auto stateId: succeededEpsReader) {
        succeededEps.emplace_back(stateId);
    }

    return {
        senderId,
        stateIds,
        succeededEps
    };
}

bool PlanTreeInfo::isValid(alica_msgs::PlanTreeInfo::Reader &planTreeInfo) {
    return planTreeInfo.hasSenderId() && planTreeInfo.hasStateIds() && planTreeInfo.hasSucceededEps();
}

capnzero::Id PlanTreeInfo::getSenderId() const {
    return senderId_;
}

PlanTreeInfo::PlanTreeInfo(capnzero::Id &senderId, std::vector<int64_t> &stateIds,
                           std::vector<int64_t> &succeededEps)
        : senderId_(senderId), stateIds_(stateIds), succeededEps_(succeededEps) {}

std::vector<int64_t> PlanTreeInfo::getStateIds() const {
    return stateIds_;
}

std::vector<int64_t> PlanTreeInfo::getSucceededEps() const {
    return succeededEps_;
}

const std::string PlanTreeInfo::toJson() const {
    rapidjson::Document planTreeInfo(rapidjson::kObjectType);

    rapidjson::Document senderId;
    senderId.Parse(senderId_.toJson().c_str());
    planTreeInfo.AddMember("senderId", senderId.GetObject(), planTreeInfo.GetAllocator());

    rapidjson::Value stateIds(rapidjson::kArrayType);
    stateIds.Reserve(stateIds_.size(), planTreeInfo.GetAllocator());
    for(auto stateId: stateIds_) {
        stateIds.PushBack(stateId, planTreeInfo.GetAllocator());
    }
    planTreeInfo.AddMember("stateIds", stateIds, planTreeInfo.GetAllocator());

    rapidjson::Value succeededEps(rapidjson::kArrayType);
    succeededEps.Reserve(succeededEps_.size(), planTreeInfo.GetAllocator());
    for(auto succeededEp: succeededEps_) {
        succeededEps.PushBack(succeededEp, planTreeInfo.GetAllocator());
    }
    planTreeInfo.AddMember("succeededEps", succeededEps, planTreeInfo.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    planTreeInfo.Accept(writer);

    return buffer.GetString();


}
