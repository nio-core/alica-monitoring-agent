#pragma once

#include <capnp/serialize.h>
#include <conversion//capnzero/Id.h>
#include <conversion/EntrypointRobots.h>

namespace conversion {

    class AllocationAuthorityInfo {
    public:
        static AllocationAuthorityInfo from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::AllocationAuthorityInfo::Reader &reader);

    public:
        AllocationAuthorityInfo(capnzero::Id &senderId, int64_t planId, int64_t parentState,
                                int64_t planType, capnzero::Id &authority,
                                std::vector<conversion::EntrypointRobots> &entrypointRobots);

        capnzero::Id getSenderId() const;

        int64_t getPlanId() const;

        int64_t getParentState() const;

        int64_t getPlanType() const;

        capnzero::Id getAuthority() const;

        std::vector<EntrypointRobots> getEntrypointRobots() const;

        const std::string toJson() const;

    private:
        capnzero::Id senderId_;
        int64_t planId_;
        int64_t parentState_;
        int64_t planType_;
        capnzero::Id authority_;
        std::vector<EntrypointRobots> entrypointRobots_;
    };
}