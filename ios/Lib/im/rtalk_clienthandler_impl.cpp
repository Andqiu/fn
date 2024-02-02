//#include "common/nsox/nulog.h"
#include "rtalk_clienthandler_impl.h"
#include "arc/arc.h"
#include "chat_clienthandler_impl.h"
#include "chatp/chatp.h"
#include "EventMiddleLayer.h"
#include "locate_clienthandler_impl.h"


//void logger(const std::string &name, const std::string &level, const std::string &context, const char *format, va_list args)
//{
//    char    buf[1024 + 1];
//    VSPRINTF(buf, 1024, format, args);        /* safe */
//    printf("rtalk name = %s, level = %s, context = %s, args = %s", name.c_str(), level.c_str(), context.c_str(), buf);
//}

namespace rtalk_wrap
{
    CRtalkClientHandlerImpl::CRtalkClientHandlerImpl() : _rtalkClient(NULL)
        ,_canProxy(false)
        ,_bConnect(false)
        ,_reloginTime(10)

    {
        arc::GetService()->Init();

    //    arc::ExternalLogger::Set(logger);
    }

    CRtalkClientHandlerImpl::~CRtalkClientHandlerImpl()
    {
    //    Logout();
    //    arc::GetService()->Stop();
    }

    void CRtalkClientHandlerImpl::Keeplive()
    {
        arc::Service *p = arc::GetService();
        p->Pulse();
    }
    
    void CRtalkClientHandlerImpl::Stop()
    {
        Logout();
        arc::GetService()->Destroy();
//        arc::GetService()->Stop();
    }

    /**
     * 登錄操作
     */
    void CRtalkClientHandlerImpl::Login(UInt32 loginType,
                                        const std::string& ip,
                                        const std::string& account,
                                        const std::string& pwd,
                                        const std::string &version,
                                        entryp::Login::Params params,
                                        UInt32 timeOut)
    {
        Logout();
        //online server
//        arc::SocketAddress addr(ip, 82);

        _rtalkClient = rtalk::CreateClient(ip, 82, version, rtalk::ConnectionType::AUTO);
        if ( !_rtalkClient )
        {
            printf("create rtalk client failed.");
            return;
        }
        _rtalkClient->SetHandler(this);

        gettimeofday(&_startTime, NULL);

        _loginType = loginType;
        _rtalkStatus = E_Rtalk_Status_logining;

        params["platform"] = "ios";
        params["showMsg"] = "1";
        
        _rtalkClient->Login(account, pwd, loginType, entryp::DeviceType::TYPE_IOS, params, timeOut);

    }

    /**
     * 登出操作
     */
    void CRtalkClientHandlerImpl::Logout()
    {
        if ( _rtalkClient )
        {
            // https://bugly.qq.com/v2/crash-reporting/crashes/900021658/1401249/report?pid=2&crashDataType=undefined
            // crash，屏蔽(v717加的)
//            CLocateHandlerImpl::GetInstance().DisConnectFromServer();
            
            _rtalkClient->SetHandler(NULL);
            _rtalkClient->Logout();
        }

//        CChatClientHandlerImpl::GetInstance().Destroy();

        _rtalkClient = NULL;
        _bConnect = false;
        
        _rtalkStatus = E_Rtalk_Status_logout;
        
    }

    bool CRtalkClientHandlerImpl::CreateIMService()
    {
        if (IsDataValid()) {
            CChatClientHandlerImpl::GetInstance().Create(_rtalkClient);
            return true;
        }
        return false;
    }

    const rtalk::Client* CRtalkClientHandlerImpl::GetRtalkClient() const
    {
        return _rtalkClient;
    }

    bool CRtalkClientHandlerImpl::IsDataValid()
    {
        if (!_rtalkClient || !_bConnect) {
            return false;
        }

        return true;
    }

    int CRtalkClientHandlerImpl::SetDeviceToken(const std::string &deviceToken)
    {
        if ( _rtalkClient == NULL )
            return -1;
        
        return _rtalkClient->SetDeviceToken(deviceToken);
    }

    std::string CRtalkClientHandlerImpl::Stats()
    {
        std::string reportData = arc::GetService()->Stats();
        return reportData;
    }


    int CRtalkClientHandlerImpl::InitGlobalServerCfg(const std::string& jsonCfg)
    {
        return arc::InitGlobalServerCfg(jsonCfg);
    }

    void CRtalkClientHandlerImpl::DetectLocalIPStack()
    {
        arc::System::IPStackInfo info = arc::GetSystem()->DetectLocalIPStack("", false);
        arc::GetSystem()->SetLocalIPStackInfo(info);
    }
    
