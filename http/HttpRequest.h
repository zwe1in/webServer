#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include "Buffer.h"
#include <algorithm>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> kvMap;

class HttpRequest{
public:
    enum Method{
        INVALID, GET, POST, PUT, DELETE, HEAD
    };

    enum PARSE_STATE{
        REQUEST_LINE,
        HEADER,
        BODY,
        COMPLETE
    };

    HttpRequest();
    ~HttpRequest() = default;
    HttpRequest(const HttpRequest&) = delete;
    HttpRequest& operator=(const HttpRequest&) = delete;
    HttpRequest(HttpRequest&&);
    HttpRequest& operator=(HttpRequest&&);

    Method getMethodEn() const;
    std::string getMethod() const;
    std::string getVersion() const;
    std::string getPath() const;
    std::string getQuery() const;
    const kvMap& getHeaders() const;
    const kvMap& getPosts() const; 
    int getContentLength() const;
    bool getKeepAlive() const;

    bool setMethod(const std::string&);
    void setVersion(const char* start, const char* end);
    void setPath(const char* start, const char* end);
    void setQuery(const char* start, const char* end);
    void addHeader(const char* start, const char* colon, const char* end);
    void addPost(const std::string&, const std::string&);

    void reset();
    bool parse(Buffer& buffer);

private:
    bool parseRequestLine(const char* start, const char* end);
    bool parseHeader(const char* start, const char* end);
    bool parseBody(const char* start, const char* end);
private:
    PARSE_STATE state;  // 当前解析状态
    Method method;      // Http请求方法
    std::string version, path, query;   // 版本、路径、请求参数
    kvMap headers;  // 请求头集合
    kvMap postData; // Post请求参数
    int contentLength;  // Body长度
    bool isKeepAlive;   // 是否长连接
};


#endif