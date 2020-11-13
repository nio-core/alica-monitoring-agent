#include <model/SyncTalk.h>
#include <string>
#include <stdexcept>

namespace model {
    SyncTalk SyncTalk::from(capnp::MessageReader &reader) {
        auto syncTalk = reader.getRoot<alica_msgs::SyncTalk>();
        if (!isValid(syncTalk)) {
            throw std::runtime_error("Invalid Sync Talk");
        }

        auto senderIdReader = syncTalk.getSenderId();
        auto senderId = capnzero::Id::from(senderIdReader);

        auto syncDataReader = syncTalk.getSyncData();
        std::vector<SyncData> syncData;
        syncData.reserve(syncDataReader.size());
        for (auto dataReader: syncDataReader) {
            syncData.emplace_back(SyncData::from(dataReader));
        }

        return {
                senderId,
                syncData
        };
    }

    bool SyncTalk::isValid(alica_msgs::SyncTalk::Reader &syncTalk) {
        return syncTalk.hasSyncData() && syncTalk.hasSenderId();
    }

    SyncTalk::SyncTalk(const capnzero::Id &senderId, std::vector<SyncData> &syncData)
            : senderId_(senderId), syncData_(syncData) {}

    capnzero::Id SyncTalk::getSenderId() const {
        return senderId_;
    }

    std::vector<SyncData> SyncTalk::getSyncData() const {
        return syncData_;
    }
}