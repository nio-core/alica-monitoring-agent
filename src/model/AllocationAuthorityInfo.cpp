#include <AllocationAuthorityInfo.capnp.h>
#include <stdexcept>
#include <model/EntrypointRobots.h>
#include <model/AllocationAuthorityInfo.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <rapidjson/writer.h>

AllocationAuthorityInfo::AllocationAuthorityInfo(capnzero::Id &senderId, int64_t planId, int64_t parentState,
                                                 int64_t planType, capnzero::Id &authority,
                                                 std::vector<EntrypointRobots> &entrypointRobots)
        : senderId_(senderId), planId_(planId), parentState_(parentState), planType_(planType), authority_(authority),
          entrypointRobots_(entrypointRobots) {

}

AllocationAuthorityInfo AllocationAuthorityInfo::from(capnp::MessageReader &reader) {
    auto allocationAuthorityInfo = reader.getRoot<alica_msgs::AllocationAuthorityInfo>();
    if(!isValid(allocationAuthorityInfo)) {
        throw std::runtime_error("Invalid Allocation Authority");
    }

    auto senderIdReader = allocationAuthorityInfo.getSenderId();
    auto senderId = capnzero::Id::from(senderIdReader);
    auto authorityReader = allocationAuthorityInfo.getAuthority();
    auto authority = capnzero::Id::from(authorityReader);
    std::vector<EntrypointRobots> entrypointRobots;
    for(auto entrypointRobot: allocationAuthorityInfo.getEntrypointRobots()) {
        entrypointRobots.emplace_back(EntrypointRobots::from(entrypointRobot));
    }

    return {
            senderId,
            allocationAuthorityInfo.getPlanId(),
            allocationAuthorityInfo.getParentState(),
            allocationAuthorityInfo.getPlanType(),
            authority,
            entrypointRobots
    };
}

bool AllocationAuthorityInfo::isValid(alica_msgs::AllocationAuthorityInfo::Reader& allocationAuthorityInfo) {
    return allocationAuthorityInfo.hasAuthority() && allocationAuthorityInfo.hasSenderId() && allocationAuthorityInfo.hasEntrypointRobots();
}

capnzero::Id AllocationAuthorityInfo::getSenderId() const {
    return senderId_;
}

int64_t AllocationAuthorityInfo::getPlanId() const {
    return planId_;
}

int64_t AllocationAuthorityInfo::getParentState() const {
    return parentState_;
}

int64_t AllocationAuthorityInfo::getPlanType() const {
    return planType_;
}

capnzero::Id AllocationAuthorityInfo::getAuthority() const {
    return authority_;
}

std::vector<EntrypointRobots> &AllocationAuthorityInfo::getEntrypointRobots() {
    return entrypointRobots_;
}

const std::string AllocationAuthorityInfo::toJson() const {
    rapidjson::Document allocationAuthorityInfo(rapidjson::kObjectType);

    allocationAuthorityInfo.AddMember("parentState", parentState_, allocationAuthorityInfo.GetAllocator());
    allocationAuthorityInfo.AddMember("planType", planType_, allocationAuthorityInfo.GetAllocator());
    allocationAuthorityInfo.AddMember("planId", planId_, allocationAuthorityInfo.GetAllocator());

    rapidjson::Document authority;
    authority.Parse(authority_.toJson().c_str());
    allocationAuthorityInfo.AddMember("authority", authority.GetObject(), allocationAuthorityInfo.GetAllocator());

    rapidjson::Document senderId;
    senderId.Parse(senderId_.toJson().c_str());
    allocationAuthorityInfo.AddMember("senderId", senderId.GetObject(), allocationAuthorityInfo.GetAllocator());

    rapidjson::Document entrypointRobot;
    rapidjson::Value entrypointRobots(rapidjson::kArrayType);
    for(const auto& epr: entrypointRobots_) {
        entrypointRobot.Parse(epr.toJson().c_str());
        entrypointRobots.PushBack(entrypointRobot.GetObject(), allocationAuthorityInfo.GetAllocator());
    }
    allocationAuthorityInfo.AddMember("entrypointRobots", entrypointRobots, allocationAuthorityInfo.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    allocationAuthorityInfo.Accept(writer);

    return buffer.GetString();
}
