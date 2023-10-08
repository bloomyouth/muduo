#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/epoll.h>
//#include "../include/util.h"
#include "Util.h"
#include "Socket.h"
#include "InetAddress.h"

using namespace std;
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd==-1,"socket create error");
    Socket *serv_sock=new Socket();
    InetAddress* serv_addr=new InetAddress("127.0.01",8888);
    serv_sock->bind(serv_addr);
    serv_sock->listen();
    InetAddress* clnt_addr=new InetAddress();
    Socket *clnt_sock=new Socket(serv_sock->accept(clnt_addr));

    



    printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->addr.sin_addr), ntohs(clnt_addr->addr.sin_port));

    while (true)
    {
        char recvBuf[1024];
        bzero(&recvBuf, sizeof(recvBuf));
        int readByteNum = read(clnt_sock->getFd(), recvBuf, sizeof(recvBuf));
        if(readByteNum>0){ 
            printf("message from client fd %d: %s\n", clnt_sock->getFd(), recvBuf);
            write(clnt_sock->getFd(),recvBuf,sizeof(recvBuf));
        } else if(readByteNum==0){
            printf("client fd %d disconnected\n", clnt_sock->getFd());
            close(clnt_sock->getFd());
        } else if(readByteNum==-1){
            errif(true, "socket read error");
            close(clnt_sock->getFd());
        }
    }
    close(sockfd);
    return 0;
}
