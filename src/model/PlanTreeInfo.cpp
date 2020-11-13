#include <model/PlanTreeInfo.h>
#include <stdexcept>

namespace model {
    PlanTreeInfo PlanTreeInfo::from(capnp::MessageReader &reader) {
        auto planTreeInfo = reader.getRoot<alica_msgs::PlanTreeInfo>();
        if (!isValid(planTreeInfo)) {
            throw std::runtime_error("Invalid Plan Tree Info");
        }

        auto senderIdReader = planTreeInfo.getSenderId();
        auto senderId = capnzero::Id::from(senderIdReader);

        auto stateIdsReader = planTreeInfo.getStateIds();
        std::vector<int64_t> stateIds;
        stateIds.reserve(stateIdsReader.size());
        for (auto stateId: stateIdsReader) {
            stateIds.emplace_back(stateId);
        }

        auto succeededEpsReader = planTreeInfo.getSucceededEps();
        std::vector<int64_t> succeededEps;
        succeededEps.reserve(succeededEpsReader.size());
        for (auto stateId: succeededEpsReader) {
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
}