    /**
     * 登錄成功後，建立chat,locate,dike,convos服務的連接
     */
    void CRtalkClientHandlerImpl::OnLoginSuccess(rtalk::Client *client)
    {
        struct timeval end;
        std::string report = _rtalkClient->GetReportData();
        gettimeofday(&end, NULL);
        long diff = 1000000*(end.tv_sec-_startTime.tv_sec) + (end.tv_usec-_startTime.tv_usec);
        printf("login time user: %ld ms", diff/1000);

        _bConnect = true;
        CLoginEventMiddle::getInstance().OnLoginSuccess(report);

        CreateIMService();

        CLocateHandlerImpl::GetInstance().ConnectToLocateServer(client);

        GetPersonInfo();
        
    }

    /**
     * 登錄失敗時，rtalk::Client這個對象已經不能再繼續使用，並且要通知上層邏輯
     */
    void CRtalkClientHandlerImpl::OnLoginFailed(UInt32 reason, rtalk::Client *client)
    {
        gettimeofday(&_startTime, NULL);
        
        if (reason == 403 || reason == 404 || reason == 401) {
            memset(&_startTime , 0 ,sizeof(_startTime));
        }
        
        std::string report = _rtalkClient->GetReportData();
        
        _bConnect = false;
        _rtalkClient = NULL;
        //_rtalkClient->Logout();
        
        CLoginEventMiddle::getInstance().OnLoginFailed(reason, _loginType, report);
        
    }

    /**
     *
     */
    void CRtalkClientHandlerImpl::OnDisconnect(UInt32 reason, rtalk::Client *client)
    {
        gettimeofday(&_startTime, NULL);
        
        if (reason == 1) {
            memset(&_startTime, 0 ,sizeof(_startTime));
        }
        
        _rtalkClient = NULL;
        _bConnect = false;

        CLoginEventMiddle::getInstance().OnDisconnect(reason);
    }

    /**/
    void CRtalkClientHandlerImpl::OnSetPropertyResult(UInt32 requestId, UInt32 result, rtalk::Client *client)
    {
        // result 0为成功，1为失败
        CLoginEventMiddle::getInstance().OnSetPropertyResult(requestId, result);
    }
    /**
     *
     */
    UInt32 CRtalkClientHandlerImpl::GetUserId()
    {
        if ( IsDataValid() == false )
        {
            return 0;
        }

        return _rtalkClient->GetUserId();
    }

    /**
     * 獲取個人性別
     */
    UInt32 CRtalkClientHandlerImpl::GetSex()
    {
        if ( IsDataValid() == false )
        {
            return 2;
        }

        std::string value;

        if ( !GetProperty("sex", value) || value.empty() )
        {
            printf("get property failed");
            return 2;
        }

        UInt32 sex = static_cast<UInt32>(atoi(value.c_str()));

        return sex;
    }

    /**
     * 獲取個人慣稱
     */
    std::string CRtalkClientHandlerImpl::GetNick()
    {
        std::string value;

        const std::string key = "nick";

        if ( !GetProperty(key, value) )
        {
            printf("get property failed");
        }

        return value;
    }


/**
 * 獲取用户头像
 */
std::string CRtalkClientHandlerImpl::GetHeadImg()
{
    std::string value;

    const std::string key = "headImg";

    if ( !GetProperty(key, value) )
    {
        printf("get property failed");
    }

    return value;
}


    /**
     * 獲取登錄token
     */
    std::string CRtalkClientHandlerImpl::GetToken()
    {
        std::string value;

        const std::string key = "token";
        if ( !GetProperty(key, value) )
        {
            printf("get property failed");
        }

//        nsox::xlog(NsoxDebug, "call GetToken, result: %s", value.c_str());
        return value;
    }

    /**
     * 獲取個人信息
     */
    std::string CRtalkClientHandlerImpl::GetPersonInfo()
    {
        std::string value;

        if(_rtalkClient)
            _rtalkClient->GetProperty("info", value);

        if(!value.empty())
        {
            _info = value;
        }

        return _info;
    }


    /**
     * 獲取個人屬性
     */
    bool CRtalkClientHandlerImpl::GetProperty(const std::string &key, std::string &value)
    {
        bool bOK = false;
        value.empty();

        if ( _rtalkClient )
        {
            std::string v;

            bOK = _rtalkClient->GetProperty("info", v);
            if ( !bOK )
            {
                printf("GetProperty Failed: get");
                return bOK;
            }

//            nsox::xlog(NsoxDebug, "get key(%s) from info(%s)", key.c_str(), v.c_str());

            if ( !key.compare("info") )
            {
                value = v;
                return bOK;
            }

            json::Variant data;
            bOK = data.Decode(v);

            if ( !bOK )
            {
                printf("GetProperty Failed:decodec");
                return bOK;
            }

            //value = data[key].ToString();
            if ( data[key].Is<json::Number>() )
            {
                char buf[512] = {0};
                printf(buf, "%d", json::Number::OriginType(data[key].As<json::Number>()));
                value = buf;
            }
            else
            {
                value = json::String::OriginType(data[key].As<json::String>());
            }
        }
        else
        {
            printf("GetProperty Failed:instance null");
        }

//        nsox::xlog(NsoxDebug, "%s", value.c_str());

        return bOK;
    }


}




