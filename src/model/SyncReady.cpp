#include <model/SyncReady.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <SyncReady.capnp.h>

SyncReady::SyncReady(const capnzero::Id &senderId, int64_t syncId) : senderId_(senderId), syncId_(syncId) {}

const std::string SyncReady::toJson() const {
    rapidjson::Document syncReady(rapidjson::kObjectType);

    rapidjson::Document senderId;
    senderId.Parse(senderId_.toJson().c_str());
    syncReady.AddMember("senderId", senderId.GetObject(), syncReady.GetAllocator());
    syncReady.AddMember("synchronisationId", syncId_, syncReady.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    syncReady.Accept(writer);

    return buffer.GetString();
}

SyncReady SyncReady::from(capnp::MessageReader &reader) {
    auto syncReady = reader.getRoot<alica_msgs::SyncReady>();
    if(!syncReady.hasSenderId()) {
        throw std::runtime_error("Invalid Sync Ready");
    }

    auto senderIdReader = syncReady.getSenderId();
    auto senderId = capnzero::Id::from(senderIdReader);

    return {
        senderId,
        syncReady.getSynchronisationId()
    };
}

capnzero::Id SyncReady::getSenderId() const {
    return senderId_;
}

int64_t SyncReady::getSyncId() const {
    return syncId_;
}
