#ifndef __RTALK_CHAT_IMPL_H__
#define __RTALK_CHAT_IMPL_H__


#include "platform.hpp"
#include "chat/chat.h"

extern void CallbackFunc(const std::string &cb, bool);

namespace rtalk_wrap
{
	class CChatSubscribeHandlerImpl;
	class CChatRosterHandlerImpl;
	class CRtalkClientHandlerImpl;

	class CChatClientHandlerImpl : chat::ClientHandler,
	chat::RequestHandler
	{
		friend class CChatSubscribeHandlerImpl;

		typedef std::map<UInt32, CChatSubscribeHandlerImpl*> SubscribeHandlerMap;

	public:
		static CChatClientHandlerImpl& GetInstance()
		{
			static CChatClientHandlerImpl s_Instance;
			return s_Instance;
		}
        
		void Create(rtalk::Client *rtalkClient);
		void Destroy();
		virtual ~CChatClientHandlerImpl();

		//chat::Client
		UInt32 SetName(const std::string &name);
		UInt32 SetPresence(UInt8 status, const std::string &show);
		int ForwardMessage(UInt32 userId, UInt8 type, const std::string &body,const std::string &subject);
        
        /// 上报撤回消息
        int withdrawMessageFeedback(const std::string &body);
        
		UInt32 SendSubscribe(UInt32 userId, const std::string &name, const std::string &remark, chat::RosterGroup *group, const std::string &greeting);
		UInt32 SendIQ(UInt32 userId, const std::string &name, const std::string &method, const std::string &content);
        void SetOffMsgId(UInt64 msgId);
        bool IsConnect() const;

	private:
		void OnRemoveSubscribe(CChatSubscribeHandlerImpl *subscribe);

	protected:
		virtual void OnConnected(chat::Client *client);

		virtual void OnClosed(chat::Client *client);

        virtual void OnMessage(UInt32 userId, const std::string &name,
                               UInt8 type,
                               UInt32 timestamp,
                               const std::string &body,
                               const std::string &info,
                               bool isOffline,
                               UInt64 msgId,
                               UInt32 riskStatus,
                               chat::Client *client);

		virtual void OnSubscribe(chat::Subscribe *subscribe, const std::string &greeting, chat::Client *client);

		virtual void OnIQ(UInt32 userId, const std::string &name, const std::string &method, const std::string &content, chat::Client *client);

		virtual void OnAccepted(chat::RosterItem *rosterItem,chat::Client *client);

		virtual void OnRejected(UInt32 userId, const std::string &name, const std::string &reason,chat::Client *client);

		///////////////////////////////////RequestHandler////////////////////////////////
		virtual void OnRequestResult(UInt32 type, UInt32 requestId, UInt32 reason);
	private:
		chat::Client *chatClient_;
		bool bConnect_;
		SubscribeHandlerMap subscribeHandlers_;
		int subscribeIndex_;


	private:
		CChatClientHandlerImpl();
		CChatClientHandlerImpl(const CChatClientHandlerImpl& rh);
		CChatClientHandlerImpl& operator=(const CChatClientHandlerImpl& rh);
	};
}


#endif

