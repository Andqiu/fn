//#include "common/nsox/nulog.h"
#include "chat_clienthandler_impl.h"
#include "arc/arc.h"
#include "EventMiddleLayer.h"

namespace rtalk_wrap
{

    CChatClientHandlerImpl::CChatClientHandlerImpl() : chatClient_(NULL)
        , bConnect_(false)
    {

    }

    CChatClientHandlerImpl::~CChatClientHandlerImpl()
    {
        Destroy();
    }

    /**
     * 建立chat服務，並註冊chat::ClientHandler事件回調。
     */
    void CChatClientHandlerImpl::Create(rtalk::Client *rtalkClient)
    {
        if (chatClient_ || rtalkClient == NULL) {
            return;
        }
        
        chatClient_ = chat::ConnectChatService(rtalkClient);
        
        if (chatClient_) {
            chatClient_->SetHandler(this);
            chatClient_->SetRequestHandler(this);
            CIMEventMiddle::getInstance().onIMCreated();
        }
    }

    void CChatClientHandlerImpl::Destroy()
    {
        if (chatClient_) {
            chatClient_->SetHandler(NULL);
            chatClient_->SetRequestHandler(NULL);
        }

        bConnect_ = false;
        chatClient_ = NULL;
        subscribeHandlers_.clear();
    }

    /**
     * chat服務連接成功回調，可以在這個回調裏面通過參數中的client來拿到好友及好友分組的數據。
     */
    void CChatClientHandlerImpl::OnConnected(chat::Client *client)
    {
        bConnect_ = true;

        CIMEventMiddle::getInstance().onIMConnectSuccess();
    }

    /**
     * chat連接斷開後，OnConnected中保存的數據要清掉，並且通知上層的邏輯服務已斷開，不應該再使用該服務。
     */
    void CChatClientHandlerImpl::OnClosed(chat::Client *client)
    {
        Destroy();

        CIMEventMiddle::getInstance().onIMConnectClose();
    }

    /**
     * 收到陌生人消息的回調，通知上層UI處理。
     * remark:友好的消息回調會在RosterItemHandler::OnMessage裏面通知，注意區分這一點。
     */
    void CChatClientHandlerImpl::OnMessage(UInt32 userId,
                                           const std::string &name,
                                           UInt8 type,
                                           UInt32 timestamp,
                                           const std::string &body,
                                           const std::string &info,
                                           bool isOffline,
                                           UInt64 msgId,
                                           UInt32 riskStatus,
                                           chat::Client *client)
    {
        CIMEventMiddle::getInstance().onMessage(userId,
                                                name,
                                                type,
                                                timestamp,
                                                body,
                                                info,
                                                isOffline,
                                                msgId,
                                                riskStatus);
    }

    /**
     * 收到好友請求
     */
    void CChatClientHandlerImpl::OnSubscribe(chat::Subscribe *subscribe, const std::string &greeting, chat::Client *client)
    {
    }

    void CChatClientHandlerImpl::OnIQ(UInt32 userId, const std::string &name, const std::string &meth, const std::string &content,chat::Client *client)
    {
        //TODO
//        json::Variant cb;
//
//        cb["callback_type"] = CALLBACK_TYPE_IM;
//        cb["method"] = METHOD_onIQ;
//        cb["method_name"] = "chat_onIQ";
//        cb["uid"] = userId;
//        cb["name"] = name;
//        cb["conntent"] = content;
//        CallbackFunc(cb.ToString(), true);
    }

    /**
     * 請求加別人為好友，別人同意好友請求的回調
     */
    void CChatClientHandlerImpl::OnAccepted(chat::RosterItem *rosterItem,chat::Client *client)
    {
        //TODO
//        json::Variant cb;
//        cb["callback_type"] = CALLBACK_TYPE_IM;
//        cb["method"] = METHOD_onSubscribeMessage;
//        cb["method_name"] = "subscribe_onaccepted";
//        cb["uid"] = rosterItem->GetUserId();
//        cb["name"] = rosterItem->GetRemark();
//        cb["greeting"] = "";
//        cb["sub_type"] = Subscribe_SubType_Accepted;
//        cb["reason"] = "";
//
//        CallbackFunc(cb.ToString(), true);
    }

