#include <model/SyncTalk.h>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

SyncTalk::SyncTalk(const capnzero::Id &senderId, std::vector<SyncData> &syncData)
        : senderId_(senderId), syncData_(syncData) {}

const std::string SyncTalk::toJson() const {
    rapidjson::Document syncTalk(rapidjson::kObjectType);

    rapidjson::Document senderId;
    senderId.Parse(senderId_.toJson().c_str());
    syncTalk.AddMember("senderId", senderId.GetObject(), syncTalk.GetAllocator());

    rapidjson::Value syncData(rapidjson::kArrayType);
    syncData.Reserve(syncData_.size(), syncTalk.GetAllocator());
    for(const auto& data: syncData_) {
        rapidjson::Document d;
        d.Parse(data.toJson().c_str());
        syncData.PushBack(d.GetObject(), syncTalk.GetAllocator());
    }
    syncTalk.AddMember("syncData", syncData, syncTalk.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    syncTalk.Accept(writer);

    return buffer.GetString();
}

SyncTalk SyncTalk::from(capnp::MessageReader& reader) {
    auto syncTalk = reader.getRoot<alica_msgs::SyncTalk>();
    if(!isValid(syncTalk)) {
        throw std::runtime_error("Invalid Sync Talk");
    }

    auto senderIdReader = syncTalk.getSenderId();
    auto senderId = capnzero::Id::from(senderIdReader);

    auto syncDataReader = syncTalk.getSyncData();
    std::vector<SyncData> syncData;
    syncData.reserve(syncDataReader.size());
    for(auto dataReader: syncDataReader) {
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

capnzero::Id SyncTalk::getSenderId() const {
    return senderId_;
}

std::vector<SyncData> SyncTalk::getSyncData() const {
    return syncData_;
}

