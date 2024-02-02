#ifndef LOCATEP_API_HPP
#define LOCATEP_API_HPP
namespace locatep {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
/**
 * @file locatep/locatep.h
 * @author 古原辉 
 */
#include <ark/ark.h>
#endif /* API */
#ifndef LOCATEP_API_HPP
#include "locationclean.hpp"
#include "locationcleanreply.hpp"
#include "locationupdate.hpp"
#include "locationupdatereply.hpp"
#include "nearbyquery.hpp"
#include "nearbyreply.hpp"
#include "packettype.hpp"
#include "position.hpp"
#include "servicetype.hpp"
#include "userinfo.hpp"
#include "userlocation.hpp"
#include "rescode.hpp"
#include "sextype.hpp"
#endif /* LOCATEP_API_HPP */
namespace locatep {
/**
 * 此类实现定位信息清空
 */
class LocationClean : public ark::Packet {
public:
    /**
     * 构造函数
     */
    LocationClean();
    /**
     * 析构函数
     */
    virtual ~LocationClean();
    /**
     * 设置用户id
     * @parma uid 用户id
     */
    void SetUserId(UInt32 uid);
    /**
     * 获取用户ID
     * @return 用户id
     */
    UInt32 GetUserId() const;
    /**
     * 设置请求id
     * @parma id id
     */
    void SetRequestId(UInt32 id);
    /**
     * 获取请求ID
     * @return id
     */
    UInt32 GetRequestId() const;
public:
    /**
     * 获取包消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 uid_;
    UInt32 requestId_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
/**
 * 此类实现定位信息清空应答
 */
class LocationCleanReply : public ark::Packet {
public:
    /**
     * 构造函数
     */
    LocationCleanReply();
    /**
     * 析构函数
     */
    virtual ~LocationCleanReply();
    /**
     * 设置结果
     * @parma result 结果
     */
    void SetResult(UInt32 result);
    /**
     * 获取结果
     * @return 结果
     */
    UInt32 GetResult() const;
    /**
     * 设置请求id
     * @parma id id
     */
    void SetRequestId(UInt32 id);
    /**
     * 获取请求ID
     * @return id
     */
    UInt32 GetRequestId() const;
public:
    /**
     * 获取包消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 result_;
    UInt32 requestId_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
/**
 * 此类实现地理位置信息
 */
class Position : public ark::Data {
public:
    /**
     * 缺省构造函数
     */
    Position();
    /**
     * 构造函数
     */
    Position(double latitude, double longitude);
    /**
     * 析构函数
     */
    virtual ~Position();
    /**
     * 比较两个位置是否相等
     * @param dest 目标位置
     * @return 返回是否相等,true表示相等
     */
    bool operator == (const Position &dest) const;
    /**
     * 设置地理位置的经度
     * @param para 经度(double)
     */
    void SetLongitude(double para);
    /**
     * 获取地理位置的经度
     * @return 经度(double)
     */
    double GetLongitude() const;
    /**
     * 设置地理位置的纬度
     * @param para 纬度
     */
    void SetLatitude(double para);
    /**
     * 获取地理位置的纬度
     * @return 纬度(double)
     */
    double GetLatitude() const;
public:
    virtual void Form(ark::DataForm &form) const;
    virtual bool Encode(ark::PacketWriter &writer) const;
    virtual bool Decode(ark::PacketReader &reader);
private:
    double latitude_;
    double longitude_;
};
}
namespace locatep {
class LocationUpdate : public ark::Packet {
public:
    LocationUpdate();
    virtual ~LocationUpdate();
    void SetUserId(UInt32 uid);
    UInt32 GetUserId() const;
    /**
     * 设置用户自己的性别
     * @param 性别 
     */
    void SetSex(UInt8 type);
    /**
     * 获取用户自己的性别
     * @return 用户性别
     */
    UInt8 GetSex() const;
    /**
     * 设置用户的地理位置
     * @param pos 位置信息
     */
    void SetPos(const Position &pos);
    /**
     * 获取用户的地理位置
     * @return 位置信息
     */
    const Position &GetPos() const;
    /**
     * 设置请求id
     * @parma id id
     */
    void SetRequestId(UInt32 id);
    /**
     * 获取请求ID
     * @return id
     */
    UInt32 GetRequestId() const;
public:
    /**
     * 获取包消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 uid_;
    UInt8 sex_;
    UInt32 requestId_;
    Position position_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
class LocationUpdateReply : public ark::Packet {
public:
    LocationUpdateReply();
    virtual ~LocationUpdateReply();
    void SetResult(UInt32 result);
    UInt32 GetResult() const;
    /**
     * 设置请求id
     * @parma id id
     */
    void SetRequestId(UInt32 id);
    /**
     * 获取请求ID
     * @return id
     */
    UInt32 GetRequestId() const;
public:
    /**
     * 获取包消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 result_;
    UInt32 requestId_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
/**
 * 此类实现附近用户查询包
 */
class NearbyQuery : public ark::Packet {
public:
    /**
     * 缺省构造函数
     */
    NearbyQuery();
    /**
     * 析构函数
     */
    virtual ~NearbyQuery();
    /**
     * 设置用户id
     * @param uid 用户id
     */
    void SetUserId(UInt32 uid);
    /**
     * 获取用户id
     */
    UInt32 GetUserId() const;
    /**
     * 设置用户的地理位置
     * @param pos 位置信息
     */
    void SetPos(const Position &pos);
    /**
     * 获取用户的地理位置
     * @return 位置信息
     */
    const Position &GetPos() const;
    /**
     * 设置查询的最大距离
     * @param distance 距离,单位为米
     */
    void SetDistance(UInt32 distance);
    /**
     * 获取查询的最大距离
     * @return 距离,单位为米
     */
    UInt32 GetDistance() const;
    /**
     * 设置查询的最大用户数
     * @param count 用户数
     */
    void SetMaxCount(UInt32 count);
    /**
     * 获取查询的最大用户数
     * @return 用户数
     */
    UInt32 GetMaxCount() const;
    /**
     * 设置用户查询条件中的性别
     * @param 性别 
     */
    void SetQuerySex(UInt8 type);
    /**
     * 获取用户查询条件中的性别
     * @return 性别
     */
    UInt8 GetQuerySex() const;
    /**
     * 设置查询的最久远刷新时间
     * @param minute 时间,分钟为单位
     */
    void SetTime(UInt32 minute);
    /**
     * 获取查询的最久远刷新时间
     * @return 时间,分钟为单位
     */
    UInt32 GetTime() const;
    /**
     * 设置已经读取的用户数
     * @param count 用户数
     */
    void SetReadedCount(UInt32 count);
    /**
     * 获取已经读取的用户数
     * @return 用户数
     */
    UInt32 GetReadedCount() const;
    /**
     * 设置请求id
     * @parma id id
     */
    void SetRequestId(UInt32 id);
    /**
     * 获取请求ID
     * @return id
     */
    UInt32 GetRequestId() const;
    /**
     * dump 包内容
     * @return 字符串
     */
    std::string Dump() const;
public:
    /**
     * 获取包消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 uid_;
    Position position_;
    UInt32 maxDistance_;
    UInt32 maxCount_;
    UInt32 maxTime_;
    UInt8 querySex_;
    UInt32 readedCount_;
    UInt32 requestId_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
/**
 * 此类实现用户信息
 */
class UserInfo {
public:
    /**
     * 缺省构造函数
     */
    UserInfo();
    /**
     * 构造函数
     * @param uid 用户id
     * @param distance 用户距离
     * @param time 用户刷新的时间
     */
    UserInfo(UInt32 uid, UInt32 distance, UInt32 time, UInt8 sex);
    /**
     * 析构函数
     */
    ~UserInfo();
    /**
     * 设置用户id
     * @param uid 用户id
     */
    void SetUserId(UInt32 uid);
    /**
     * 获取用户id
     * @return 用户id
     */
    UInt32 GetUserId() const;
    /**
     * 设置用户的距离
     * @param distance 距离
     */
    void SetDistance(UInt32 distance);
    /**
     * 获取用户的距离
     * @return 距离
     */
    UInt32 GetDistance() const;
    /**
     * 设置用户的刷新时间,以分钟为单位
     * @param time 时间
     */
    void SetTime(UInt32 time);
    /**
     * 获取用户的刷新时间,以分钟为单位
     * @return 时间
     */
    UInt32 GetTime() const;
    /**
     * 设置用户的性别
     * @param type 性别 
     */
    void SetSex(UInt8 type);
    /**
    * 获取用户的性别
     * @return 性别 
     */
    UInt8 GetSex() const;
private:
    UInt32 uid_;
    UInt32 distance_;
    UInt32 time_;
    UInt8 sex_;
};
}
namespace locatep {
/**
 * 此类实现用户的定位信息
 */
class UserLocation : public ark::Data {
public:
    /**
     * 缺省构造函数
     */
    UserLocation();
    /**
     * 构造函数
     * @param id 用户id
     * @param distance 用户距离
     * @param time 用户刷新时间
     */
    UserLocation(UInt32 uid, UInt32 distance, UInt32 time, UInt8 sex);
    virtual ~UserLocation();
    /**
     * 获取用户id
     * @return 用户id
     */
    UInt32 GetUId() const;
    /**
     * 获取用户的距离
     * @return 用户距离
     */
    UInt32 GetDistance() const;
    /**
     * 获取用户的最近刷新距离现在的时间
     * @return 时间,单位为秒
     */
    UInt32 GetTime() const;
    /**
     * 获取用户的性别
     * @return 性别
     */
    UInt8 GetSex() const;
    /**
     * 获取用户的信息,包含ID,距离,时间
     * @return 用户信息
     */
    UserInfo GetUserInfo() const;
public:
    virtual void Form(ark::DataForm&) const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UserInfo user_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
/**
 * 此类实现附近用户应答包
 */
class NearbyReply : public ark::Packet {
public:
    /**
     * 用户定位信息列表类型定义
     */
    typedef std::list<UserLocation> Locations;
public:
    /**
     * 缺省构造函数
     */
    NearbyReply();
    /**
     * 析构函数
     */
    virtual ~NearbyReply();
    /**
     * 设置结果
     * @parma result 结果
     */
    void SetResult(UInt32 result);
    /**
     * 获取结果
     * @return 结果
     */
    UInt32 GetResult() const;
    /**
     * 获取用户定位信息列表的引用
     * @return 定位信息列表的引用
     */
    Locations &GetLocations();
    /**
     * 获取用户定位信息列表的常量引用
     * @return 定位信息列表的常量引用
     */
    const Locations &GetLocations() const;
    /**
     * 设置请求id
     * @parma id id
     */
    void SetRequestId(UInt32 id);
    /**
     * 获取请求ID
     * @return id
     */
    UInt32 GetRequestId() const;
    /**
     * dump 包内容
     * @retrun 字符串
     */
    std::string Dump() const;
public:
    /**
     * 获取包消息类型
     * @return 消息类型
     */
    virtual UInt32 GetType() const;
    /**
     * 将包编码到packetwriter
     * @param writer 写缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Encode(ark::PacketWriter &writer) const;
    /**
     * 将packetreader解码到包
     * @param reader 读缓冲区
     * @return 成功与否,true表示成功
     */
    virtual bool Decode(ark::PacketReader &reader);
private:
    UInt32 result_;
    Locations locations_;
    UInt32 requestId_;
    typedef std::map<UInt32, ark::Any> Directory;
    Directory reserve_;
};
}
namespace locatep {
namespace PacketType {
    const UInt32 QUERY = 0;
    const UInt32 QUERY_REPLY = 1;
    const UInt32 UPDATE = 2;
    const UInt32 UPDATE_REPLY = 3;
    const UInt32 CLEAN = 4;
    const UInt32 CLEAN_REPLY = 5;
}
}
namespace locatep {
/**
 * 此类定义定位业务类型
 */
namespace ServiceType {
    /**
     * 定位业务类型
     */
    const UInt8 TYPE = 2;
};
}
namespace locatep {
namespace ResCode {
    const UInt32 OK = 0;
    const UInt32 UNKNOWN_ERROR = 1;
    const UInt32 SERVER_INNER_ERROR = 2;
    const UInt32 TIMEOUT = 3;
}
}
namespace locatep {
namespace SexType {
    const UInt8 ALL = 0;
    const UInt8 ANONYMOUS = 0;
    const UInt8 MAN = 1;
    const UInt8 WOMAN = 2;
}
}
#endif /* LOCATEP_API_HPP */
