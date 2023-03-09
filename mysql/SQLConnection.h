#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H
#include <mysql/mysql.h>
#include "../log/Log.h"
#include "../utils/Common.h"
#include <string>
#include <vector>
class SQLConnection : nonCopyable{
public:
    SQLConnection() = default;
    SQLConnection(MYSQL* sql);
    SQLConnection(SQLConnection&& other);
    SQLConnection& operator=(SQLConnection&& other);
    SQLConnection(
        const char* name_,
        const char* password_,
        const char* dbName_,
        const char* host_, 
        unsigned int port_);
    ~SQLConnection();
    bool exec(const char* statement);
    bool query(const char* statement, std::vector<std::vector<std::string>>& res);
    bool operator==(const SQLConnection& rhs);
private:
    MYSQL* sql;
    MYSQL_RES* result; 
};

#endif