#include "HandleMapper.h"

funcMapper POST_HANDLES = {
    {"/login", login}
};

void login(const kvMap& data, std::string& res)
{

    if(data.size() != 2)
        throw("Unexpected length of map data.");
    if(data.find("user_name") == data.end() || data.find("password") == data.end())
        throw("Error input data");
    std::string uname = data.find("user_name")->second, pwd = data.find("password")->second;
    std::cout << uname << " " << pwd << std::endl;
    SQLConnection sql;
    SQLAcquire(sql);
    std::string statement = "SELECT id, password FROM users WHERE uname='";
    statement += uname + "'";
    std::vector<std::vector<std::string>> result;
    sql.query(statement.c_str(), result);
    std::string id = result[0][0], rPwd = result[0][1];
    if(rPwd == pwd)
    {
        res = "{\"success\":\"True\"}";
    }
    else
    {
        res = "{\"success\":\"False\", \"msg\":\"Password error.\"}";
    }

}