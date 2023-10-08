#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
//#include "../include/util.h"
#include "Util.h"

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd==-1,"socket create error");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    // bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)); 客户端不进行bind操作

    connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr));

    while (true)
    {
        char buf[1024];
        bzero(&buf, sizeof(buf));
        std::cin.getline(buf,sizeof(buf));
        int wirteByteNum = write(sockfd, buf, sizeof(buf));
        if(wirteByteNum==-1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }

        bzero(&buf, sizeof(buf));
        int readByteNum=read(sockfd,buf,sizeof(buf));
        if(readByteNum>0){ 
            printf("message from server fd : %s\n",buf);
        } else if(readByteNum==0){
            printf("server fd %d disconnected\n", sockfd);
            break;
        } else if(readByteNum==-1){
            printf("socket error\n");
            close(sockfd);
        }




    }
    close(sockfd);
    return 0;
}
