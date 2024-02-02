#ifndef ARK_API_HPP
#define ARK_API_HPP
namespace ark {
    extern const char *MAJOR_VERSION;
    extern const char *MINOR_VERSION;
    extern const char *BUILD_VERSION;
    extern const char *VERSION;
}
#ifndef API
/**
 * @file ark/ark.h
 * @author 喻扬
 */
#include <list>
#include <set>
#include <string>
#include <vector>
#include <arc/arc.h>
#include <ssl/ssl.h>
#endif /* API */
#ifndef ARK_API_HPP
#include "acceptor.hpp"
#include "acceptorhandler.hpp"
#include "any.hpp"
#include "connection.hpp"
#include "connectionhandler.hpp"
#include "connectiontype.hpp"
#include "data.hpp"
#include "dataform.hpp"
#include "datatype.hpp"
#include "emptypacket.hpp"
#include "export.hpp"
#include "flow.hpp"
#include "flowhandler.hpp"
#include "packet.hpp"
#include "packetreader.hpp"
#include "packetwriter.hpp"
#endif /* ARK_API_HPP */
namespace ark {
class AcceptorHandler;
/**
 * 此类用于监听端口，并且接受传入连接
 */
class Acceptor {
public:
    /**
     * 监听指定的地址
     * @param address 要监听的地址
     * @return 返回是否成功绑定到指定地址，如果返回false，可能是端口被占用了
     */
    virtual bool Listen(const arc::SocketAddress &address) = 0;
    /**
     * 关闭此监听器
     */
    virtual void Close() = 0;
    /**
     * 设置处理程序
     * @param handler 要设置的处理程序
     */
    virtual void SetHandler(AcceptorHandler *handler) = 0;
};
}
namespace ark {
class Acceptor;
class Connection;
/**
 * 监听器的处理程序
 */
class AcceptorHandler {
public:
    /**
     * 有新的传入连接（已经收到IHello包）
     * @param connection 传入连接
     * @param fingerprint 对端的连接标识
     * @param acceptor 监听器
     */
    virtual void OnConnection(Connection *connection, const std::string &fingerprint, Acceptor *acceptor) = 0;
    /**
     * 监听器关闭（主动关闭不会触发此函数）
     * @param acceptor 监听器
     */
    virtual void OnClose(Acceptor *acceptor) = 0;
};
}
namespace ark {
class PacketReader;
class PacketWriter;
/**
 * 表示Ark协议的任意基本类型
 */
class Any {
public:
    /**
     * 构造一个空的对象
     */
    Any();
    /**
     * 拷贝构造函数，其内部保存的数据是拷贝其值，而非引用
     */
    Any(const Any &other);
    /**
     * 构造一个数字类型
     */
    Any(UInt64 value);
    /**
     * 构造一个字符串类型
     */
    Any(const std::string &value);
    /**
     * 构造一个字符串类型
     */
    Any(const char *value);
    /**
     * 构造一个数组类型
     */
    Any(const std::vector<Any> &value);
    /**
     * 构造一个字典类型
     */
    Any(const std::map<UInt64, Any> &value);
    /**
     * 构造一个对象类型
     */
    Any(const std::map<std::string, Any> &value);
    /**
     * 析构函数
     */
    virtual ~Any();
public:
    /**
     * 清除数据
     */
    void Clear();
    /**
     * 获取数据类型
     */
    UInt8 GetType() const;
    /**
     * 用其他Any对象为此对象赋值
     * @param other 其他Any对象
     */
    Any &operator=(const Any &other);
    /**
     * 将此对象赋值为整数
     * @param value 指定的整数
     */
    Any &operator=(UInt64 value);
    /**
     * 将此对象赋值为字符串
     * @param value 指定的字符串
     */
    Any &operator=(const std::string &value);
    /**
     * 将此对象赋值为字符串
     * @param value 指定的字符串
     */
    Any &operator=(const char *value);
    /**
     * 将此对象赋值为数组
     * @param value 指定的数组
     */
    Any &operator=(const std::vector<Any> &value);
    /**
     * 将此对象赋值为字典
     * @param value 指定的字典
     */
    Any &operator=(const std::map<UInt64, Any> &value);
    /**
     * 将此对象赋值为对象
     * @param value 指定的对象
     */
    Any &operator=(const std::map<std::string, Any> &value);
    /**
     * 获取此对象的整数值
     * @note 此对象的值必须为整数才能获取
     */
    operator UInt64 &();
    /**
     * 获取此对象的字符串值
     * @note 此对象的值必须为字符串才能获取
     */
    operator std::string &();
    /**
     * 获取此对象的数组值
     * @note 此对象的值必须为数组才能获取
     */
    operator std::vector<Any> &();
    /**
     * 获取此对象的字典值
     * @note 此对象的值必须为字典才能获取
     */
    operator std::map<UInt64, Any> &();
    /**
     * 获取此对象的Object值
     * @note 此对象的值必须为Object才能获取
     */
    operator std::map<std::string, Any> &();
    /**
     * 获取此对象的整数值
     * @note 此对象的值必须为整数才能获取
     */
    operator const UInt64 &() const;
    /**
     * 获取此对象的字符串值
     * @note 此对象的值必须为字符串才能获取
     */
    operator const std::string &() const;
    /**
     * 获取此对象的数组值
     * @note 此对象的值必须为数组才能获取
     */
    operator const std::vector<Any> &() const;
    /**
     * 获取此对象的字典值
     * @note 此对象的值必须为字典才能获取
     */
    operator const std::map<UInt64, Any> &() const;
    /**
     * 获取此对象的Object值
     * @note 此对象的值必须为Object才能获取
     */
    operator const std::map<std::string, Any> &() const;
    /**
     * 读取整数值，若不为整数，则返回false
     * @param[out] value 保存读取的整数
     * @return 读取成功，返回true，否则，返回false
     */
    bool Get(UInt64 &value) const;
    /**
     * 读取字符串值，若不为字符串，则返回false
     * @param[out] value 保存读取的字符串
     * @return 读取成功，返回true，否则，返回false
     */
    bool Get(std::string &value) const;
    /**
     * 读取数组值，若不为数组，则返回false
     * @param[out] value 保存读取的数组
     * @return 读取成功，返回true，否则，返回false
     */
    bool Get(std::vector<Any> &value) const;
    /**
     * 读取字典值，若不为字典，则返回false
     * @param[out] value 保存读取的字典
     * @return 读取成功，返回true，否则，返回false
     */
    bool Get(std::map<UInt64, Any> &value) const;
    /**
     * 读取对象值，若不为对象，则返回false
     * @param[out] value 保存读取的对象
     * @return 读取成功，返回true，否则，返回false
     */
    bool Get(std::map<std::string, Any> &value) const;
    /**
     * 将其赋值为整数
     * @param 指定的值
     */
    void Set(UInt64 value);
    /**
     * 将其赋值为字符串
     * @param 指定的值
     */
    void Set(const std::string &value);
    /**
     * 将其赋值为字符串
     * @param 指定的值
     */
    void Set(const char *value);
    /**
     * 将其赋值为数组
     * @param 指定的值
     */
    void Set(const std::vector<Any> &value);
    /**
     * 将其赋值为字典
     * @param 指定的值
     */
    void Set(const std::map<UInt64, Any> &value);
    /**
     * 将其赋值为对象
     * @param 指定的值
     */
    void Set(const std::map<std::string, Any> &value);
private:
    UInt8 type_;
    void *value_;
};
}
namespace ark {
class ConnectionHandler;
class Flow;
class Lifetime;
class Packet;
/**
 * 表示连接的类
 */
class Connection {
public:
    /**
     * 返回此连接的本地端口
     * @return 此连接的本地端口
     */
    virtual arc::SocketAddress GetLocalAddress() const = 0;
    /**
     * 返回此连接的远程端口
     * @return 此连接的远程端口
     */
    virtual arc::SocketAddress GetRemoteAddress() const = 0;
    /**
     * 获取此连接是否已经成功建立
     * @return 此连接是否成功建立
     */
    virtual bool IsConnected() const = 0;
    /**
     * 接受此连接，并通知对端自己的标识，此操作只能作用于传入连接
     * @param fingerprint 自己的连接标识
     * @param plain 此连接是否使用明文传输，默认使用明文
     */
    virtual void Accept(const std::string &fingerprint, bool plain = true) = 0;
    /**
     * 中止此连接，所有未发送的数据都会丢弃
     */
    virtual void Abort() = 0;
    /**
     * 关闭此连接，但会将未发送的数据都发送完
     */
    virtual void Close() = 0;
    /**
     * 向对端发送一个数据包，此数据包通过默认的流传输
     * @param payload 要发送的数据
     * @param length 数据包的长度
     * @param lifetime 表示数据包的生存期，超时的数据包会被丢弃，如果为NULL，则表示数据包永不超时。
     */
    virtual void Send(const char *payload, UInt32 length, Lifetime *lifetime = NULL) = 0;
    /**
     * 向对端发送一个数据包，此数据包通过默认的流传输
     * @param packet 要发送的数据包
     * @param lifetime 表示数据包的生存期，超时的数据包会被丢弃，如果为NULL，则表示数据包永不超时。
     */
    virtual void Send(const Packet &packet, Lifetime *lifetime = NULL) = 0;
    /**
     * 创建流，只有传出连接才能创建流
     * @return 创建的流，如果创建失败，则返回NULL
     */
    virtual Flow *CreateFlow() = 0;
    /**
     * 启用原始包，收到数据包时回调函数会将原始的数据传递给Handler，而不解析数据包的类型
     * @param raw 是否启用原始包，默认为不启用
     */
    virtual void EnableRawPacket(bool raw) = 0;
    /**
     * 设置连接的处理程序
     * @param handler 处理程序
     */
    virtual void SetHandler(ConnectionHandler *handler) = 0;
};
}
namespace ark {
class Connection;
class Flow;
class PacketReader;
/**
 * 连接的处理程序
 */
class ConnectionHandler {
public:
    /**
     * 对端打开了一个流时的通知
     * @param flow 打开的流
     * @param connection 对应的连接
     */
    virtual void OnFlowOpen(Flow *flow, Connection *connection) = 0;
    /**
     * 当连接收到一个数据包时的处理函数，此时连接的EnableRawPacket应为false
     * @param payload 收到的数据
     * @param length 数据包的长度
     * @param connection 对应的连接
     */
    virtual void OnPacket(const char *payload, UInt32 length, Connection *connection) = 0;
    /**
     * 当连接收到一个数据包时的处理函数，此时连接的EnableRawPacket应为true
     * @param type 数据包的类型
     * @param reader 用于读取数据包
     * @param connection 收到数据包的连接
     */
    virtual void OnPacket(UInt32 type, PacketReader &reader, Connection *connection) = 0;
    /**
     * 连接建立时的通知，此时已经完成握手操作
     * @param connection 对应的连接
     */
    virtual void OnConnected(Connection *connection, const std::string &fingerprint) = 0;
    /**
     * 连接关闭时的通知，主动关闭不会触发此函数
     * @param connection 对应的连接
     */
    virtual void OnClosed(Connection *connection) = 0;
};
}
namespace ark {
/**
 * ark协议连接类型
 */
namespace ConnectionType {
    /**
     * 普通TCP连接
     */
    const UInt8 NORMAL = 0x00;
    /**
     * 简单TCP连接，无需握手
     */
    const UInt8 SIMPLE = 0x01;
    /**
     * UDP连接
     */
    const UInt8 UDP = 0x02;
 /*
	* NSOX
	*/
 const UInt8 NSOX = 0x03;
}
}
namespace ark {
class DataForm;
class PacketReader;
class PacketWriter;
/**
 * 此类表示扩展的数据
 */
class Data {
public:
    /**
     * 获取此数据的格式，需要依次向form传入Data中的数据
     * @param form 用于获取数据的格式
     */
    virtual void Form(DataForm &form) const = 0;
    /**
     * 编码此数据
     * @param writer 用于向缓冲区写入数据
     * @return 返回是否编码成功
     */
    virtual bool Encode(PacketWriter &writer) const = 0;
    /**
     * 解码此数据
     * @param reader 用于从缓冲区读取数据
     * @return 返回是否解码成功
     */
    virtual bool Decode(PacketReader &reader) = 0;
};
}
namespace ark {
/**
 * 用户获取Data类型的格式
 * @see Data
 */
class DataForm {
public:
    /**
     * 编码数据
     */
    template <typename T>
    DataForm &operator()(const T &value);
    virtual DataForm &operator()(const void *value, bool placeholder) = 0;
};
template <typename T>
DataForm &DataForm::operator()(const T &value) {
    return (*this)(&value, true);
}
}
namespace ark {
/**
 * 表示Any类型中的数据类型
 */
namespace DataType {
    /**
     * 空类型，表示未初始化
     */
    const UInt8 NONE = 0;
    /**
     * 数字类型
     */
    const UInt8 NUMBER = 1;
    /**
     * 字符串类型
     */
    const UInt8 STRING = 2;
    /**
     * 数组类型
     */
    const UInt8 ARRAY = 3;
    /**
     * 字典类型，为整数到Any的映射
     */
    const UInt8 DICTIONARY = 4;
    /**
     * 对象类型，为字符串到Any的映射
     */
    const UInt8 OBJECT = 5;
}
}
namespace ark {
class PacketReader;
class PacketWriter;
/**
 * 数据包的编码类，用于编码和解码数据包
 */
class Packet {
public:
    /**
     * 返回数据包的类型
     * @return 数据包的类型
     */
    virtual UInt32 GetType() const = 0;
    /**
     * 对数据包进行编码
     * @param writer 用于数据包编码，可以向缓冲区写入各种类型
     * @return 返回编码是否成功
     */
    virtual bool Encode(PacketWriter &writer) const = 0;
    /**
     * 解码数据包
     * @param reader 用于解码数据包，可以从缓冲区读取各种类型
     * @return 返回解码是否成功
     */
    virtual bool Decode(PacketReader &reader) = 0;
};
}
namespace ark {
/**
 * 表示没有内容的数据包
 */
class EmptyPacket : public Packet {
public:
    /**
     * 构造函数
     * @param type 指定数据包的类型
     */
    EmptyPacket(UInt32 type);
    /**
     * 析构函数
     */
    virtual ~EmptyPacket();
public:
    virtual UInt32 GetType() const;
    virtual bool Encode(PacketWriter &writer) const;
    virtual bool Decode(PacketReader &reader);
private:
    UInt32 type_;
};
}
/**
 * 命名空间ark
 */
