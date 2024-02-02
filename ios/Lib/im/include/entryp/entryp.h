#ifndef ENTRYP_API_HPP
#define ENTRYP_API_HPP
namespace entryp {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
/**
 * @file entryp/entryp.h
 * @author 陈梓文 
 */
#ifndef API
#include "ark/ark.h"
#endif /* API */
#ifndef ENTRYP_API_HPP
#include "connectservice.hpp"
#include "connectserviceresult.hpp"
#include "login.hpp"
#include "loginresult.hpp"
#include "kickoff.hpp"
#include "rttrequest.hpp"
#include "rttresponse.hpp"
#include "setproperty.hpp"
#include "devicetype.hpp"
#endif /* ENTRYP_API_HPP */
/**
 * @file entryp/entryp.h
 * @author 陈梓文 
 */
namespace entryp {
/**
 * 连接服务
 */
class ConnectService : public ark::Packet {
public:
    enum { TYPE = 0x10 };
public:
    //! 服务参数
    typedef std::map<std::string, std::string> Params;
public:
    /**
     * 构造函数
     */
    ConnectService();
    /**
     * 虚构函数
     */
    virtual ~ConnectService();
public:
    /**
     * 获取连接的服务类型
     */
    UInt32 GetServiceType() const;
    /**
     * 设置连接的服务类型
     * @param serviceType 服务类型
     */
    void SetServiceType(UInt32 serviceType);
    /**
     * @brief 获取连接服务的其他参数
     * @return
     */
    Params GetServiceParams() const;
    /**
     * @brief 设置连接服务的其他参数
     * @param params
     */
    void SetServiceParams(const Params& params);
public:
    /**
     * 获取类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解包
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 服务类型
     */
    UInt32 serviceType_;
    //! 服务参数
    Params serviceParams_;
};
}
namespace entryp {
/**
 * 连接服务回复
 */
class ConnectServiceResult : public ark::Packet {
public:
    enum { TYPE = 0x11 };
    enum Result {
        Success,
        Failed
    };
public:
    typedef std::map<UInt64, ark::Any> Dictionary;
public:
    /**
     * 构造函数
     */
    ConnectServiceResult();
    /**
     * 虚构函数
     */
    virtual ~ConnectServiceResult();
public:
    /**
     * 获取连接返回码
     * @return 结果
     */
    UInt32 GetRescode() const;
    /**
     * 设置连接结果
     * @param rescode 返回码
     */
    void SetRescode(UInt32 rescode);
    /**
     * 获取连接的服务类型
     * @param 服务类型
     */
    UInt32 GetService() const;
    /**
     * 设置连接的服务类型
     * @param service 服务类型
     */
    void SetService(UInt32 service);
    /**
     * 获取扩展参数
     * @param 可变参数
     */
    Dictionary &GetParams();
    /**
     * 设置扩展参数
     * @param params 可扩展参数
     */
    void SetParams(const Dictionary &params);
public:
    /**
     * 获取类型
     * @return 类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /*
     * 解包
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 结果
     */
    UInt32 rescode_;
    /**
     * 连接的类型
     */
    UInt32 service_;
    /**
     * 可变参数
     */
    Dictionary params_;
};
}
namespace entryp {
/**
 * 客户端登录协议 
 */
class Login : public ark::Packet {
public:
    typedef std::map<std::string, ark::Any> Params;
public:
    enum { TYPE = 0x00 };
public:
    /**
     * 构造函数
     */
    Login();
    /**
     * 虚构函数
     */
    virtual ~Login();
public:
    /**
     * 获取登录帐号
     */
    const std::string &GetAccount() const;
    /**
     * 设置登录帐号
     */
    void SetAccount(const std::string &account);
    /**
     * 获取登录密码
     */
    const std::string &GetPassword() const;
    /**
     * 设置登录密码
     */
    void SetPassword(const std::string &password);
    /**
     * 获取客户端版本
     */
    const std::string &GetVersion() const;
    /**
     * 设置客户端版本
     */
    void SetVersion(const std::string &version);
    /**
     * 获取登录类型（普通登录，一键登录，FB登录等等）
     */
    const UInt32 GetLoginType() const;
    /**
     * 设置登录类型
     */
    void SetLoginType(UInt32 loginType);
    /**
     * 获取登录参数（机器码等等）
     */
    const Params &GetParams() const;
    /**
     * 设置登录类型
     */
    void SetParams(const Params &params);
public:
    /**
     * 获取协议类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解包
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 帐号
     */
    std::string account_;
    /**
     * 密码
     */
    std::string password_;
    /**
     * 版本
     */
    std::string version_;
    /**
     * 登录类型
     */
    UInt32 loginType_;
    /** 
     * 登录参数
     */
    Params params_;
};
}
namespace entryp {
/**
 * 登录结果
 */
class LoginResult : public ark::Packet {
public:
    enum { TYPE = 0x01 };
    typedef std::map<std::string, ark::Any> Property;
public:
    /**
     * 构造函数
     */
    LoginResult();
    /**
     * 虚构函数
     */
    virtual ~LoginResult();
public:
    /**
     * 获取登录结果
     * @return 登录结果
     */
    UInt32 GetRescode() const;
    /**
     * 设置登录结果
     * @return 登录结果
     */
    void SetRescode(UInt32 rescode);
    /**
     * 获取登录成功的用户UId
     * @return 用户UId
     */
    UInt32 GetUId() const;
    /**
     * 设置用户UId
     * @param 用户UId
     */
    void SetUId(UInt32 uid);
    /**
     * 获取登录成功的用户信息
     * @return 用户信息
     */
    const Property &GetProperty() const;
    /**
     * 设置登录成功后的用户信息
     * @param property 用户信息
     */
    void SetProperty(const Property &property);
public:
    /**
     * 获取类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解包
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 登录结果
     */
    UInt64 rescode_;
    /**
     * 用户UId
     */
    UInt64 uid_;
    /**
     * 用户信息
     */
    Property property_;
};
}
namespace entryp {
/**
 * 踢出在entry的用户
 */
class Kickoff : public ark::Packet {
public:
    enum { TYPE = 0x00 };
public:
    /**
     * 构造函数
     */
    Kickoff();
    /**
     * 虚构函数
     */
    virtual ~Kickoff();
public:
    /**
     * 获取用户UId
     * @return 用户UId
     */
    UInt32 GetUserId() const;
    /**
     * 设置用户UId
     * @param userId 用户UId
     */
    void SetUserId(UInt32 userId);
public:
    /**
     * 获取类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解包
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 用户UId
     */
    UInt32 userId_;
};
}
namespace entryp {
/**
 * RTT请求包
 */
class RTTRequest : public ark::Packet {
public:
    enum { TYPE = 0x12 };
public:
    /**
     * 构造函数
     */
    RTTRequest();
    /**
     * 虚构函数
     */
    virtual ~RTTRequest();
public:
    /**
     * 获取时间
     * @return 时间
     */
    UInt32 GetTime() const;
    /**
     * 设置时间
     * @param time 时间
     */
    void SetTime(UInt64 time);
public:
    /**
     * 获取类型
     * @return 类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     * @param writer 打包接口
     * @return 打包是否成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解包
     * @param reader 解包接口
     * @return 解包是否成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 时间
     */
    UInt64 time_;
};
}
namespace entryp {
class RTTResponse : public ark::Packet {
public:
    enum { TYPE = 0x13 };
public:
    /**
     * 构造函数
     */
    RTTResponse();
    /**
     * 虚构函数
     */
    virtual ~RTTResponse();
public:
    /**
     * 获取时间
     * @return 时间
     */
    UInt32 GetTime() const;
    /**
     * 设置时间
     * @param time 时间
     */
    void SetTime(UInt64 time);
public:
    /**
     * 获取类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解压
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 时间
     */
    UInt64 time_;
};
}
namespace entryp {
/**
 * 设置属性 
 */
class SetProperty : public ark::Packet {
public:
    enum { TYPE = 0x14 };
    enum Result {
        SUCCESS,
        FAILED
    };
public:
    typedef std::map<std::string, ark::Any> Params;
public:
    /**
     * 构造函数
     */
    SetProperty();
    /**
     * 虚构函数
     */
    virtual ~SetProperty();
public:
    /**
     * 获取结果
     * @return 结果
     */
    UInt32 GetResult() const;
    /**
     * 设置结果
     * @param result 结果
     */
    void SetResult(UInt32 result);
    /**
     * 获取Context
     * @return context
     */
    UInt32 GetContext() const;
    /**
     * 设置结果
     * @param context 上下文
     */
    void SetContext(UInt32 context);
    /**
     * 设置设备Token
     */
    void SetDeviceToken(const std::string &deviceToken);
    /**
     * 设置设备类型: android/ios
     */
    void SetDeviceType(const std::string &deviceType);
    /**
     * 获取设备Token
     */
    const bool GetDeviceToken(std::string &deviceToken) const;
    /**
     * 获取设备类型: android/ios
     */
    const bool GetDeviceType(std::string &deviceType) const;
public:
    /**
     * 获取类型
     */
    virtual UInt32 GetType() const;
    /**
     * 打包
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 解包
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    /**
     * 结果
     */
    UInt32 result_;
    /**
     * 上下文
     */
    UInt32 context_;
    /**
     * 服务类型
     */
    Params params_;
};
}
namespace entryp {
namespace DeviceType {
    const UInt8 TYPE_ANDROID = 0;
    const UInt8 TYPE_IOS = 1;
    /**
     * 判断设备类型是否有效果
     * @param deviceType 设备类型
     * @return 是否有效果 
     */
    bool IsDeviceTypeValid(UInt8 deviceType);
}
}
#endif /* ENTRYP_API_HPP */
