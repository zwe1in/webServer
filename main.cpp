#include "server/Server.h"
#include "log/Log.h"
#include "tcp/InetAddress.h"
#include "mysql/SQLConnPool.h"

int main(int argc, char* argv[])
{   
    Log::getInstance()->init(LOGTARGET::BOTH, true, "log.log");
    if(argc != 2)
    {
        printf("Input error.\n");
        return -1;
    }
    uint16_t port = atoi(argv[1]);
    InetAddress address(port);
    const char* host = "localhost";
    const char* user = "zwl";
    const char* password = "123456";
    const char* dbName = "web";
    unsigned int pport = 3306;
    SQLPoolInit(host, user, password, dbName, pport);
    Server server;
    server.start(address);
    return 0;
}