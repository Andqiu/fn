//#include "common/nsox/nulog.h"
#include "platform.hpp"
#include "locate_clienthandler_impl.h"
#include "EventMiddleLayer.h"

namespace rtalk_wrap
{
    CLocateHandlerImpl::CLocateHandlerImpl() : _locateClient(NULL)
    , _bConnect(false) ,  _latitude(0.0),
    _longitude(0.0),  _sex(0)
    {
    }

    /**
     * 建立到lcoate服務的連接，並註冊locate::ClientHandler事件回調。
     */
    void CLocateHandlerImpl::ConnectToLocateServer(rtalk::Client *rtalkClient)
    {
        if ( !rtalkClient )
        {
            return;
        }

        _locateClient = locate::ConnectLocateService(rtalkClient);
        if ( _locateClient )
        {
            _locateClient->SetHandler(this);
        }
        else
        {
            printf("connect to locate server fail.");
        }
    }


    /**
     * 斷開locate服務連接
     */
    void CLocateHandlerImpl::DisConnectFromServer()
    {
//        nsox::xlog(NsoxDebug, "disconnect from locate server.");

        if ( _locateClient )
        {
            _locateClient->SetHandler(NULL);
        }

        if ( _locateClient && _bConnect )
        {
//            _locateClient->CleanLocation();
            _locateClient->Close();
        }

        _locateClient = NULL;
        _bConnect = false;
    }
    
    void CLocateHandlerImpl::SetPosQueryOpt(double latitude, double longitude,UInt32 maxDistance, UInt32 refreshTime, UInt32 maxCountPerTime,UInt8 sex)
    {
        if ( !_locateClient )
        {
            printf("Locate Service SetPosQueryOpt failed \n");
            return;
        }
        printf("Locate Service SetPosQueryOpt successful \n");

        _locateClient->SetMaxCount(maxCountPerTime);
        _locateClient->SetMaxDistance(maxDistance);
        _locateClient->SetMaxTime(refreshTime);
        _locateClient->SetPosition(latitude, longitude);
        _locateClient->SetQuerySex(sex);
    }
    
    int CLocateHandlerImpl::ExecuteQuery(UInt32 countFrom)
    {
        if ( !_locateClient
            || !_bConnect )
        {
            
            return -1;
        }
        
        locate::Request* request = _locateClient->QueryNearbyUser(countFrom);
        if(request == NULL)
            return -1;
        
        return request->GetId();
    }
    
    int CLocateHandlerImpl::SetSex(UInt8 sex)
    {
        if ( !_locateClient || !_bConnect)
        {
            return -1;
        }
        
        locate::Request* request = _locateClient->UploadInfo(sex);

        if(request == NULL)
            return -1;

        return request->GetId();
    }


    int CLocateHandlerImpl::SetLocateInfo(double latitude, double longitude, UInt8 sex)
    {
        _latitude = latitude;
        _longitude = longitude;
        _sex = sex;
        
        if ( !_locateClient || !_bConnect)
        {
            printf("Locate Service SetLocateInfo failed \n");
            return -1;
        }
        printf("Locate Service SetLocateInfo successful %f %f \n",_latitude,_longitude);
        
        _locateClient->SetPosition(latitude, longitude);
        locate::Request* request = _locateClient->UploadInfo(sex);
        
        if(request == NULL)
            return -1;
        
        return request->GetId();
    }
    /**
     * locate服務連接成功通知。
     */
    void CLocateHandlerImpl::OnConnected(locate::Client *client)
    {
        printf("Locate Service onConnected \n");
        _bConnect = true;
        
        if(_latitude != 0.0 && _longitude != 0.0)
            SetLocateInfo(_latitude,_longitude,_sex);

        CLocateEventMiddile::getInstance().OnConnected();
    }

    /**
     * lcoate服務連接關閉通知。
     */
    void CLocateHandlerImpl::OnClosed(locate::Client *client)
    {
        printf("Locate Service OnClosed \n");
        
        if (_locateClient) {
            _locateClient->SetHandler(NULL);
        }
        
        _bConnect = false;
        _locateClient = NULL;

        CLocateEventMiddile::getInstance().OnClose();
    }

    /**
     * lcoate查詢結果回調，返回附近的人。
     */
    void CLocateHandlerImpl::OnNearbyUserReply(UInt32 result,const UserList &users, locate::Request* request)
    {
        printf("Locate Service OnNearByUserReply  user size is %d \n", (int)users.size());
        CLocateEventMiddile::getInstance().OnNearbyUserReply(result, users, request->GetId());
    }

    void CLocateHandlerImpl::OnUpdateReply(UInt32 result, locate::Request* request)
    {
        printf("Locate Service OnUpdateReply %u \n",(unsigned int)result);
        CLocateEventMiddile::getInstance().OnUpdateReply(result, request->GetId());
    }

    void CLocateHandlerImpl::OnCleanReply(UInt32 result, locate::Request* request)
    {
        printf("Locate Service OnCleanReply， result = %u \n", (unsigned int)result);
        CLocateEventMiddile::getInstance().OnCleanReply(result, request->GetId());
    }

}






