#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H
#include "Buffer.h"
#include "HandleMapper.h"
#include <string>
#include <unordered_map>
#include "HttpRequest.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <functional>

class HttpResponse{
public:
    HttpResponse();
    ~HttpResponse() = default;

    void init(
        const std::string& src,
        int code,  
        HttpRequest&& request);
    std::string getFileType();
    void makeResponse(Buffer& buffer);      // 生成Http响应到写缓冲区
    void setSrcPath(const std::string& src);
    char* getFile() const ;
    size_t fileLen() const ;
private:
    // GET handle
    void setCode();
    void responseContent(Buffer& buffer);                       // Get请求处理
    void resposePost(Buffer& buffer, const std::string& res);   // Post请求处理
private:
    HttpRequest::Method method; // 请求方法
    int code;           // 状态码
    bool isKeepAlive;   // 是否长连接
    std::string path, rootPath, version;    // 路径、根路径、版本
    kvMap postData;          // Post请求信息
    struct stat mFileStat;  // 静态资源文件信息
    char *mFile;    // 要传输的静态资源文件

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE; // 文件后缀对应的文件类型
    static const std::unordered_map<int, std::string> CODE_STATUS;          // 状态码对应的状态
};


#endif