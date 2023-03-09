#include "HttpResponse.h"

const std::unordered_map<std::string, std::string> HttpResponse::SUFFIX_TYPE = {
    { ".html",  "text/html" },
    { ".xml",   "text/xml" },
    { ".xhtml", "application/xhtml+xml" },
    { ".txt",   "text/plain" },
    { ".pdf",   "application/pdf" },
    { ".word",  "application/nsword" },
    { ".png",   "image/png" },
    { ".gif",   "image/gif" },
    { ".jpg",   "image/jpeg" },
    { ".jpeg",  "image/jpeg" },
    { ".mpeg",  "video/mpeg" },
    { ".mpg",   "video/mpeg" },
    { ".mp3",   "audio/mp3" },
    { ".mp4",   "audio/mp4" },
    { ".avi",   "video/x-msvideo" },
    { ".tar",   "application/x-tar" },
    { ".css",   "text/css "},
    { ".js",    "text/javascript "}
};

const std::unordered_map<int, std::string> HttpResponse::CODE_STATUS = {
    { 200, "OK" },
    { 400, "Bad Request" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
    { 500, "Error"}
};


HttpResponse::HttpResponse()
    : code(200), isKeepAlive(false), mFile(nullptr), mFileStat({0})
{}

char* HttpResponse::getFile() const 
{
    return mFile;
}
size_t HttpResponse::fileLen() const 
{
    return mFileStat.st_size;
}

void HttpResponse::setSrcPath(const std::string& src)
{
    rootPath = src;
}

void HttpResponse::init(
    const std::string& src, 
    int code_,
    HttpRequest&& request)
{
    code = code_;
    isKeepAlive = request.getKeepAlive();
    method = request.getMethodEn();
    rootPath = src;
    path = std::move(request.getPath());
    version = std::move(request.getVersion());
    postData = std::move(request.getPosts());
    if(mFile)
    {
        munmap(mFile, mFileStat.st_size);
        mFile = nullptr;
    }
    mFileStat = {0};
}

void HttpResponse::makeResponse(Buffer& buffer)
{
    if(method == HttpRequest::GET)
    {
        setCode();
        // std::cout << rootPath + path << std::endl;
        if(code == 200)
        {
            // 拿到资源文件
            int srcFd = open((rootPath + path).data(), O_RDONLY);
            if(srcFd < 0)
            {
                return ;
            }
            int *mmRet = (int*)mmap(0, mFileStat.st_size, PROT_READ, MAP_PRIVATE, srcFd, 0);
            if(*mmRet == -1)
            {
                return ;
            }
            mFile = (char*)mmRet;
            close(srcFd);
        }
        responseContent(buffer);
    }
    else if(method == HttpRequest::POST)
    {
        if(code == 400) return;
        if(POST_HANDLES.count(path) == 1)
        {
            try
            {
                std::string res;
                POST_HANDLES.find(path)->second(postData, res);
                resposePost(buffer, res);
            }
            catch(std::string expression)
            {
                std::cout << expression << std::endl;
                code = 500;
            }
        }
        else
            code = 404;
    }
    
    
}

void HttpResponse::setCode()
{
    // request解析错误
    if(code == 400) return;
    // 判断资源文件是否存在
    if(stat((rootPath + path).data(), &mFileStat) < 0 || S_ISDIR(mFileStat.st_mode))
    {
        code = 404;
    }
    // 判断是否有访问权限
    else if(!(mFileStat.st_mode & S_IROTH))
        code = 403;
}

void HttpResponse::responseContent(Buffer& buffer)
{
    // stateLine
    std::string status;
    if(CODE_STATUS.count(code) == 1)
        status = CODE_STATUS.find(code)->second;
    else
    {
        code = 400;
        status = "Bad Request";
    }
    buffer.append(version + " " + std::to_string(code) + " " + status + "\r\n");

    // headers
    buffer.append("Connection: ");
    if(isKeepAlive)
    {
        buffer.append("keep-alive\r\n");
        buffer.append("keep-alive: max=6, timeout=12000\r\n");
    }
    else
        buffer.append("close\r\n");
    buffer.append("Content-type: " + getFileType() + ";"); //文件类型
    buffer.append("charset: utf-8\r\n");
    buffer.append("Content-length: " + std::to_string(mFileStat.st_size) + "\r\n\r\n");
}

void HttpResponse::resposePost(Buffer& buffer, const std::string& res)
{
    std::string status;
    if(CODE_STATUS.count(code) == 1)
        status = CODE_STATUS.find(code)->second;
    else
    {
        code = 400;
        status = "Bad Request";
    }
    buffer.append(version + " " + std::to_string(code) + " " + status + "\r\n");

    // headers
    buffer.append("Connection: ");
    if(isKeepAlive)
    {
        buffer.append("keep-alive\r\n");
        buffer.append("keep-alive: max=6, timeout=12000\r\n");
    }
    else
        buffer.append("close\r\n");
    buffer.append("Content-type: text/plain;"); //文件类型
    buffer.append("charset: utf-8\r\n");
    buffer.append("Content-length: " + std::to_string(res.size()) + "\r\n\r\n");
    buffer.append(res);
    std::cout << std::string(buffer.beginRead(), buffer.beginRead() + buffer.readableBytes()) << std::endl;
}

std::string HttpResponse::getFileType() 
{
    std::string::size_type it = path.find_last_of('.');
    if(it == std::string::npos)
        return "text/plain";
    std::string suffix = path.substr(it);
    if(SUFFIX_TYPE.count(suffix) == 1) 
        return SUFFIX_TYPE.find(suffix)->second;
    return "text/plain";
}