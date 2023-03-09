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
    void makeResponse(Buffer& buffer);
    void setSrcPath(const std::string& src);
    char* getFile() const ;
    size_t fileLen() const ;
private:
    // GET handle
    void setCode();
    void responseContent(Buffer& buffer);
    
    void resposePost(Buffer& buffer, const std::string& res);
private:
    HttpRequest::Method method;
    int code;
    bool isKeepAlive;
    std::string path, rootPath, version;
    kvMap postData;    
    struct stat mFileStat;
    char *mFile;

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE; 
    static const std::unordered_map<int, std::string> CODE_STATUS; 
};


#endif