#include"Socket.h"
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>

Socket::Socket():sockfd(-1){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd==-1,"socket create error");  
}

Socket::Socket(int fd):sockfd(fd){
    errif(sockfd==-1,"socket create error");  
}

Socket::~Socket(){
    if(sockfd!=-1){
        close(sockfd);
        sockfd=-1;
    }
}

void Socket::bind(InetAddress *addr){
    errif(::bind(sockfd, (sockaddr *)&addr->addr, addr->addr_len)==-1,"socket bind error");
}

void Socket::listen(){
    errif(::listen(sockfd, SOMAXCONN)==-1,"socket listen error");
}

void Socket::setnonblocking(){
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress* addr){
    int clnt_sockfd = ::accept(sockfd, (sockaddr*)&addr->addr, &addr->addr_len);
    errif(clnt_sockfd == -1, "socket accept error");
    return clnt_sockfd;
}

int Socket::getFd(){
    return sockfd;
}


