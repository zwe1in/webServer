#include "HttpRequest.h"

HttpRequest::HttpRequest()
    : method(INVALID), state(REQUEST_LINE), contentLength(0), isKeepAlive(false)
{}

HttpRequest::HttpRequest(HttpRequest&& other)
    : state(REQUEST_LINE), method(INVALID), contentLength(0), isKeepAlive(false)
{
    std::swap(state, other.state);
    std::swap(method, other.method);
    std::swap(contentLength, other.contentLength);
    std::swap(isKeepAlive, other.isKeepAlive);
    version.swap(other.version);
    path.swap(other.path);
    query.swap(other.query);
    headers.swap(other.headers);
    postData.swap(other.postData);

}
HttpRequest& HttpRequest::operator=(HttpRequest&& other)
{
    if(&other != this)
    {
        std::swap(state, other.state);
        std::swap(method, other.method);
        std::swap(contentLength, other.contentLength);
        std::swap(isKeepAlive, other.isKeepAlive);
        version.swap(other.version);
        path.swap(other.path);
        query.swap(other.query);
        headers.swap(other.headers);
        postData.swap(other.postData);
    }
    return *this;
}

HttpRequest::Method HttpRequest::getMethodEn() const
{
    return method;
}

std::string HttpRequest::getMethod() const
{
    switch (method)
    {
        case GET:
            return "GET";
            break;
        case POST:
            return "POST";
            break;
        case PUT:
            return "PUT";
            break;
        case DELETE:
            return "DELET";
            break;
        case HEAD:
            return "HEAD";
            break;
        default:
            break;
    }
    return "INVALID";
}
std::string HttpRequest::getVersion() const
{
    return version;
}
std::string HttpRequest::getPath() const
{
    return path;
}
std::string HttpRequest::getQuery() const
{
    return query;
}
const kvMap& HttpRequest::getHeaders() const
{
    return headers;
}
const kvMap& HttpRequest::getPosts() const
{
    return postData;
}
int HttpRequest::getContentLength() const
{
    return contentLength;
}
bool HttpRequest::getKeepAlive() const
{
    return isKeepAlive;
}

bool HttpRequest::setMethod(const std::string& method_)
{
    if(method_ == "GET")
        method = GET;
    else if(method_ == "POST")
        method = POST;
    else if(method_ == "PUT")
        method = PUT;
    else if(method_ == "DELETE")
        method = DELETE;
    else if(method_ == "HEAD")
        method = HEAD;
    else
        method = INVALID;
    return method != INVALID;
}
void HttpRequest::setVersion(const char* start, const char* end)
{
    version.assign(start, end);
}
void HttpRequest::setPath(const char* start, const char* end)
{
    path.assign(start, end);
}
void HttpRequest::setQuery(const char* start, const char* end)
{
    query.assign(start, end);
}
void HttpRequest::addHeader(const char* start, const char* colon, const char* end)
{
    std::string key(start, colon);
    ++colon;
    while(isspace(*colon) && colon < end)
        ++colon;
    std::string value(colon, end);
    while(!value.empty() && isspace(value[value.size() - 1]))
        value.resize(value.size() - 1);
    if(key == "Content-Length")
        contentLength = atoi(value.c_str());
    if(key == "Connection" && value == "keep-alive")
        isKeepAlive = true;
    headers[key] = value;
}

void HttpRequest::addPost(const std::string& key, const std::string& value)
{
    postData[key] = value;
}

void HttpRequest::reset()
{
    state = REQUEST_LINE;
    method = INVALID;
    contentLength = 0;
    version.clear();
    path.clear();
    query.clear();
    headers.clear();
    postData.clear();
}

bool HttpRequest::parse(Buffer& buffer)
{
    const char CRLF[] = "\r\n";
    while(state != COMPLETE)
    {
        const char* lineEnd = std::search(buffer.beginRead(), const_cast<const char*>(buffer.beginWrite()), CRLF, CRLF + 2);
        switch (state)
        {
            case REQUEST_LINE:
                if(!parseRequestLine(buffer.beginRead(), lineEnd))
                    return false;
                state = HEADER;
                buffer.retrieveUntil(lineEnd + 2);
                break;
            case HEADER:
                if(lineEnd == buffer.beginRead())
                {
                    state = BODY;
                    buffer.retrieveUntil(lineEnd + 2);
                    break;
                }
                if(!parseHeader(buffer.beginRead(), lineEnd))
                    return false;
                buffer.retrieveUntil(lineEnd + 2);
                break;
            case BODY:
                if(!parseBody(buffer.beginRead(), buffer.beginRead() + contentLength))
                    return false;
                state = COMPLETE;
                buffer.retrieve(contentLength);
                break;
            default:
                break;
        }
    }
    return true;
}

bool HttpRequest::parseRequestLine(const char* start, const char* end)
{
    const char* space = std::find(start, end, ' ');
    if(space == end || !setMethod(std::string(start, space))) 
        return false;
    start = space + 1;
    space = std::find(start, end, ' ');
    if(space == end)
        return false;
    const char* question = std::find(start, space, '?');
    if(question == space)
        setPath(start, space);
    else
    {
        setPath(start, question);
        setQuery(question + 1, space);
    }
    start = space + 1;
    if(end - start == 8)    // "HTTP/1.x"
        setVersion(start, end);
    else 
        return false;
    return true;
}

bool HttpRequest::parseHeader(const char* start, const char* end)
{
    const char* colon = std::find(start, end, ':');
    if(colon == end)
        return false;
    addHeader(start, colon, end);
    return true;
}

bool HttpRequest::parseBody(const char* start, const char* end)
{
    if(start == end) return true;
    const char* ansMark = std::find(start, end, '&');
    const char* equalMark;
    while (ansMark < end)
    {
        equalMark = std::find(start, ansMark, '=');
        if(equalMark == ansMark)
            return false;
        addPost(std::string(start, equalMark), std::string(equalMark + 1, ansMark));
        start = ansMark + 1;
        ansMark = std::find(start, end, '&');
    }
    equalMark = std::find(start, end, '=');
    addPost(std::string(start, equalMark), std::string(equalMark + 1, end));
    return true;
    
}