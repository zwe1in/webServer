#include "SQLConnection.h"

SQLConnection::SQLConnection(MYSQL* sql_)
    : sql(sql_)
{}

SQLConnection::SQLConnection(SQLConnection&& other)
    :sql(nullptr), result(nullptr)
{
    std::swap(sql, other.sql);
    std::swap(result, other.result);
}

SQLConnection& SQLConnection::operator=(SQLConnection&& other)
{
    if(&other != this)
    {
        std::swap(sql, other.sql);
        std::swap(result, other.result);
        other.sql = nullptr;
        other.result = nullptr;
    }
    return *this;
}

SQLConnection::SQLConnection(
    const char* name_,
    const char* password_,
    const char* dbName_,
    const char* host_, 
    unsigned int port_
) : sql(nullptr), result(nullptr)
{
    sql = mysql_init(sql);
    sql = mysql_real_connect(sql, host_, name_, password_, dbName_, port_, nullptr, 0);
    if(!sql)
        LOG_FATAL("SQL init error.");
}

SQLConnection::~SQLConnection()
{
    mysql_close(sql);
}

bool SQLConnection::exec(const char* statement)
{
    int ret = mysql_query(sql, statement);
    if(ret)
    {
        LOG_FATAL("SQL_Exec error for statement: %s.", statement);
        return false;
    }
    return true;
}

bool SQLConnection::query(const char* statement, std::vector<std::vector<std::string>>& res)
{
    int ret = mysql_query(sql, statement);
    if(ret)
    {
        LOG_FATAL("SQL_Query error for statement: %s.", statement);
        return false;
    }
    result = mysql_store_result(sql);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(result))
    {
        std::vector<std::string> rowdata;
        for(int i = 0; i < mysql_num_fields(result); ++i)
        {
            rowdata.emplace_back(row[i]);
        }
        res.emplace_back(std::move(rowdata));
    }
    mysql_free_result(result);
    return true;
}

bool SQLConnection::operator==(const SQLConnection& rhs)
{
    return sql == rhs.sql;
}