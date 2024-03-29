#include <model/AllocationAuthorityInfo.h>
#include <stdexcept>

namespace model {
    AllocationAuthorityInfo AllocationAuthorityInfo::from(capnp::MessageReader &reader) {
        auto allocationAuthorityInfo = reader.getRoot<alica_msgs::AllocationAuthorityInfo>();
        if (!isValid(allocationAuthorityInfo)) {
            throw std::runtime_error("Invalid Allocation Authority");
        }

        auto senderIdReader = allocationAuthorityInfo.getSenderId();
        auto senderId = capnzero::Id::from(senderIdReader);
        auto authorityReader = allocationAuthorityInfo.getAuthority();
        auto authority = capnzero::Id::from(authorityReader);
        std::vector<EntrypointRobots> entrypointRobots;
        for (auto entrypointRobot: allocationAuthorityInfo.getEntrypointRobots()) {
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

    bool AllocationAuthorityInfo::isValid(alica_msgs::AllocationAuthorityInfo::Reader &reader) {
        return reader.hasAuthority() && reader.hasSenderId() && reader.hasEntrypointRobots();
    }

    AllocationAuthorityInfo::AllocationAuthorityInfo(capnzero::Id &senderId, int64_t planId,
                                                                 int64_t parentState,
                                                                 int64_t planType, capnzero::Id &authority,
                                                                 std::vector<EntrypointRobots> &entrypointRobots)
            : senderId_(senderId), planId_(planId), parentState_(parentState), planType_(planType),
              authority_(authority),
              entrypointRobots_(entrypointRobots) {

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

    std::vector<EntrypointRobots> AllocationAuthorityInfo::getEntrypointRobots() const {
        return entrypointRobots_;
    }
}