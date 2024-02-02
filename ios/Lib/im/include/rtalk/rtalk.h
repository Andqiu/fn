#ifndef RTALK_API_HPP
#define RTALK_API_HPP
namespace rtalk {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
/**
 * @file rtalk/rtalk.h
 * @author 陈梓文
 */
#include <ark/ark.h>
#include <arc/arc.h>
#include <entryp/entryp.h>
#include <gatewayp/gatewayp.h>
#endif /* API */
#ifndef RTALK_API_HPP
#include "export.hpp"
#include "client.hpp"
#include "clienthandler.hpp"
#include "service.hpp"
#include "servicehandler.hpp"
#include "loginrescode.hpp"
#include "disconnectreason.hpp"
#include "connectiontype.hpp"
#include "constants.hpp"
#endif /* RTALK_API_HPP */
namespace rtalk {
namespace ConnectionType {
    /**
     * 使用TCP方式连接Entry
     */
    const UInt8 TCP = 0x00;
    /**
     * 使用UDP方式连接Entry
     */
    const UInt8 UDP = 0x01;
    /**
     * 由Gateay指定方式连接Entry
     */
    const UInt8 AUTO = 0x02;
}
}
/**
 * rtalk 接口
 */
namespace rtalk {
class Client;
class Service;
/**
 * 创建一个Client接口
 * @param gatewayIp GatewayIp
 * @param gatewayPort GatewayPort
 * @param connectionType 连接类型，详见ConnectionType
 * @see Client
 */
Client *CreateClient(const std::string &gatewayIp, UInt16 gatewayPort, const std::string &version, UInt8 connectionType);
/**
 * 从Client接口转换成ServiceManager接口
 * @param client client实例
 * @param serviceType 服务类型，@see rtalk::Constants::ServiceType
 * @param params 服务参数
 *      params["specIp"] = "127.0.0.1"; // 指定此服务的ip
 *      params["specPort] = "50000"; // 指定此服务的端口
 * @see ServiceManager
 * @see Client
 */
Service *ConnectService(Client *client, UInt32 serviceType, const entryp::ConnectService::Params& params=entryp::ConnectService::Params());
/**
* sdk版本
*/
std::string Version();
}
namespace rtalk {
class ClientHandler;
/**
 * 客户端接口
 */
class Client {
public:
    /**
     * 获取UserId，该接口只有Client登录成功之后才生效
     * @return UserId
     */
    virtual UInt32 GetUserId() const = 0;
    /*
     * 获取用户的属性
     * @param key 属性的key
     * @param value 属性的value
     * @return 获取是否成功
     */
    virtual bool GetProperty(const std::string &key, std::string &value) = 0;
    /**
     * 设置设备Token。当用户注销账号，请把deviceToken设置为NULL，即可清除该用户的设备Token。
     * 该接口只能在用户已经登陆成功后使用
     * 设置结果将通过ClientHandler::OnSetPropertyResult通知
     * @param deviceToken 设备Token
     * @return 该操作的唯一Context
     */
    virtual UInt32 SetDeviceToken(const std::string &deviceToken) = 0;
    /**
     * 登录接口，登陆结果通过ClientHandler通知
     * @param account 帐号
     * @param password 密码
     * @param timeout 登陆超时时长(单位为毫秒)，包括2个步骤：Gateway和Login
     * @param loginType 登录类型
     * @param deviceType 登录设备类型，详见entryp::DeviceType
     * @see ClientHandler
     */
    virtual void Login(const std::string &account, const std::string &password, UInt32 loginType, UInt32 deviceType, const entryp::Login::Params &params, UInt32 timeout) = 0;
    /**
     * 关闭客户端
     */
    virtual void Logout() = 0;
    /**
     * 设置客户端事件处理接口
     * @param ClientHandler 处理接口
     * @see ClientHandler
     */
    virtual void SetHandler(ClientHandler *handler) = 0;
    /**
    * 获取登录相关上报信息，登录成功或失败的回调中进行上报
    */
    virtual const std::string GetReportData() = 0;
    /**
    * KCPTun模式下，创建了本地的kcpClient服务后，将本地的ip和端口作为参数调用此接口
    */
    virtual void LoginEntryd(const std::string &host, UInt16 port, bool kcpSuc) = 0;
    /**
     * @brief 是否已登录
     * @return
     */
    virtual bool IsLoggedIn() = 0;
};
}
namespace rtalk {
class Client;
/**
 * 客户端事件处理接口
 * @see Client
 */
class ClientHandler {
public:
    /**
     * 登录成功通知接口
     * @param client Client接口
     */
    virtual void OnLoginSuccess(Client *client) = 0;
    /**
     * 登录失败通知接口
     * @param rescode 失败的原因，详见LoginFailReason
     * @param client Client接口
     * @see LoginFailReason
     */
    virtual void OnLoginFailed(UInt32 rescode, Client *client) = 0;
    /**
     * 设置用户属性的结果通知
     * @param context 唯一的上下文
     * @param result 执行结果，详见：entryp::SetProperty::Result
     * @param client Client接口
     */
    virtual void OnSetPropertyResult(UInt32 context, UInt32 result, Client *client) = 0;
    /**
     * 连接断开通知接口，登录成功之后，如果和服务器断开连接，会通知该接口
     * @param reason 断开的原因
     * @param client Client接口
     * @see DisconnectReason
     */
    virtual void OnDisconnect(UInt32 reason, Client *client) = 0;
};
}
namespace rtalk {
class ServiceHandler;
/**
 * 服务接口，提供给客户端服务的接口，比如IM服务
 */
class Service {
public:
    /**
     * 获取Client的UId
     * @return Client的UId
     */
    virtual UInt32 GetUserId() const = 0;
    /**
     * 关闭服务
     */
    virtual void Close() = 0;
    /**
     * 发送消息块到服务
     * @param payload 数据块
     * @param length 数据块的长度
     * @param lifetime 包的存活时间
     */
    virtual void Send(const char *payload, UInt32 length, ark::Lifetime *lifetime = NULL) = 0;
    /**
     * 发送消息包到服务
     * @param packet 数据包
     * @param lifetime 包的存活时间
     */
    virtual void Send(const ark::Packet &packet, ark::Lifetime *lifetime = NULL) = 0;
    /**
     * 设置服务事件通知接口
     * @see ServiceHandler 服务通知接口
     */
    virtual void SetHandler(ServiceHandler *handler) = 0;
};
}
namespace rtalk {
class Service;
/**
 * 服务事件通知接口
 * @see Service
 */
class ServiceHandler {
public:
    /**
     * 服务连接成功接口，此时服务可以开始工作
     * @param token 连接服务的Token
     */
    virtual void OnConnected(const std::string &token, Service *service) = 0;
    /**
     * 服务断开连接接口
     */
    virtual void OnDisconnect(Service *service) = 0;
    /**
     * 收到数据块接口
     * @see payload 原始数据块
     * @see length 数据块的长度
     */
    virtual void OnPacket(const char *payload, UInt32 length, Service *service) = 0;
    /**
     * 收到数据包接口
     * @param type 数据包的类型
     * @param reader 用于读取数据包
     */
    virtual void OnPacket(UInt32 type, ark::PacketReader &reader, Service *service) = 0;
};
}
namespace rtalk {
/**
 * 登录失败的原因
 */
enum LoginRescode {
    /**
     * 登录成功
     */
    Successfully = 200,
    /**
     * 密码不正确
     */
    PasswordIncorrect = 401,
    /**
     * 帐号不存在
     */
    AccountNotFound = 404,
    /**
     * 服务器内部发生错误
     */
    InternalServerError = 500,
    /**
     * 连接gateway成功，但是没有申请到entry地址就把连接关闭
     */
    AllocateAddressFailed = 600,
    /**
     * 向Gateway申请前端超时
     */
    GatewayTimeouted = 601,
    /**
     * 向Gateway申请不到前端
     */
    GatewayFailed = 602,
    /**
     * 连接Gateway失败
     */
    ConnectGatewayError = 603,
    /**
     * Gateway返回结果时，解包出错
     */
    GatewayDecodeError = 604,
    /**
     * 连接前端服务超时
     */
    LoginTimeouted = 605,
    /**
     * 登录结果没有返回时，前端服务把连接断开
     */
    EntryClosed = 606,
    /**
    * 初始化kcptun时超时
    */
    KcpTimeout = 607,
};
}
namespace rtalk {
/**
 * 与服务器断开的原因
 */
namespace DisconnectReason {
    /**
     * 正常断开
     */
    const UInt32 Disconnect = 0;
    /**
     * 被踢掉
     */
    const UInt32 Kickoff = 1;
};
}
namespace rtalk {
class Constants {
public:
    static const UInt32 PingInterval = 30 * 1000;
    static const UInt32 PingExpireCount = 5;
    /**
     * @brief 内部服务类型
     */
    enum ServiceType
    {
        //! 私信服务
        Chat = 1,
        //! 定位服务
        Locate = 2,
        //! 消息广播服务
        Halo = 7,
        //! 推送服务
        Prome = 8,
        //! 抢唱服务
        GrapSing = 9,
        //! K房管理服务
        KtvRoomMgr = 10,
        //! K房服务
        KtvRoom = 11,
        //! 直播间管理服务
        AnchorRoomMgr = 12,
        //! 直播间服务
        AnchorRoom = 13,
        //! 抢唱管理服务
        GrapSingMgr = 14,
    }; // enum ServiceType
};
}
#endif /* RTALK_API_HPP */
