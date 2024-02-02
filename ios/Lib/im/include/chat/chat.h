#ifndef CHAT_API_HPP
#define CHAT_API_HPP
namespace chat {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
/**
 * @file chat/chat.h
 * @author 喻扬
 */
#include <chatp/chatp.h>
#include <rtalk/rtalk.h>
#endif /* API */
#ifndef CHAT_API_HPP
#include "client.hpp"
#include "clienthandler.hpp"
#include "export.hpp"
#include "presencestatus.hpp"
#include "roster.hpp"
#include "rostergroup.hpp"
#include "rostergrouphandler.hpp"
#include "rostergroups.hpp"
#include "rosterhandler.hpp"
#include "rosteritem.hpp"
#include "rosteritemhandler.hpp"
#include "rosteritems.hpp"
#include "subscribe.hpp"
#include "subscribehandler.hpp"
#include "requesthandler.hpp"
#include "requesttype.hpp"
#endif /* CHAT_API_HPP */
namespace chat {
class ClientHandler;
class Roster;
class RosterGroup;
class RequestHandler;
/**
 * 聊天客户端
 */
class Client {
public:
    /**
     * 设置离线消息id
     * @param msgId 要设置的离线消息id
     */
    virtual void SetOffMsgId(UInt64 msgId) = 0;
    /**
     * 设置聊天客户端处理程序
     * @param handler 要设置的处理程序
     */
    virtual void SetHandler(ClientHandler *handler) = 0;
    /**
     * 设置请求结果通知接口
     * @param handler 通知接口
     */
    virtual void SetRequestHandler(RequestHandler *handler) = 0;
    /**
     * 关闭此客户端，断开与服务器的连接，此操作不会触发ClientHandler::OnClosed
     */
    virtual void Close() = 0;
    /**
     * 获取好友名单
     * @return 好友名单
     */
    virtual Roster *GetRoster() = 0;
    /**
     * 设置此用户的用户名称
     * @param name 此用户的用户名
     * @return 该操作的RequestId
     */
    virtual UInt32 SetName(const std::string &name) = 0;
    /**
     * 设置出席状态
     * @param status 出席状态，@see PresenceStatus
     * @param show 状态描述
     * @return 该操作的RequestId
     */
    virtual UInt32 SetPresence(UInt8 status, const std::string &show) = 0;
    /**
     * 向任意用户发送消息，向好友发送消息优先使用RosterItem::ForwardMessage函数，如果用户不在线，该消息将会存离线消息
     * @param userId 用户标识
     * @param type 消息类型
     * @param body 消息内容
     * @param subject 消息扩展内容
     * @return 该操作的RequestId
     */
    virtual UInt32 ForwardMessage(UInt32 userId, UInt8 type, const std::string &body, const std::string &subject) = 0;
    /**
     * 向指定用户发送好友请求
     * @param userId 指定的用户
     * @param name 对方的用户名
     * @param remark 好友的备注
     * @param group 好友所在的分组
     * @param greeting 问候消息
     * @return 该操作的RequestId
     */
    virtual UInt32 SendSubscribe(UInt32 userId, const std::string &name, const std::string &remark, RosterGroup *group, const std::string &greeting) = 0;
    /**
     * 向任意的在线用户发送消息，如果用户不在线，消息不会存离线
     * @param userId 准备发送用户的UID
     * @param name 用户的标识
     * @param method 消息的方法名
     * @param content 消息的内容
     */
    virtual UInt32 SendIQ(UInt32 userId, const std::string &name, const std::string &method, const std::string &content) = 0;
 /**
	 * 向 server 上报撤回消息结果（目前只能撤回系统消息）
	 * @param body 消息内容
	 *			   形式为json：{"msgId": 0, "status": 0, "reason": ""} status为1则表示成功，其他为失败
	 */
 virtual UInt32 WithdrawMessageFeedback(const std::string &body) = 0;
};
}
namespace chat {
class Client;
class Subscribe;
class RosterItem;
/**
 * 聊天客户端处理程序
 */
class ClientHandler {
public:
    /**
     * 连接成功时的处理函数，此时好友名单已经全部加载
     * @param client 对应的客户端
     */
    virtual void OnConnected(Client *client) = 0;
    /**
     * 连接断开时的处理函数
     * @param client 对应的客户端
     */
    virtual void OnClosed(Client *client) = 0;
    /**
     * 收到陌生人发来的消息时的处理函数，好友的消息会回调RosterItemHandler::OnMessage
     * @param userId 用户标识
     * @param name 用户名称
     * @param type 消息类型
     * @param timestamp 离线消息的时间戳，为0表示在线消息
     * @param body 消息内容
     * @param subject 消息控制字段
     * @param isOffline 是否离线
     * @param msgId 消息id 排重用的
     * @param riskStatus 风险状态 >0 为风险
     * @param client 对应的客户端
     */
    virtual void OnMessage(UInt32 userId, const std::string &name, UInt8 type, UInt32 timestamp, const std::string &body, const std::string &subject, bool isOffline, UInt64 msgId, UInt32 riskStatus, Client *client) = 0;
    /**
     * 收到或发出好友请求的处理函数
     * @param subscribe 对应的好友请求
     * @param greeting 问候消息
     * @param client 对应的客户端
     */
    virtual void OnSubscribe(Subscribe *subscribe, const std::string &greeting, Client *client) = 0;
    /**
     * 收到陌生人的IQ消息
     * @param userId 用户ID
     * @param name 用户名称
     * @param method IQ的方法名
     * @param content IQ的内容
     */
    virtual void OnIQ(UInt32 userId, const std::string &name, const std::string &method, const std::string &content, Client *client) = 0;
    /**
     * 收到离线的好友邀请接受请求处理函数，在线的请求通过SubscribeHandler::OnAccept处理
     * @param rosterItem 邀请成功的好友
     */
    virtual void OnAccepted(RosterItem *rosterItem, Client *client) = 0;
    /**
     * 收到离线的用户拒绝邀请处理函数，在线的请求通过SubscribeHandler::OnReject处理
     * @param userId 拒绝邀请的用户Id
     * @param name 拒绝邀请的用户名称
     * @param reason 拒绝的理由
     */
    virtual void OnRejected(UInt32 userId, const std::string &name, const std::string &reason, Client *client) = 0;
};
}
/**
 * 聊天服务客户端协议库命名空间
 */
namespace chat {
class Client;
/**
 * 连接聊天服务
 * @param client rtalk客户端的指针
 * @return 聊天客户端
 */
Client *ConnectChatService(rtalk::Client *client);
/**
* sdk版本
*/
int Version();
//
enum Version
{
    VERSION_OFF_MSG = 20230227, // 20230227: 离线消息客户端也需要回复一个ack
};
}
namespace chat {
/**
 * 出席状态类型
 */
namespace PresenceStatus {
    /**
     * 在线
     */
    const UInt8 ONLINE = 0x01;
    /**
     * 离线
     */
    const UInt8 OFFLINE = 0x02;
    /**
     * 离开
     */
    const UInt8 AWAY = 0x03;
    /**
     * 忙碌
     */
    const UInt8 BUSY = 0x04;
}
}
namespace chat {
class RosterGroups;
class RosterHandler;
class RosterItems;
class RequestHandler;
/**
 * 此类表示好友名单
 */
class Roster {
public:
    /**
     * 设置好友名单的处理程序
     * @param handler 要设置的处理程序
     */
    virtual void SetHandler(RosterHandler *handler) = 0;
    /**
     * 设置请求结果通知接口
     * @param handler 通知接口
     */
    virtual void SetRequestHandler(RequestHandler *handler) = 0;
    /**
     * 获取此好友名单的处理程序
     * @return 此好友名单的处理程序
     */
    virtual RosterHandler *GetHandler() const = 0;
    /**
     * 创建好友分组，此操作不会立即生效，需等待服务器响应
     * @see RosterHandler::OnCreateGroup
     * @param name 分组名称
     * @return 该操作的RequestId
     */
    virtual UInt32 CreateGroup(const std::string &name) = 0;
    /**
     * 获取所有好友分组的列表
     * @return 好友分组的列表
     */
    virtual const RosterGroups &GetGroups() const = 0;
    /**
     * 获取所有好友的列表
     * @return 好友的列表
     */
    virtual const RosterItems &GetItems() const = 0;
};
}
namespace chat {
class RosterGroupHandler;
class RosterItems;
class RequestHandler;
/**
 * 此类表示好友名单中的分组
 */
class RosterGroup {
public:
    /**
     * 设置好友分组的处理程序
     * @param handler 好友分组的处理程序
     */
    virtual void SetHandler(RosterGroupHandler *handler) = 0;
    /**
     * 设置请求结果通知接口
     * @param handler 通知接口
     */
    virtual void SetRequestHandler(RequestHandler *handler) = 0;
    /**
     * 获取好友分组的处理程序
     * @return 好友分组的处理程序
     */
    virtual RosterGroupHandler *GetHandler() const = 0;
    /**
     * 获取好友分组的标识
     * @return 好友分组的标识
     * @return 该操作的RequestId
     */
    virtual UInt32 GetGroupId() const = 0;
    /**
     * 获取分组名称
     * @return 分组名称
     */
    virtual const std::string &GetName() const = 0;
    /**
     * 好友分组重命名，此操作不会立即生效，需等待服务器响应
     * @see RosterGroupHandler::OnRename
     * @param name 要设置的分组名
     * @return 该操作的RequestId
     */
    virtual UInt32 Rename(const std::string &name) = 0;
    /**
     * 删除此好友分组，组内的用户将被移至默认分组，此操作不会立即生效，需等待服务器响应
     * @see RosterGroupHandler::OnRemove
     * @return 该操作的RequestId
     */
    virtual UInt32 Remove() = 0;
    /**
     * 获取此分组的好友列表
     * @return 此分组的好友列表
     */
    virtual const RosterItems &GetItems() const = 0;
};
}
namespace chat {
class RosterGroup;
/**
 * 好友分组的处理程序
 */
class RosterGroupHandler {
public:
    /**
     * 好友分组发生重命名时的处理函数
     * @see RosterGroup::Rename
     * @param name 新的分组名称
     * @param group 对应的好友分组
     */
    virtual void OnRename(const std::string &name, RosterGroup *group) = 0;
    /**
     * 好友分组被删除时的处理函数
     * @see RosterGroup::Remove
     * @param group 被删除的好友分组
     */
    virtual void OnRemove(RosterGroup *group) = 0;
};
}
namespace chat {
class RosterGroup;
class RosterGroups : public std::map<UInt32, RosterGroup *> {
};
}
namespace chat {
class Roster;
class RosterGroup;
class RosterItem;
/**
 * 好友名单的处理程序
 */
class RosterHandler {
public:
    /**
     * 新的分组创建时的处理函数
     * @see Roster::CreateGroup
     * @param group 新创建的分组
     * @param roster 对应的好友名单
     */
    virtual void OnCreateGroup(RosterGroup *group, Roster *roster) = 0;
    /**
     * 新的好友创建时的处理函数
     * @param rosterItem 新创建的好友
     * @param roster 对应的好友名单
     */
    virtual void OnCreateRosterItem(RosterItem *rosterItem, Roster *roster) = 0;
};
}
namespace chat {
class RosterGroup;
class RosterItemHandler;
class RequestHandler;
/**
 * 此类表示好友名单中的一个好友
 */
class RosterItem {
public:
    /**
     * 设置处理程序
     * @param handler 要设置的处理程序
     */
    virtual void SetHandler(RosterItemHandler *handler) = 0;
    /**
     * 设置请求结果通知接口
     * @param handler 通知接口
     */
    virtual void SetRequestHandler(RequestHandler *handler) = 0;
    /**
     * 获取此好友的处理程序
     * @param handler 此好友的处理程序
     */
    virtual RosterItemHandler *GetHandler() const = 0;
    /**
     * 获取此好友的标识
     * @return 此好友的标识
     */
    virtual UInt32 GetUserId() const = 0;
    /**
     * 获取此好友的备注
     * @return 此好友的备注
     */
    virtual const std::string &GetRemark() const = 0;
    /**
     * 设置此好友的备注，此操作不会立即生效，需等待服务器响应
     * @param remark 要设置的备注
     * @return 该操作的RequestId
     */
    virtual UInt32 Remark(const std::string &remark) = 0;
    /**
     * 获取此好友所在的分组
     * @return 此好友所在的分组
     */
    virtual RosterGroup *GetGroup() const = 0;
    /**
     * 移动此好友到指定的分组，此操作不会立即生效，需等待服务器响应
     * @see RosterItemHandler::OnMove
     * @param group 要移至的分组
     * @return 该操作的RequestId
     */
    virtual UInt32 Move(RosterGroup *group) = 0;
    /**
     * 解除好友关系，此操作不会立即生效，需等待服务器响应
     * @see RosterItemHandler::OnRemove
     * @return 该操作的RequestId
     */
    virtual UInt32 Remove() = 0;
    /**
     * 向此好友发送消息
     * @param type 消息类型
     * @param body 发送的消息体
     * @param subject 发送的消息扩展
     * @return 该操作的RequestId
     */
    virtual UInt32 ForwardMessage(UInt8 type, const std::string &body, const std::string &subject) = 0;
    /**
     * 向该用户发送消息，如果用户不在线，消息不会存离线
     * @param name 用户的标识
     * @param method 消息的方法名
     * @param content 消息的内容
     */
    virtual UInt32 SendIQ(const std::string &name, const std::string &method, const std::string &content) = 0;
};
}
namespace chat {
class RosterGroup;
class RosterItem;
/**
 * 好友的处理程序
 */
class RosterItemHandler {
public:
    /**
     * 好友备注发生变更时的处理函数
     * @see RosterItem::Remark
     * @param remark 新的备注名
     * @param item 对应的好友
     */
    virtual void OnRemark(const std::string &remark, RosterItem *item) = 0;
    /**
     * 当好友移至新的分组时的处理函数
     * @see RosterItem::Move
     * @param from 旧的分组
     * @param to 新的分组
     * @param item 对应的好友
     */
    virtual void OnMove(RosterGroup *from, RosterGroup *to, RosterItem *item) = 0;
    /**
     * 当好友被删除时的处理函数
     * @see RosterItem::Remove
     * @param item 对应的好友
     */
    virtual void OnRemove(RosterItem *item) = 0;
    /**
     * 当收到好友重命名通知时的处理函数
     * @param name 好友的新用户名称
     * @param item 对应的好友
     */
    virtual void OnRename(const std::string &name, RosterItem *item) = 0;
    /**
     * 当收到好友的出席状态时的处理函数
     * @param status 好友的出席状态，@see PresenceStatus
     * @param show 好友的状态描述
     * @param item 对应的好友
     */
    virtual void OnPresence(UInt32 status, const std::string &show, RosterItem *item) = 0;
    /**
     * 当收到好友消息时的处理函数
     * @param timestamp 离线消息的时间戳，为0则表示是在线消息
     * @param body 收到的消息
     * @param subject 消息扩展字段
     * @param item 对应的好友
     * @param isOffline 是否为离线消息
     */
    virtual void OnMessage(UInt8 type, UInt32 timestamp, const std::string &body, const std::string &subject, bool isOffline, RosterItem *item) = 0;
    /**
     * 收到好友的IQ消息
     * @param name 用户名称
     * @param method IQ的方法名
     * @param content IQ的内容
     */
    virtual void OnIQ(const std::string &name, const std::string &method, const std::string &content, RosterItem *item) = 0;
};
}
namespace chat {
class RosterItem;
/**
 * 好友名单的列表
 */
class RosterItems : public std::map<UInt32, RosterItem *> {
};
}
namespace chat {
class SubscribeHandler;
class RosterGroup;
class RequestHandler;
/**
 * 此类表示好友请求
 */
class Subscribe {
public:
    /**
     * 设置处理程序
     * @param handler 要设置的处理程序
     */
    virtual void SetHandler(SubscribeHandler *handler) = 0;
    /**
     * 设置请求结果通知接口
     * @param handler 通知接口
     */
    virtual void SetRequestHandler(RequestHandler *handler) = 0;
    /**
     * 返回此好友请求是否为传入请求
     * @return 是否为传入请求
     */
    virtual bool IsIncoming() const = 0;
    /**
     * 返回此好友请求是否为传出请求
     * @return 是否为传出请求
     */
    virtual bool IsOutgoing() const = 0;
    /**
     * 获取对方的用户标识
     * @return 对方的用户标识
     * @return 该操作的RequestId
     */
    virtual UInt32 GetUserId() const = 0;
    /**
     * 获取对方的用户名
     * @return 对方的用户名
     */
    virtual const std::string &GetName() const = 0;
    /**
     * 获取时间戳
     * @return 时间戳 
     */
    virtual const UInt32 GetTimestamp() const = 0;
    /**
     * 取消此请求（只能用于传出请求）
     * @return 该操作的RequestId
     */
    virtual UInt32 Cancel() = 0;
    /**
     * 接受此请求（只能用于传入请求）
     * @param remark 设置对方的备注
     * @param group 要将对方添加至的分组
     * @return 该操作的RequestId
     */
    virtual UInt32 Accept(const std::string &remark, RosterGroup *group) = 0;
    /**
     * 拒绝此请求（只能用于传入请求）
     * @param reason 拒绝的原因
     * @return 该操作的RequestId
     */
    virtual UInt32 Reject(const std::string &reason) = 0;
};
}
namespace chat {
class Subscribe;
/**
 * 好友请求的处理程序
 */
class SubscribeHandler {
public:
    /**
     * 刷新时的处理函数（请求重发时）
     * @param greeting 问候消息
     * @param subscribe 对应的好友请求
     */
    virtual void OnRefresh(const std::string &greeting, Subscribe *subscribe) = 0;
    /**
     * 取消时的处理函数
     * @param subscribe 对应的好友请求
     */
    virtual void OnCancel(Subscribe *subscribe) = 0;
    /**
     * 拒绝时的处理函数
     * @param reason 拒绝的原因
     * @param subscribe 对应的好友请求
     */
    virtual void OnReject(const std::string &reason, Subscribe *subscribe) = 0;
    /**
     * 接受时的处理函数
     * @param subscribe 对应的好友请求
     */
    virtual void OnAccept(Subscribe *subscribe) = 0;
};
}
namespace chat {
/**
 * 异步请求结果通知接口
 */
class RequestHandler {
public:
    /**
     * @param type 请求类型，详见ClientRequest, RosterRequest, RosterGroupRequest, RosterItemRequest, SubscribeRequest
     * @param requestId 请求Id
     * @param reason 执行结果，0表示成功，其他表示失败的原因
     */
    virtual void OnRequestResult(UInt32 type, UInt32 requestId, UInt32 reason) = 0;
};
}
namespace chat {
/**
 * 对应Client的接口
 */
namespace ClientRequest {
    /**
     * 对应SetName接口
     */
    const UInt32 SET_NAME = 0x00;
    /**
     * 对应SetPresence接口
     */
    const UInt32 SET_PRESENCE = 0x01;
    /**
     * 对应ForwardMessage接口
     */
    const UInt32 FORWARD_MESSAGE = 0x02;
    /**
     * 对应SendSubscribe接口
     */
    const UInt32 SEND_SUBSCRIBE = 0x03;
    /**
     * 对应SendIQ接口
     */
    const UInt32 SEND_IQ = 0x04;
}
/**
 * 对应Roster的接口
 */
namespace RosterRequest {
    /**
     * 对应CreateGroup接口
     */
    const UInt32 CREATE_GROUP = 0x00;
}
/**
 * 对应RosterGroup的接口
 */
namespace RosterGroupRequest {
    /**
     * 对应Rename接口
     */
    const UInt32 RENAME = 0x00;
    /**
     * 对应Remove接口
     */
    const UInt32 REMOVE = 0x01;
}
/**
 * 对应RosterItem的接口
 */
namespace RosterItemRequest {
    /**
     * 对应Remark接口
     */
    const UInt32 REMARK = 0x00;
    /**
     * 对应Move接口
     */
    const UInt32 MOVE = 0x01;
    /**
     * 对应Remove接口
     */
    const UInt32 REMOVE = 0x02;
    /**
     * 对应ForwardMessage接口
     */
    const UInt32 FORWARD_MESSAGE = 0x03;
    /**
     * 对应SendIQ接口
     */
    const UInt32 SEND_IQ = 0x04;
}
/**
 * 对应Subscribe的接口
 */
namespace SubscribeRequest {
    /**
     * 对应Cancel接口
     */
    const UInt32 CANCEL = 0x00;
    /**
     * 对应Accept接口
     */
    const UInt32 ACCEPT = 0x01;
    /**
     * 对应Reject接口
     */
    const UInt32 REJECT = 0x02;
}
}
#endif /* CHAT_API_HPP */
