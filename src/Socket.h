#pragma once
#include"Util.h"
#include"InetAddress.h"

class Socket
{
private:
    int sockfd;

public:
    Socket();
    Socket(int);
    ~Socket();
    void bind(InetAddress *);
    void listen();
    void setnonblocking();
    int accept(InetAddress *);
    int getFd();


};