namespace ark {
class Acceptor;
class Connection;
class Flow;
/**
 * 监听指定地址，并返回监听器
 * @param address 要监听的地址
 * @param type 表示支持的连接类型 @see ConnectionType
 * @return 创建的监听器，如果失败，则返回NULL
 */
Acceptor *Listen(const arc::SocketAddress &address, UInt8 type = ConnectionType::NORMAL);
/**
 * 指定地址和连接标识创建一个连接
 * @param address 要连接的地址
 * @param fingerprint 连接的标识
 * @param type 表示连接类型 @see ConnectionType
 * @return 创建的连接
 */
Connection *Connect(const arc::SocketAddress &address, const std::string &fingerprint, UInt8 type = ConnectionType::NORMAL);
/**
* sdk版本
*/
std::string Version();
}
namespace ark {
class FlowHandler;
class Lifetime;
class Packet;
class PacketReader;
/**
 * 连接上的双向数据流。可以看作一条虚拟的TCP连接
 */
class Flow {
public:
    /**
     * 获取流ID，每个流在当前连接上的ID是唯一的
     * @return 返回流ID
     */
    virtual UInt32 GetId() const = 0;
    /**
     * 中止流。立即关闭流，并取消所有未发送的数据
     */
    virtual void Abort() = 0;
    /**
     * 关闭流。流立即失效，但是会将队列中的数据发送完
     */
    virtual void Close() = 0;
    /**
     * 通过流向对端发送一个数据包
     * @param payload 要发送的数据
     * @param length 数据包的长度
     * @param lifetime 表示数据包的生存期，超时的数据包会被丢弃，如果为NULL，则表示数据包永不超时。
     */
    virtual void Send(const char *payload, UInt32 length, Lifetime *lifetime = NULL) = 0;
    /**
     * 通过流向对端发送一个数据包
     * @param packet 要发送的数据包
     * @param lifetime 表示数据包的生存期，超时的数据包会被丢弃，如果为NULL，则表示数据包永不超时
     */
    virtual void Send(const Packet &packet, Lifetime *lifetime = NULL) = 0;
    /**
     * 启用原始包，收到数据包时回调函数会将原始的数据传递给Handler，而不解析数据包的类型
     * @param raw 是否启用原始包，默认为不启用
     */
    virtual void EnableRawPacket(bool raw) = 0;
    /**
     * 设置流的处理程序
     * @param handler 流的处理程序
     */
    virtual void SetHandler(FlowHandler *handler) = 0;
};
}
namespace ark {
class Flow;
class PacketReader;
/**
 * 流的处理程序。用于接收和处理流上收到的数据包
 */
class FlowHandler {
public:
    /**
     * 当流接收到一个数据包时的处理函数，此时流的EnableRawPacket应为false
     * @note 注意生存期
     * @param payload 收到的数据
     * @param length 数据包的长度
     * @param flow 收到数据包的流
     */
    virtual void OnPacket(const char *payload, UInt32 length, Flow *flow) = 0;
    /**
     * 当流接收到一个数据包时的处理函数，此时流的EnableRawPacket应为true
     * @note 注意生存期
     * @param type 数据包的类型
     * @param reader 用于读取数据包
     * @param flow 收到数据包的流
     */
    virtual void OnPacket(UInt32 type, PacketReader &reader, Flow *flow) = 0;
    /**
     * 当流关闭时的处理函数，调用Abort或Close主动关闭流不会触发此函数
     * @note 注意生存期
     * @param flow 关闭的流
     */
    virtual void OnClose(Flow *flow) = 0;
};
}
namespace ark {
class Any;
class Data;
/**
 * 表示包的输入缓冲区，用于从缓冲区读取指定的数据结构
 */
class PacketReader {
public:
    /**
     * 构造函数
     * @param data 指向输入缓冲区的指针
     * @param size 输入缓冲区的大小
     */
    PacketReader(const char *data, UInt32 size);
    /**
     * 析构函数
     */
    ~PacketReader();
public:
    /**
     * 获取缓冲区的数据
     * @return 指向缓冲区开头的指针
     */
    const char *GetData() const;
    /**
     * 获取缓冲区的长度
     * @return 缓冲区的总长度
     */
    UInt32 GetLength() const;
    /**
     * 获取缓冲区的读指针
     * @return 缓冲区的读指针
     */
    const char *GetCursor() const;
    /**
     * 获取缓冲区内可读的数据长度
     * @return 缓冲区内可读的数据长度
     */
    UInt32 GetAvailable() const;
    /**
     * 返回缓冲区的状态
     * @return 缓冲区的状态，true表示正常，false表示异常，不能再对其操作
     */
    operator bool() const;
    /**
     * 在缓冲区跳过指定字节的数据
     * @param bytes 要跳过的字节数
     * @return 此对象的引用
     */
    PacketReader &Skip(UInt32 bytes);
    /**
     * 从缓冲区读取一个布尔值
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(bool &value);
    /**
     * 从缓冲区读取一个8位有符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(Int8 &value);
    /**
     * 从缓冲区读取一个8位无符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(UInt8 &value);
    /**
     * 从缓冲区读取一个16位有符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(Int16 &value);
    /**
     * 从缓冲区读取一个16位无符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(UInt16 &value);
    /**
     * 从缓冲区读取一个32位有符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(Int32 &value);
    /**
     * 从缓冲区读取一个32位无符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(UInt32 &value);
    /**
     * 从缓冲区读取一个64位无符号整数
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(UInt64 &value);
    /**
     * 从缓冲区读取一个字符串
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(std::string &value);
    /**
     * 从缓冲区读取一个Any类型的值
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(Any &value);
    /**
     * 从缓冲区读取一个扩展数据
     * @param value 要读取的值
     * @return 此对象的引用
     */
    PacketReader &operator()(Data &value);
    /**
     * 从缓冲区读取一个数组
     * @param value 要读取的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketReader &operator()(std::vector<T> &value);
    /**
     * 从缓冲区读取一个列表
     * @param value 要读取的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketReader &operator()(std::list<T> &value);
    /**
     * 从缓冲区读取一个集合
     * @param value 要读取的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketReader &operator()(std::set<T> &value);
    /**
     * 从缓冲区读取一个Dictionary
     * @param value 要读取的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketReader &operator()(std::map<UInt32, T> &value);
    /**
     * 从缓冲区读取一个Dictionary
     * @param value 要读取的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketReader &operator()(std::map<UInt64, T> &value);
    /**
     * 从缓冲区读取一个Object
     * @param value 要读取的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketReader &operator()(std::map<std::string, T> &value);
private:
    PacketReader &ReadArrayHeader(UInt32 &count);
    PacketReader &ReadDictionaryHeader(UInt32 &count);
    PacketReader &ReadObjectHeader(UInt32 &count);
    PacketReader &ReadInteger(UInt64 &integer);
    PacketReader &Success();
    PacketReader &Failed();
private:
    const char *begin_;
    const char *end_;
    const char *cursor_;
};
template <typename T>
PacketReader &PacketReader::operator()(std::vector<T> &value) {
    UInt32 count;
    if (ReadArrayHeader(count)) {
        value.clear();
        value.reserve(count);
        for (UInt32 i = 0; i < count; ++i) {
            value.resize(i + 1);
            if (!(*this)(value[i])) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketReader &PacketReader::operator()(std::list<T> &value) {
    UInt32 count;
    if (ReadArrayHeader(count)) {
        value.clear();
        for (UInt32 i = 0; i < count; ++i) {
            value.resize(i + 1);
            if (!(*this)(value.back())) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketReader &PacketReader::operator()(std::set<T> &value) {
    UInt32 count;
    if (ReadArrayHeader(count)) {
        value.clear();
        for (UInt32 i = 0; i < count; ++i) {
            T item;
            if (!(*this)(item)) {
                value.insert(item);
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketReader &PacketReader::operator()(std::map<UInt32, T> &value) {
    UInt32 count;
    if (ReadDictionaryHeader(count)) {
        for (UInt32 i = 0; i < count; ++i) {
            UInt32 key;
            if (!(*this)(key)) {
                break;
            }
            if (!(*this)(value[key])) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketReader &PacketReader::operator()(std::map<UInt64, T> &value) {
    UInt32 count;
    if (ReadDictionaryHeader(count)) {
        for (UInt32 i = 0; i < count; ++i) {
            UInt64 key;
            if (!(*this)(key)) {
                break;
            }
            if (!(*this)(value[key])) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketReader &PacketReader::operator()(std::map<std::string, T> &value) {
    UInt32 count;
    if (ReadObjectHeader(count)) {
        for (UInt32 i = 0; i < count; ++i) {
            std::string key;
            if (!(*this)(key)) {
                break;
            }
            if (!(*this)(value[key])) {
                break;
            }
        }
    }
    return *this;
}
}
namespace ark {
class Any;
class Data;
/**
 * 表示包的输出缓冲区，用于向缓冲区中写入指定的数据结构
 */
class PacketWriter {
public:
    /**
     * 构造函数，自动分配缓冲区的空间，并且缓冲区的空间会自动增长
     */
    PacketWriter();
    /**
     * 用指定的缓冲区初始化此对象，此时缓冲区不能自动增长
     * @param data 指向缓冲区的指针
     * @param size 缓冲区的大小
     */
    PacketWriter(char *data, UInt32 size);
    /**
     * 析构函数
     */
    ~PacketWriter();
public:
    /**
     * 获取输出缓冲区的指针
     * @return 输出缓冲区的指针
     */
    char *GetData();
    /**
     * 获取输出缓冲区的指针
     * @return 输出缓冲区的指针
     */
    const char *GetData() const;
    /**
     * 获取输出缓冲区已写入的数据长度
     * @return 已写入的数据长度
     */
    UInt32 GetLength() const;
    /**
     * 获取输出缓冲区的可用字节数
     * @return 可用字节数
     */
    UInt32 GetAvailable() const;
    /**
     * 返回缓冲区的状态
     * @return 缓冲区的状态，true表示正常，false表示异常，不能再对其操作
     */
    operator bool() const;
    /**
     * 向缓冲区写入原始数据
     * @param data 要写入的内容
     * @param length 要写入的长度
     * @return 此对象的引用
     */
    PacketWriter &operator()(const char *data, UInt32 length);
    /**
     * 向缓冲区写入一个布尔值
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(bool value);
    /**
     * 向缓冲区写入一个8位有符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(Int8 value);
    /**
     * 向缓冲区写入一个8位无符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(UInt8 value);
    /**
     * 向缓冲区写入一个16位有符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(Int16 value);
    /**
     * 向缓冲区写入一个16位无符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(UInt16 value);
    /**
     * 向缓冲区写入一个32位有符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(Int32 value);
    /**
     * 向缓冲区写入一个32位无符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(UInt32 value);
    /**
     * 向缓冲区写入一个64位无符号整数
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(UInt64 value);
    /**
     * 向缓冲区写入一个字符串
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(const std::string &value);
    /**
     * 向缓冲区写入一个Any类型的值
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(const Any &value);
    /**
     * 向缓冲区写入一个扩展数据
     * @param value 要写入的值
     * @return 此对象的引用
     */
    PacketWriter &operator()(const Data &value);
    /**
     * 向缓冲区写入一个数组
     * @param value 要写入的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketWriter &operator()(const std::vector<T> &value);
    /**
     * 向缓冲区写入一个列表
     * @param value 要写入的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketWriter &operator()(const std::list<T> &value);
    /**
     * 向缓冲区写入一个集合
     * @param value 要写入的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketWriter &operator()(const std::set<T> &value);
    /**
     * 向缓冲区写入一个Dictionary
     * @param value 要写入的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketWriter &operator()(const std::map<UInt32, T> &value);
    /**
     * 向缓冲区写入一个Dictionary
     * @param value 要写入的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketWriter &operator()(const std::map<UInt64, T> &value);
    /**
     * 向缓冲区写入一个Object
     * @param value 要写入的值
     * @return 此对象的引用
     */
    template <typename T>
    PacketWriter &operator()(const std::map<std::string, T> &value);
private:
    PacketWriter &WriteArrayHeader(UInt32 count);
    PacketWriter &WriteDictionaryHeader(UInt32 count);
    PacketWriter &WriteObjectHeader(UInt32 count);
    PacketWriter &WriteInteger(UInt64 integer);
    PacketWriter &Success();
    PacketWriter &Failed();
    bool ExpandBuffer(UInt32 length);
private:
    arc::Buffer *buffer_;
    char *begin_;
    char *cursor_;
    char *end_;
};
template <typename T>
PacketWriter &PacketWriter::operator()(const std::vector<T> &value) {
    if (WriteArrayHeader(value.size())) {
        for (typename std::vector<T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (!(*this)(*it)) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketWriter &PacketWriter::operator()(const std::list<T> &value) {
    if (WriteArrayHeader(value.size())) {
        for (typename std::list<T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (!(*this)(*it)) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketWriter &PacketWriter::operator()(const std::set<T> &value) {
    if (WriteArrayHeader(value.size())) {
        for (typename std::set<T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (!(*this)(*it)) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketWriter &PacketWriter::operator()(const std::map<UInt32, T> &value) {
    if (WriteDictionaryHeader(value.size())) {
        for (typename std::map<UInt32, T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (!(*this)(it->first)) {
                break;
            }
            if (!(*this)(it->second)) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketWriter &PacketWriter::operator()(const std::map<UInt64, T> &value) {
    if (WriteDictionaryHeader(value.size())) {
        for (typename std::map<UInt64, T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (!(*this)(it->first)) {
                break;
            }
            if (!(*this)(it->second)) {
                break;
            }
        }
    }
    return *this;
}
template <typename T>
PacketWriter &PacketWriter::operator()(const std::map<std::string, T> &value) {
    if (WriteObjectHeader(value.size())) {
        for (typename std::map<std::string, T>::const_iterator it = value.begin(); it != value.end(); ++it) {
            if (!(*this)(it->first)) {
                break;
            }
            if (!(*this)(it->second)) {
                break;
            }
        }
    }
    return *this;
}
}
#endif /* ARK_API_HPP */
