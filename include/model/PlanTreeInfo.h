#pragma once

#include <capnp/message.h>
#include <PlanTreeInfo.capnp.h>
#include <model/capnzero/Id.h>

namespace model {
    class PlanTreeInfo {
    public:
        static PlanTreeInfo from(capnp::MessageReader &reader);

        static bool isValid(alica_msgs::PlanTreeInfo::Reader &planTreeInfo);

    public:
        PlanTreeInfo(capnzero::Id &senderId, std::vector<int64_t> &stateIds,
                     std::vector<int64_t> &succeededEps);

        capnzero::Id getSenderId() const;

        std::vector<int64_t> getStateIds() const;

        std::vector<int64_t> getSucceededEps() const;

    private:
        capnzero::Id senderId_;
        std::vector<int64_t> stateIds_;
        std::vector<int64_t> succeededEps_;
    };
}