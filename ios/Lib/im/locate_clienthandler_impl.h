#ifndef __LOCATE_CLIENTHANDLER_IMPL_H__
#define __LOCATE_CLIENTHANDLER_IMPL_H__

#include "locate/locate.h"

namespace rtalk {
    class Client;
}

extern void CallbackFunc(const std::string &cb, bool);

namespace rtalk_wrap
{
	class CLocateHandlerImpl : public locate::ClientHandler
	{
		friend class CRtalkClientHandlerImpl;

	public:
		static CLocateHandlerImpl& GetInstance()
		{
			static CLocateHandlerImpl s_Instance;
			return s_Instance;
		}

	public:
        void SetPosQueryOpt(double latitude, double longitude,UInt32 maxDistance, UInt32 refreshTime, UInt32 maxCountPerTime,UInt8 sex);
        int  ExecuteQuery(UInt32 countFrom);
        int  SetSex(UInt8 sex);
        int  SetLocateInfo(double latitude, double longitude,UInt8 sex);
	private:
		void ConnectToLocateServer(rtalk::Client *rtalkClient);
		void DisConnectFromServer();

	protected:
		//locate::ClientHandler implement.
		virtual void OnConnected(locate::Client *client);
		virtual void OnClosed(locate::Client *client);
        virtual void OnNearbyUserReply(UInt32 result, const UserList &users,locate::Request *request);
        virtual void OnUpdateReply(UInt32 result,locate::Request *request);
        virtual void OnCleanReply(UInt32 result,locate::Request *request);

	private:
		locate::Client *_locateClient;
		bool _bConnect;

        double _latitude;
        double _longitude;
        UInt8  _sex;

	private:
		CLocateHandlerImpl();
		CLocateHandlerImpl(const CLocateHandlerImpl &rh);
		CLocateHandlerImpl& operator=(const CLocateHandlerImpl &rh);
	};
}


#endif

