#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ip4server/server/serverErro.h"

static const int MAXPENDING = 5; //maximum connection requests

int main(int argc, char* argv[]){

    if (argc != 2)
        DieWithUserMessage("Parameter", "server port");
    
    in_port_t servPort = atoi(argv[1]);

    int servSock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (servSock < 0)
        DieWithSystemMessage("socket failed", " ");
    
    struct sockaddr_in6 servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin6_family = AF_INET6;
    servAddr.sin6_addr = in6addr_any;
    servAddr.sin6_port = htons(servPort);

    if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        DieWithSystemMessage("bind() failed", " ");

    if (listen(servSock, MAXPENDING) < 0)
        DieWithSystemMessage("listen() failed", " ");

    while(1){
        struct sockaddr_in6 clntAddr;
        socklen_t clntAddrLen = sizeof(clntAddr);
    
        int clntSock = accept(servSock, (struct sockaddr*) &clntAddr, &clntAddrLen);
        if (clntSock < 0)
            dieWithSystemMessage("accept() failed", " ");
        
        char clientName[INET6_ADDRSTRLEN];  // clinet connection address
        if (inet_ntop(AF_INET6, &clntAddr.sin6_addr.s6_addr, clientName, 
            sizeof(clientName)) != NULL)
            printf("client address: %s ::%(port)", clientName, ntohs(clntAddr.sin6_port));
        else
            puts("unable to get client address");
        
        HandleTCPClient(clntSock);
    }
}