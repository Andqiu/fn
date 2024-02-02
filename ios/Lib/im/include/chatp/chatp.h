#ifndef CHATP_API_HPP
#define CHATP_API_HPP
namespace chatp {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
/**
 * @file chatp/chatp.h
 * @author 喻扬
 */
#include <ark/ark.h>
#endif /* API */
#ifndef CHATP_API_HPP
#include "ack.hpp"
#include "ackrescode.hpp"
#include "connect.hpp"
#include "connectrescode.hpp"
#include "connectresult.hpp"
#include "group.hpp"
#include "groups.hpp"
#include "iq.hpp"
#include "iqaction.hpp"
#include "message.hpp"
#include "messagetype.hpp"
#include "packettype.hpp"
#include "presence.hpp"
#include "presenceaction.hpp"
#include "presencestatus.hpp"
#include "roster.hpp"
#include "rosteraction.hpp"
#include "rosteritems.hpp"
#include "rosteritems.hpp"
#include "subscribe.hpp"
#include "subscribeaction.hpp"
#include "iqtype.hpp"
#endif /* CHATP_API_HPP */
namespace chatp {
/**
 * 确认包，用于向对端确认某个请求的处理结果
 */
class Ack : public ark::Packet {
public:
    /**
     * 构造函数
     */
    Ack();
    /**
     * 构造函数
     * @param rescode 要设置的返回码
     * @param requestId 对应的请求标识
     */
    Ack(UInt8 rescode, UInt32 requestId);
    /**
     * 析构函数
     */
    virtual ~Ack();
public:
    /**
     * 获取返回码
     * @see AckRescode
     * @return 返回码
     */
    virtual UInt8 GetRescode() const;
    /**
     * 设置返回码
     * @see AckRescode
     * @param rescode 要设置的返回码
     */
    virtual void SetRescode(UInt8 rescode);
    /**
     * 获取请求标识
     * @return 请求标识
     */
    virtual UInt32 GetRequestId() const;
    /**
     * 设置请求标识
     * @param requestId 要设置的请求标识
     */
    virtual void SetRequestId(UInt32 requestId);
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 rescode_;
    UInt32 requestId_;
};
}
namespace chatp {
/**
 * 确认包的返回码
 */
namespace AckRescode {
    /**
     * 成功
     */
    const UInt8 OK = 0x00;
    /**
     * 请求超时
     */
    const UInt8 TIMEOUT = 0x01;
    /**
     * 错误的请求，表示请求本身有问题（如包格式错误）
     */
    const UInt8 BAD_REQUEST = 0x02;
    /**
     * 服务器内部错误，表示服务器处理时发生错误
     */
    const UInt8 INTERNAL_ERROR = 0x03;
}
}
namespace chatp {
/**
 * 连接数据包
 */
    class Connect : public ark::Packet {
    public:
        enum Type
        {
            VERTSION = 0x00,
            OFFMSGID = 0x01,
        };
        /**
         * 构造函数
         */
        Connect();
        /**
         * 析构函数
         */
        virtual ~Connect();
    public:
        /**
         * 获取用户标识
         * @return 用户标识
         */
        UInt32 GetJid() const;
        /**
         * 设置用户标识
         * @param 要设置的用户标识
         */
        void SetJid(UInt32 jid);
        /**
         * 获取连接令牌
         * @return 连接令牌
         */
        const std::string &GetToken() const;
        /**
         * 设置连接令牌
         * @param token 要设置的连接令牌
         */
        void SetToken(const std::string &token);
        /**
         * 获取版本号
         * @return 版本号
         */
        int GetVersion() const;
        /**
         * 设置版本号
         * @param token 要设置的版本号
         * @param version 要设置的版本号
         */
        void SetVersion(int version);
        /**
         * 获取本地缓存的离线消息id
         * @return 本地缓存的离线消息id
         */
        UInt64 GetOffMsgId() const;
        /**
         * 设置本地缓存的离线消息id
         * @param token 要设置的本地缓存的离线消息id
         */
        void SetOffMsgId(UInt64 offMsgId);
    public:
        virtual UInt32 GetType() const;
        virtual bool Encode(ark::PacketWriter &writer) const;
        virtual bool Decode(ark::PacketReader &reader);
    private:
        UInt32 jid_;
        std::string token_;
        int version_;
        UInt64 offMsgId_;
    };
}
namespace chatp {
/**
 * 连接结果的返回码
 */
namespace ConnectRescode {
    /**
     * 连接成功
     */
    const UInt8 SUCCESS = 0x00;
    /**
     * 连接失败
     */
    const UInt8 FAILED = 0x01;
    /**
     * 服务器拒绝
     */
    const UInt8 REJECTED = 0x02;
}
}
namespace chatp {
/**
 * 连接结果数据包
 */
class ConnectResult : public ark::Packet {
public:
    /**
     * 构造函数
     */
    ConnectResult();
    /**
     * 析构函数
     */
    virtual ~ConnectResult();
public:
    /**
     * 获取连接结果
     * @see ConnectRescode
     * @return 连接结果
     */
    UInt8 GetResult() const;
    /**
     * 设置连接结果
     * @see ConnectRescode
     * @param result 要设置的连接结果
     */
    void SetResult(UInt8 result);
    /**
     * 获取连接的资源标识
     * @return 资源标识
     */
    const std::string &GetResource() const;
    /**
     * 设置连接的资源标识
     * @param resource 要设置的资源标识
     */
    void SetResource(const std::string &resource);
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 result_;
    std::string resource_;
};
}
namespace chatp {
/**
 * 此类表示好友名单中的一条记录
 */
class RosterItem : public ark::Data {
public:
    /**
     * 构造函数
     */
    RosterItem();
    /**
     * 析构函数
     */
    virtual ~RosterItem();
public:
    /**
     * 获取用户标识
     * @return 用户标识
     */
    UInt32 GetJid() const;
    /**
     * 设置用户标识
     * @param jid 要设置的用户标识
     */
    void SetJid(UInt32 jid);
    /**
     * 获取好友备注
     * @return 好友备注
     */
    const std::string &GetRemark() const;
    /**
     * 设置好友备注
     * @param remark 要设置的好友备注
     */
    void SetRemark(const std::string &remark);
    /**
     * 获取用户名
     * @return 用户名
     */
    const std::string &GetName() const;
    /**
     * 设置用户名
     * @param name 要设置的用户名
     */
    void SetName(const std::string &name);
public:
    virtual void Form(ark::DataForm &form) const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 jid_;
    std::string remark_;
    std::string name_;
};
}
namespace chatp {
/**
 * 好友名单列表
 */
class RosterItems : public std::list<RosterItem> {
};
}
namespace chatp {
/**
 * 群组数据
 */
class Group : public ark::Data {
public:
    /**
     * 构造函数
     */
    Group();
    /**
     * 析构函数
     */
    virtual ~Group();
public:
    /**
     * 获取组标识
     * @return 组标识
     */
    UInt32 GetGroupId() const;
    /**
     * 设置组标识
     * @param groupId 要设置的组标识
     */
    void SetGroupId(UInt32 groupId);
    /**
     * 获取组名称
     * @return 组名称
     */
    const std::string &GetGroupName() const;
    /**
     * 设置组名称
     * @param 要设置的组名称
     */
    void SetGroupName(const std::string &groupName);
    /**
     * 获取好友名单列表
     * @return 好友名单列表
     */
    const RosterItems &GetRosterItems() const;
    /**
     * 获取好友名单列表
     * @return 好友名单列表
     */
    RosterItems &GetRosterItems();
public:
    virtual void Form(ark::DataForm &form) const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 groupId_;
    std::string groupName_;
    RosterItems items_;
};
}
namespace chatp {
/**
 * 群组列表类
 */
class Groups : public std::list<Group> {
};
}
namespace chatp {
/**
 * IQ数据包
 */
class IQ : public ark::Packet {
public:
    /**
     * 构造函数
     */
    IQ();
    /**
     * 析构函数
     */
    virtual ~IQ();
public:
    /**
     * 获取操作Action
     * @see IQAction
     * @return 操作类型
     */
    UInt8 GetAction() const;
    /**
     * 设置IQ的Action
     * @see IQAction
     * @param type 要设置的操作类型
     */
    void SetAction(UInt8 action);
    /**
     * 获取IQ类型
     * @return 类型，详见IQType
     */
    UInt8 GetIQType() const;
    /**
     * 设置IQ类型
     * @param type 类型
     */
    void SetIQType(UInt8 type);
    /**
     * 获取IQ的上下文
     * @return IQ的上下文
     */
    UInt32 GetRequestId() const;
    /**
     * 设置IQ的上下文
     * @param 要设置的IQ上下文
     */
    void SetRequestId(UInt32 requestId);
    /**
     * 获取用户标识
     * @return 用户标识
     */
    UInt32 GetJid() const;
    /**
     * 设置用户标识
     * @param jid 要设置的用户标识
     */
    void SetJid(UInt32 jid);
    /**
     * 获取资源标识
     * @return 资源标识
     */
    const std::string &GetResource() const;
    /**
     * 设置资源标识
     * @param resource 要设置的资源标识
     */
    void SetResource(const std::string &resource);
    /**
     * 获取用户名
     * @return 用户名
     */
    const std::string &GetName() const;
    /**
     * 设置用户名
     * @param name 要设置的用户名
     */
    void SetName(const std::string &name);
    /**
     * 获取方法名
     * @return 方法名
     */
    const std::string &GetMethod() const;
    /**
     * 设置方法名
     * @param method 要设置的方法名
     */
    void SetMethod(const std::string &method);
    /**
     * 获取请求内容
     * @return 请求内容
     */
    const std::string &GetContent() const;
    /**
     * 设置请求内容
     * @param content 要设置的请求内容
     */
    void SetContent(const std::string &content);
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 action_;
    UInt8 type_;
    UInt32 requestId_;
    UInt32 jid_;
    std::string resource_;
    std::string name_;
    std::string method_;
    std::string content_;
};
}
namespace chatp {
/**
 * IQ操作类型
 */
namespace IQAction {
    /**
     * 空，不执行任何操作
     */
    const UInt8 NONE = 0x00;
    /**
     * 请求
     */
    const UInt8 REQUEST = 0x01;
    /**
     * 回复
     */
    const UInt8 RESPONSE = 0x02;
    /**
     * 转发
     */
    const UInt8 FORWARD = 0x03;
}
}
namespace chatp {
/**
 * 消息数据包
 */
class Message : public ark::Packet {
public:
    /**
     * 构造函数
     */
    Message();
    /**
     * 析构函数
     */
    virtual ~Message();
public:
    /**
     * 获取消息类型
     * @see MessageType
     * @return 消息类型
     */
    UInt8 GetMessageType() const;
    /**
     * 设置消息类型
     * @see MessageType
     * @param type 要设置的消息类型
     */
    void SetMessageType(UInt32 type);
    /**
     * 获取消息上下文，消息上下文非0则表示消息需要确认
     * @return 消息上下文
     */
    UInt32 GetContext() const;
    /**
     * 设置消息上下文，消息上下文非0则表示消息需要确认
     * @param context 要设置的消息上下文
     */
    void SetContext(UInt32 context);
    /**
     * 获取用户标识
     * @return 用户标识
     */
    UInt32 GetJid() const;
    /**
     * 设置用户标识
     * @param 要设置的用户标识
     */
    void SetJid(UInt32 jid);
    /**
     * 获取资源标识
     * @return 资源标识
     */
    const std::string &GetResource() const;
    /**
     * 设置资源标识
     * @param resource 要设置的资源标识
     */
    void SetResource(const std::string &resource);
    /**
     * 获取用户名
     * @return 用户名
     */
    const std::string &GetName() const;
    /**
     * 设置用户名
     * @param name 要设置的用户名
     */
    void SetName(const std::string &name);
    /**
     * 获取消息内容
     * @return 消息内容
     */
    const std::string &GetBody() const;
    /**
     * 设置消息内容
     * @param body 要设置的消息内容
     */
    void SetBody(const std::string &body);
    /**
     * 获取消息扩展
     * return 消息扩展
     */
    const std::string &GetSubject() const;
    /**
     * 设置消息扩展
     * @param subject 设置的消息扩展
     */
    void SetSubject(const std::string &subject);
    /**
     * 获取消息时间戳
     * @return 消息的时间戳
     */
    UInt32 GetTimestamp() const;
    /**
     * 设置消息的时间戳，默认为0
     * @param timestamp 要设置的时间戳
     */
    void SetTimestamp(UInt32 timestamp);
    /**
     * 获取请求标识
     * @return 获取请求标识
     */
    UInt32 GetRequestId() const;
    /**
     * 设置请求标识
     * @params 要设置的请求标识
     */
    void SetRequestId(UInt32 requestId);
    /**
     * 获取此消息是否为离线消息
     * @return 如果是离线消息，则返回true，否则返回false
     */
    bool IsOffline() const;
    /**
     * 设置此消息是否为离线消息
     * @param offline 标识此消息是否为离线消息
     */
    void SetOffline(bool offline);
    /**
     * 设置此消息的消息id 用于排重
     * @param offline 标识此消息是否为离线消息
     */
    void SetMsgId(UInt64 msgId);
    /**
     * 获取此的消息id
     * @return  消息id
     */
    UInt64 GetMsgId() const;
    /**
     * 设置风险消息提示
     * @param risky 是否为风险用户消息
     */
    void SetRiskStatus(UInt32 risky);
    /**
     * 获取IM风控状态
     * @return risky >0 为风险
     */
    UInt32 GetRiskStatus() const;
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 offline_;
    UInt8 type_;
    UInt32 context_;
    UInt32 jid_;
    std::string resource_;
    std::string name_;
    std::string body_;
    std::string subject_;
    UInt32 timestamp_;
    UInt32 requestId_;
    UInt64 msgId_;
    UInt32 riskStatus_;
};
}
namespace chatp {
/**
 * 消息类型
 */
namespace MessageType {
    /**
     * 空，不使用，仅用于测试
     */
    const UInt8 NONE = 0x00;
    /**
     * 聊天消息
     */
    const UInt8 CHAT = 0x01;
    /**
     * 确认消息
     */
    const UInt8 ACK = 0x02;
    /**
     * 控制消息
     */
    const UInt8 CONTROL = 0x03;
    /**
     * 系统消息
     */
    const UInt8 SYSTEM = 0x04;
    /**
     * 撤回消息
     */
    const UInt8 WITHDRAW = 0x05;
}
}
namespace chatp {
/**
 * chat服务相关数据包类型
 */
namespace PacketType {
    /**
     * 连接包
     */
    const UInt32 CONNECT = 0x00;
    /**
     * 连接结果包
     */
    const UInt32 CONNECT_RESULT = 0x01;
    /**
     * IQ包
     */
    const UInt32 IQ = 0x02;
    /**
     * 好友名单包
     */
    const UInt32 ROSTER = 0x03;
    /**
     * 出席状态包
     */
    const UInt32 PRESENCE = 0x04;
    /**
     * 消息包
     */
    const UInt32 MESSAGE = 0x05;
    /**
     * 订阅包
     */
    const UInt32 SUBSCRIBE = 0x06;
    /**
     * 确认包
     */
    const UInt32 ACK = 0x07;
}
}
namespace chatp {
/**
 * 出席状态数据包
 */
class Presence : public ark::Packet {
public:
    /**
     * 构造函数
     */
    Presence();
    /**
     * 析构函数
     */
    virtual ~Presence();
public:
    /**
     * 获取操作类型
     * @see PresenceAction
     * @return 操作类型
     */
    UInt8 GetAction() const;
    /**
     * 设置操作类型
     * @see PresenceAction
     * @param action 要设置的操作类型
     */
    void SetAction(UInt8 action);
    /**
     * 获取用户标识
     * @return 用户标识
     */
    UInt32 GetJid() const;
    /**
     * 设置用户标识
     * @param jid 要设置的用户标识
     */
    void SetJid(UInt32 jid);
    /**
     * 获取资源标识
     * @return 资源标识
     */
    const std::string &GetResource() const;
    /**
     * 设置资源标识
     * @param resource 要设置的资源标识
     */
    void SetResource(const std::string &resource);
    /**
     * 获取出席状态
     * @see PresenceStatus
     * @return 出席状态
     */
    UInt8 GetStatus() const;
    /**
     * 设置出席状态
     * @see PresenceStatus
     * @param status 要设置的出席状态
     */
    void SetStatus(UInt8 status);
    /**
     * 获取状态描述
     * @return 状态描述
     */
    const std::string &GetShow() const;
    /**
     * 设置状态描述
     * @param show 要设置的状态描述
     */
    void SetShow(const std::string &show);
    /**
     * 获取用户名称
     * @return 用户名称
     */
    const std::string &GetName() const;
    /**
     * 设置用户名称
     * @param name 要设置的用户名称
     */
    void SetName(const std::string &name);
    /**
     * 获取请求标识
     * @return 获取请求标识
     */
    UInt32 GetRequestId() const;
    /**
     * 设置请求标识
     * @params 要设置的请求标识
     */
    void SetRequestId(UInt32 requestId);
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 action_;
    UInt32 jid_;
    std::string resource_;
    UInt8 status_;
    std::string show_;
    std::string name_;
    UInt32 requestId_;
};
}
namespace chatp {
/**
 * 出席状态操作类型
 */
namespace PresenceAction {
    /**
     * 广播，向所有好友发送出席状态
     */
    const UInt8 BROADCAST = 0x00;
    /**
     * 转发，向指定好友发送出席状态
     */
    const UInt8 FORWARD = 0x01;
    /**
     * 探测，探测指定好友的出席状态
     */
    const UInt8 PROBE = 0x02;
    /**
     * 更新用户显示名
     */
    const UInt8 RENAME = 0x03;
}
}
namespace chatp {
/**
 * 出席状态
 */
namespace PresenceStatus {
    /**
     * 自定义状态
     */
    const UInt8 CUSTOM = 0x00;
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
namespace chatp {
/**
 * Roster数据包
 */
class Roster : public ark::Packet {
public:
    /**
     * 构造函数
     */
    Roster();
    /**
     * 析构函数
     */
    virtual ~Roster();
public:
    /**
     * 获取操作类型
     * @see RosterAction
     * @return 操作类型
     */
    UInt8 GetAction() const;
    /**
     * 设置操作类型
     * @see RosterAction
     * @param action 要设置的操作类型
     */
    void SetAction(UInt8 action);
    /**
     * 获取群组列表
     * @return 群组列表
     */
    const Groups &GetGroups() const;
    /**
     * 获取群组列表
     * @return 群组列表
     */
    Groups &GetGroups();
    /**
     * 获取请求标识
     * @return 获取请求标识
     */
    UInt32 GetRequestId() const;
    /**
     * 设置请求标识
     * @params 要设置的请求标识
     */
    void SetRequestId(UInt32 requestId);
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 action_;
    Groups groups_;
    UInt32 requestId_;
};
}
namespace chatp {
/**
 * 好友名单操作
 */
namespace RosterAction {
    /**
     * 读取好友名单
     */
    const UInt8 LOAD = 0x00;
    /**
     * 创建好友分组
     */
    const UInt8 CREATE_GROUP = 0x01;
    /**
     * 重命名好友分组
     */
    const UInt8 RENAME_GROUP = 0x02;
    /**
     * 删除好友分组
     */
    const UInt8 REMOVE_GROUP = 0x03;
    /**
     * 创建好友
     */
    const UInt8 CREATE_ROSTER = 0x04;
    /**
     * 修改好友备注
     */
    const UInt8 REMARK_ROSTER = 0x05;
    /**
     * 移动好友
     */
    const UInt8 MOVE_ROSTER = 0x06;
    /**
     * 删除好友
     */
    const UInt8 REMOVE_ROSTER = 0x07;
}
}
namespace chatp {
/**
 * 好友订阅数据包
 */
class Subscribe : public ark::Packet {
public:
    /**
     * 构造函数
     */
    Subscribe();
    /**
     * 析构函数
     */
    virtual ~Subscribe();
public:
    /**
     * 获取操作类型
     * @see SubscribeAction
     * @return 操作类型
     */
    UInt8 GetAction() const;
    /**
     * 设置操作类型
     * @see SubscribeAction
     * @param action 要设置的操作类型
     */
    void SetAction(UInt8 action);
    /**
     * 获取用户标识
     * @return 用户标识
     */
    UInt32 GetJid() const;
    /**
     * 设置用户标识
     * @param jid 要设置的用户标识
     */
    void SetJid(UInt32 jid);
    /**
     * 获取用户名
     * @return 用户名
     */
    const std::string &GetName() const;
    /**
     * 设置用户名
     * @param name 要设置的用户名
     */
    void SetName(const std::string &name);
    /**
     * 获取请求发送方的用户名
     * @return 请求发送方的用户名
     */
    const std::string &GetMyname() const;
    /**
     * 设置请求发送方的用户名
     * @param 要设置的请求发送方的用户名
     */
    void SetMyname(const std::string &myname);
    /**
     * 获取好友的备注
     * @return 好友的备注
     */
    const std::string &GetRemark() const;
    /**
     * 设置好友备注
     * @param remark 要设置的好友备注
     */
    void SetRemark(const std::string &remark);
    /**
     * 获取好友分组标识
     * @return 好友分组标识
     */
    UInt32 GetGroupId() const;
    /**
     * 设置好友分组标识
     * @param groupId 要设置的好友分组
     */
    void SetGroupId(UInt32 groupId);
    /**
     * 获取问候消息
     * @return 问候消息
     */
    const std::string &GetGreeting() const;
    /**
     * 设置问候消息
     * @param greeting 要设置的问候消息
     */
    void SetGreeting(const std::string &greeting);
    /**
     * 获取请求标识
     * @return 获取请求标识
     */
    UInt32 GetRequestId() const;
    /**
     * 设置请求标识
     * @param 要设置的请求标识
     */
    void SetRequestId(UInt32 requestId);
    /**
     * 获取时间戳
     * @return 时间戳
     */
    UInt32 GetTimestamp() const;
    /**
     * 设置时间戳
     * @param timestamp 时间戳
     */
    void SetTimestamp(UInt32 timestamp);
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 action_;
    UInt32 jid_;
    std::string name_;
    std::string myname_;
    std::string remark_;
    UInt32 groupId_;
    std::string greeting_;
    UInt32 requestId_;
    UInt32 timestamp_;
};
}
namespace chatp {
/**
 * 订阅操作类型
 */
namespace SubscribeAction {
    /**
     * 发送请求
     */
    const UInt8 REQUEST = 0x00;
    /**
     * 取消请求
     */
    const UInt8 CANCEL = 0x01;
    /**
     * 接受请求
     */
    const UInt8 ACCEPT = 0x02;
    /**
     * 拒绝请求
     */
    const UInt8 REJECT = 0x03;
    /**
     * 成功发送请求
     */
    const UInt8 REQUESTED = 0x04;
    /**
     * 成功取消好友请求
     */
    const UInt8 CANCELED = 0x05;
    /**
     * 成功接受好友请求
     */
    const UInt8 ACCEPTED = 0x06;
    /**
     * 成功拒绝好友请求
     */
    const UInt8 REJECTED = 0x07;
}
}
namespace chatp {
/**
 * IQ协议的类型
 */
namespace IQType {
    /**
     * 转发IQ到其他用户
     */
    const UInt8 FORWARD = 0x00;
    /**
     * 确认收到的IQ包(Client -> Client)
     */
    const UInt8 ACK = 0x01;
    /**
     * 转发的用户不在线，转发失败(Server -> Client)
     */
    const UInt8 NOT_ARRIVE_ACK = 0x02;
}
}
#endif /* CHATP_API_HPP */
