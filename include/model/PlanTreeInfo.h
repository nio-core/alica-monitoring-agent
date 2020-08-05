#pragma once

#include <capnp/message.h>
#include <PlanTreeInfo.capnp.h>
#include <model/capnzero/Id.h>

class PlanTreeInfo {

public:
    PlanTreeInfo(capnzero::Id &senderId, std::vector<int64_t> &stateIds,
                 std::vector<int64_t> &succeededEps);

    static PlanTreeInfo from(capnp::MessageReader &reader);

    static bool isValid(alica_msgs::PlanTreeInfo::Reader &planTreeInfo);

    capnzero::Id getSenderId();

    std::vector<int64_t> getStateIds();

    std::vector<int64_t> getSucceededEps();

    const std::string toJson() const;

private:
    capnzero::Id senderId_;
    std::vector<int64_t> stateIds_;
    std::vector<int64_t> succeededEps_;
};
