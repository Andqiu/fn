#ifndef GATEWAYP_API_HPP
#define GATEWAYP_API_HPP
namespace gatewayp {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
#include <ark/ark.h>
#endif /* API */
#ifndef GATEWAYP_API_HPP
#include "askway.hpp"
#include "askwayrescode.hpp"
#include "askwayresult.hpp"
#include "fingerprint.hpp"
#include "linkinfo.hpp"
#endif /* GATEWAYP_API_HPP */
namespace gatewayp {
/**
 * 问路包,获取link的ip和端口
 */
class AskWay : public ark::Packet {
public:
    enum { TYPE = 0x00 };
    enum { AREA_AUTO = 0x00 };
    /**
     * 参数的类型定义
     */
    typedef std::map<std::string, ark::Any> Object;
public:
    /**
     * 默认构造函数
     */
    AskWay();
    /**
     * 默认析构函数
     */
    virtual ~AskWay();
public:
    /**
     * 设置客户端的版本
     * @param key 字段名
     * @param val 字段值
     */
    void SetParam(const std::string &key, const std::string &val);
    /**
     * 设置客户端的版本
     * @param 版本号信息
     */
    void SetVersion(const std::string &version);
    /**
     * 获取客户端的版本
     * @return 版本号信息
     */
    const std::string &GetVersion() const;
    /**
     * 设置客户端的平台
     * @param ios/android
     */
    void SetPlatform(const std::string &version);
    /**
     * 获取客户端的平台
     * @return ios/android
     */
    const std::string &GetPlatform() const;
    /**
     * 获取Ark版本
     * @return 版本号信息
     */
    const std::string &GetArkVersion() const;
    /**
     * 获取Arc版本
     * @return 版本号信息
     */
    const std::string &GetArcVersion() const;
    /**
     * 获取rtalk版本
     * @return 版本号信息
     */
    const std::string &GetRtalkVersion() const;
    /**
     * 设置客户端的区域信息
     * @param 区域信息
     */
    void SetArea(UInt8 area);
    /**
     * 获取客户端的区域
     * @return 区域信息
     */
    UInt8 GetArea() const;
    /**
     * 设置客户端帐号的类型
     * @param 帐号类型
     */
    void SetAccountType(UInt32 type);
    /**
     * 获取客户端帐号的类型
     * @return 帐号类型
     */
    UInt32 GetAccountType() const;
    /**
     * 设置客户端的帐号
     * @param 帐号信息
     */
    void SetAccount(const std::string &account);
    /**
     * 获取客户端的帐号
     * @return 帐号信息
     */
    const std::string &GetAccount() const;
    /**
     * 获取对象的引用
     * @return 对象的引用
     */
    const Object &GetObject() const;
    /**
     * 获取对象的引用
     * @return 对象的引用
     */
    Object &GetObject();
public:
    /**
     * 获取包的消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 消息编码到writer
     * @param writer 写入缓冲区
     * @return 是否成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 从reader解码消息
     * @param reader 读入缓冲区
     * @return 是否成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 area_;
    UInt32 type_;
    std::string version_;
    std::string ark_version_;
    std::string arc_version_;
    std::string rtalk_version_;
    std::string account_;
    std::string platform_;
    Object data_;
};
}
namespace gatewayp {
/**
 * 问路应答的应答码定义
 */
namespace AskwayResCode {
/**
 * 成功
 */
const UInt32 RESULT_OK = 0;
/**
 * 失败
 */
const UInt32 RESULT_FAILED_START = 10000;
const UInt32 RESULT_UNKNOWN_ERR = RESULT_FAILED_START;
const UInt32 RESULT_UNKNOWN_PROTO = RESULT_FAILED_START + 1;
const UInt32 RESULT_NO_ENTRY = RESULT_FAILED_START + 2;
}
}
namespace gatewayp {
/**
 * link服务器的地址信息
 */
class LinkInfo : public ark::Data {
public:
    /**
     * 默认构造函数
     */
    LinkInfo();
    /**
     * 单参数的构造函数
     * @param ip IP地址
     * @param port 端口地址
     */
    LinkInfo(UInt32 ip, UInt16 port);
    /**
     * 获取IP地址
     * @return ip地址
     */
    UInt32 GetIp() const;
    /**
     * 获取端口号
     * @return 端口号
     */
    UInt16 GetPort() const;
protected:
    virtual void Form(ark::DataForm &form) const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 ip_;
    UInt16 port_;
};
}
namespace gatewayp {
/**
 * 问路应答包
 */
class AskWayResult: public ark::Packet {
public:
    enum { TYPE = 0x01 };
public:
    typedef std::list<LinkInfo> LinkList;
    /**
     * 参数的类型定义
     */
    typedef std::map<std::string, ark::Any> Object;
public:
    /**
     * 默认构造函数
     */
    AskWayResult();
    /**
     * 默认析构函数
     */
    virtual ~AskWayResult();
public:
    /**
     * 设置结果值
     * @param result 结果
     */
    void SetResult(UInt32 result);
    /**
     * 获取结果
     * @return 结果
     */
    UInt32 GetResult() const;
    /**
     * 获取link服务器列表的引用
     * @return 服务器列表的引用
     */
    LinkList &GetLinkInfo();
    /**
     * 获取link服务器列表的常量引用
     * @return 服务器列表的常量引用
     */
    const LinkList &GetLinkInfo() const;
    /**
     * 设置连接link服务器的连接类型
     * @param 连接类型
     */
    void SetConnectionType(UInt8 type);
    /**
     * 获取连接link服务器的连接类型
     * @return 连接类型
     */
    UInt8 GetConnectionType() const;
    /**
     * 获取参数对象的引用
     * @return 对象的引用
     */
    const Object &GetParaObject() const;
    /**
    *设置是否使用kcp
    */
    virtual void SetKcp(UInt8 useKcp);
    /**
    * 是否使用kcp
    */
    UInt8 IsKcp() const;
    void SetProxyHost(const std::string &host);
    std::string GetProxyHost() const;
    void SetProxyPort(UInt16 port);
    UInt16 GetProxyPort() const;
public:
    /**
     * 获取消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 消息编码到writer
     * @param writer 写入缓冲区
     * @return 是否成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 从reader解码消息
     * @param reader 读入缓冲区
     * @return 是否成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt8 type_;
    UInt32 result_;
    LinkList linkInfos_;
    Object paraObject_;
    UInt8 kcp_;
    std::string proxyHost_;
    UInt16 proxyPort_;
};
}
namespace gatewayp {
class Fingerprint {
public:
    static std::string Encode();
    static bool Decode(const std::string &para);
};
}
#endif /* GATEWAYP_API_HPP */
