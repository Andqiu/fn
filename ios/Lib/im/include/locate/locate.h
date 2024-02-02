#ifndef LOCATE_API_HPP
#define LOCATE_API_HPP
namespace locate {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
#include <rtalk/rtalk.h>
#include <locatep/locatep.h>
/**
 * @file locate/locate.h
 * @author 古原辉
 */
#endif /* API */
#ifndef LOCATE_API_HPP
#include "client.hpp"
#include "request.hpp"
#include "clienthandler.hpp"
#include "export.hpp"
#endif /* LOCATE_API_HPP */
namespace locate {
class ClientHandler;
class Request;
/**
 * 此类是客户端的服务接口类
 */
class Client {
public:
    /**
     * 断开服务连接,此操作不会触发ClientHandler::OnClosed 
     */
    virtual void Close() = 0;
    /**
     * 设置超时时间,不设置默认时10s
     * @param second 超时时间，单位秒
     */
    virtual void SetTimeout(UInt32 second) = 0;
    /**
     * 设置locate 的客户端处理程序
     * @param handler 处理程序
     */
    virtual void SetHandler(ClientHandler *handler) = 0;
    /**
     * 设置地理位置的经纬度
     * @param latitude 经度
     * @param longitude 纬度
     */
    virtual void SetPosition(double latitude, double longitude) = 0;
    /**
     * 设置最大距离,距离外的用户不会被查询到
     * @param 最大距离,单位为m
     */
    virtual void SetMaxDistance(UInt32 distance) = 0;
    /**
     * 设置最大活跃时间,超出活跃时间的用户不会被查询到
     * @param time 活跃时间,单位为秒
     */
    virtual void SetMaxTime(UInt32 time) = 0;
    /**
     * 设置期望最大用户人数
     * @param count 用户数
     */
    virtual void SetMaxCount(UInt32 count) = 0;
    /**
     * 设置查询条件中的用户性别
     * @param type 性别,@see locatep::SexType
     */
    virtual void SetQuerySex(UInt8 type) = 0;
    /**
     * 发送查询附近用户异步请求,请求服务器,结果需要等待回调@see ClientHandler::OnNearbyUserReply,查询多页用户,需要调用此接口多次,并更新参数readed
     * @param readed 已读用户数
     */
    virtual Request *QueryNearbyUser(UInt32 readed) = 0;
    /**
     * 向服务器更新我的个人资料,请求服务器,结果需要等待回调@see ClientHandler::OnUpdateReply,主要包括性别,地理位置
     * @param sex 性别,@see locatep::SexType
     */
    virtual Request *UploadInfo(UInt8 sex) = 0;
    /**
     * 清除定位信息,请求服务器,结果需要等待回调@see ClientHandler::OnCleanReply
     */
    virtual Request *CleanLocation() = 0;
};
}
namespace locate {
class RequestHandler;
/**
 * 用户发出的请求接口
 */
class Request {
public:
    /**
     * 取消发出的请求，取消后不会再回调
     */
    virtual void Cancel() = 0;
    /**
     * 获取请求的ID
     */
    virtual UInt32 GetId() const = 0;
};
}
namespace locate {
class Client;
class Request;
/**
 * 此类是定位服务客户端的处理接口类
 */
class ClientHandler {
public:
    /**
     * 用户信息列表定义
     */
    typedef std::list<locatep::UserInfo> UserList;
    /**
     * 连接建立回调
     * @param client 客户端接口
     */
    virtual void OnConnected(Client *client) = 0;
    /**
     * 连接断开回调
     * @param client 客户端接口
     */
    virtual void OnClosed(Client *client) = 0;
    /**
     * 附近用户回应接口
     * @parma result 结果，@see locatep::ResCode 
     * @parma users 用户列表
     */
    virtual void OnNearbyUserReply(UInt32 result, const UserList &users, Request *request) = 0;
    /**
     * 更新信息回应接口
     * @parma result 结果，@see locatep::ResCode 
     */
    virtual void OnUpdateReply(UInt32 result, Request *request) = 0;
    /**
     * 清空定位信息回应接口
     * @parma result 结果，@see locatep::ResCode 
     */
    virtual void OnCleanReply(UInt32 result, Request *request) = 0;
};
}
namespace locate {
class Client;
/**
 * 连接定位服务,返回定位服务的客户端
 * @param client 客户端
 */
Client *ConnectLocateService(rtalk::Client *client);
}
#endif /* LOCATE_API_HPP */
