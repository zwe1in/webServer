#ifndef INETADDRESS_H
#define INETADDRESS_H
#include <arpa/inet.h>
#include <string>
#include <string.h>

class InetAddress{
public:
    InetAddress() = default;
    InetAddress(uint16_t port)
    {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    InetAddress(std::string& ip, uint16_t port)
    {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    InetAddress(struct sockaddr_in& addr_) : addr(addr_){}
    InetAddress(const InetAddress& other)
    {
        addr = other.addr;
    }
    InetAddress(InetAddress&& other)
    {
        std::swap(other.addr, addr);
    }
    InetAddress& operator=(const InetAddress& other)
    {
        addr = other.addr;
        return *this;
    }
    InetAddress& operator=(InetAddress&& other)
    {
        std::swap(other.addr, addr);
        return *this;
    }
    ~InetAddress() = default;

    std::string toIp()
    {
        char buf[32] = "";
        inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf));
        return buf;
    }

    std::string toIpPort()
    {
        char buf[32] = "";
        inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf));
        uint16_t port = getHostPort();
        return std::string(buf) + ":" + std::to_string(port);
    }

    uint16_t getHostPort() const { return ntohs(addr.sin_port); }
    uint32_t getHostIp() const { return ntohl(addr.sin_addr.s_addr); }
    uint16_t getNetPort() const { return addr.sin_port; }
    uint32_t getNetIp() const { return addr.sin_addr.s_addr; }
    const struct sockaddr_in& getAddr() const { return addr; }
    bool operator==(const InetAddress& rhs)
    {
        return addr.sin_family == rhs.addr.sin_family
            && addr.sin_port == rhs.addr.sin_port
            && addr.sin_addr.s_addr == addr.sin_addr.s_addr;
    }
private:
    struct sockaddr_in addr;
};

#endif