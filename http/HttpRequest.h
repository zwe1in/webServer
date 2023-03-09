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
    PARSE_STATE state;
    Method method;
    std::string version, path, query;
    kvMap headers;
    kvMap postData;
    int contentLength;
    bool isKeepAlive;
};


#endif