#include <mysql/mysql.h>
#include <iostream>
#include "SQLConnPool.h"
int main1()
{
    const char* host = "localhost";
    const char* user = "zwl";
    const char* password = "123456";
    const char* dbName = "web";
    unsigned int port = 3306;
    SQLPoolInit(host, user, password, dbName, port);
    
    SQLConnection sql;
    SQLAcquire(sql);
    std::vector<std::vector<std::string>> res;
    sql.exec("INSERT INTO users(uname, password) values('adis', '223546')");
    sql.query("SELECT * FROM users", res);
    for(int i = 0; i < res.size(); ++i)
    {
        for(int j = 0; j < res[i].size(); ++j)
        {
            std::cout << res[i][j] << " ";
        }
        std::cout << std::endl;
    }
    SQLRelease(std::move(sql));
    return 0;
}