    /**
     * 請求加別人為好友，但被別人拒絕了的回調。
     */
    void CChatClientHandlerImpl::OnRejected(UInt32 userId, const std::string &name, const std::string &reason,chat::Client *client)
    {
        //TODO
//        json::Variant cb;
//        cb["callback_type"] = CALLBACK_TYPE_IM;
//        cb["method"] = METHOD_onSubscribeMessage;
//        cb["method_name"] = "subscribe_onrejected";
//        cb["uid"] = userId;
//        cb["name"] = name;
//        cb["greeting"] = "";
//        cb["sub_type"] = Subscribe_SubType_Rejected;
//        cb["reason"] = reason;
//
//        CallbackFunc(cb.ToString(), true);
    }


    void CChatClientHandlerImpl::OnRequestResult(UInt32 type, UInt32 requestId, UInt32 reason)
    {
        //TODO
//        json::Variant cb;
//        cb["request_id"] = requestId;
//        cb["callback_type"] = CALLBACK_REQUEST_RESULT;
//        cb["method"] = METHOD_OnRequestResult;
//        cb["method_name"] = "OnRequestResult_CChatClientHandlerImpl";
//        cb["reason"] = reason;
//        cb["request_id"] = requestId;
//        cb["type"] = type;
//        CallbackFunc(cb.ToString(), true);
        
        //ClientRequest
        CIMEventMiddle::getInstance().onRequestResult(type, requestId, reason);
    }

    /**
     * 設置自己的暱稱
     */
    UInt32 CChatClientHandlerImpl::SetName(const std::string &name)
    {
        if ( !chatClient_
            || !bConnect_ )
        {
            printf("please create chat client instance or connect to server first");
            return 0;
        }

        return chatClient_->SetName(name);
    }

    /**
     * 設置自己的在線狀態
     * remark:這個函數有向別人廣播消息的功能，不限於自己在線狀態的設置。
     */
    UInt32 CChatClientHandlerImpl::SetPresence(UInt8 status, const std::string &show)
    {
        return -1;
    }

    /**
     * 向陌生人發送消息
     * remark:向好友發送消息是通過RosterItem::ForwardMessage來發送，注意區分這一點。只要type > 0x10，我们都可以自定义消息。
     */
    int CChatClientHandlerImpl::ForwardMessage(UInt32 userId, UInt8 type, const std::string &body, const std::string& subject)
    {
        if ( !chatClient_ || !bConnect_ )
        {
            printf("please create chat client instance or connect to server first");
            return -1;
        }

        printf("ForwardMessage userId = %u, type = %d, body = %s\n", userId, type, body.c_str());

        return chatClient_->ForwardMessage(userId, type, body,subject);
    }

    int CChatClientHandlerImpl::withdrawMessageFeedback(const std::string &body)
    {
        if ( !chatClient_ || !bConnect_ ) {
            printf("please create chat client instance or connect to server first");
            return -1;
        }
        
        printf("WithdrawMessageFeedback: %s\n", body.c_str());

        return chatClient_->WithdrawMessageFeedback(body);
    }

    /**
     * 發送好友請求
     */
    UInt32 CChatClientHandlerImpl::SendSubscribe(UInt32 userId, const std::string &name, const std::string &remark, chat::RosterGroup *group, const std::string &greeting)
    {
        if ( !chatClient_
            || !bConnect_
            || !group )
        {
            printf("please create chat client instance or connect to server first");
            return 0;
        }

        printf("chatClient_->SendSubscribe uid = %d, greeting = %s name = %s ", userId,  greeting.c_str(), name.c_str());
        return chatClient_->SendSubscribe(userId, name, remark, group, greeting);
    }

    UInt32 CChatClientHandlerImpl::SendIQ(UInt32 userId, const std::string &name, const std::string &method, const std::string &content)
    {
        if ( !chatClient_ || !bConnect_)
        {
            printf("please create chat client instance or connect to server first");
            return -1;
        }

        return chatClient_->SendIQ(userId, name, method, content);
    }

    void CChatClientHandlerImpl::SetOffMsgId(UInt64 msgId)
    {
        if (chatClient_) {
            chatClient_->SetOffMsgId(msgId);
        }
    }

    bool CChatClientHandlerImpl::IsConnect() const
    {
        return bConnect_;
    }

    /**
     * 刪除（更新）好友請求列表
     */
    void CChatClientHandlerImpl::OnRemoveSubscribe(CChatSubscribeHandlerImpl *subscribe)
    {
        SubscribeHandlerMap::iterator it = subscribeHandlers_.begin();
        for ( ; it != subscribeHandlers_.end(); ++it )
        {
            if ( it->second == subscribe )
            {
                subscribeHandlers_.erase(it);
                break;
            }
        }
    }

}




