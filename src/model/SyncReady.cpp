#include <model/SyncReady.h>
#include <stdexcept>

namespace model {
    SyncReady SyncReady::from(capnp::MessageReader &reader) {
        auto syncReady = reader.getRoot<alica_msgs::SyncReady>();
        if (!syncReady.hasSenderId()) {
            throw std::runtime_error("Invalid Sync Ready");
        }

        auto senderIdReader = syncReady.getSenderId();
        auto senderId = capnzero::Id::from(senderIdReader);

        return {
                senderId,
                syncReady.getSynchronisationId()
        };
    }

    bool SyncReady::isValid(alica_msgs::SyncReady::Reader &reader) {
        return reader.hasSenderId();
    }

    SyncReady::SyncReady(const capnzero::Id &senderId, int64_t syncId) : senderId_(senderId), syncId_(syncId) {}

    capnzero::Id SyncReady::getSenderId() const {
        return senderId_;
    }

    int64_t SyncReady::getSyncId() const {
        return syncId_;
    }
}