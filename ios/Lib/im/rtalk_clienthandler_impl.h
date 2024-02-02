#ifndef __IM_CHAT_H__
#define __IM_CHAT_H__
#include "platform.hpp"
#include "chat/chat.h"
#include <sys/timeb.h>
#include <stdlib.h>

extern void CallbackFunc(const std::string &cb, bool);

namespace rtalk_wrap
{
	class CChatClientHandlerImpl;
	class CRtalkClientHandlerImpl : public rtalk::ClientHandler
	{
	public:
		static CRtalkClientHandlerImpl& GetInstance()
		{
			static CRtalkClientHandlerImpl s_Instance;
			return s_Instance;
		}

		virtual ~CRtalkClientHandlerImpl();

	public:
		//登录相关
        void Login(UInt32 loginType,
                   const std::string& ip,
                   const std::string& account,
                   const std::string& pwd,
                   const std::string &version,
                   entryp::Login::Params params,
                   UInt32 timeOut);

		void Logout();
        
        bool CreateIMService();
        
		void Keeplive();
        
        void Stop();

		//個人信息
		UInt32 GetUserId();
		UInt32 GetSex();
        std::string GetHeadImg();
		std::string GetNick();
		std::string GetToken();
		std::string GetPersonInfo();

		bool GetProperty(const std::string &key, std::string &value);

		const rtalk::Client* GetRtalkClient() const;
        
        bool IsDataValid();
        
        int SetDeviceToken(const std::string &deviceToken);
        
        std::string Stats(); // 上报信息
        
        //初始化底层全局服务器配置
        int InitGlobalServerCfg(const std::string& jsonCfg);
        
        //更新ipv6的检测
        void DetectLocalIPStack();

	protected:
		//rtalk::ClientHandler接口的實現，詳細說明請參考headers/chat/chat.h
		virtual void OnLoginSuccess(rtalk::Client *client);
		virtual void OnLoginFailed(UInt32 reason, rtalk::Client *client);
		virtual void OnDisconnect(UInt32 reason,  rtalk::Client *client);
        virtual void OnSetPropertyResult(UInt32 context, UInt32 result, rtalk::Client *client);

	private:
		bool		  _bConnect;
		rtalk::Client *_rtalkClient;
		bool           _canProxy;

		/////////////////////////////////////////////////////////

	private:
		CRtalkClientHandlerImpl();
		CRtalkClientHandlerImpl(const CRtalkClientHandlerImpl& rh);
		CRtalkClientHandlerImpl& operator= (const CRtalkClientHandlerImpl& rh);

		//調試用的數據
	private:
		struct timeval _startTime;
        enum ERtalkStatus{ //暂时不需要管理太多状态
            E_Rtalk_Status_logining,
            E_Rtalk_Status_logout,
        };
        
        ERtalkStatus _rtalkStatus;
        int          _reloginTime;
        
        std::string  _info;
        int          _loginType;
	};
}



#endif

