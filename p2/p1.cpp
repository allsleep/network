#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "p2.hpp"

static const int MAXPENDING = 5; // maximum outstanding connection requests

int main(int argc, char* argv[]){

    if (argc != 2) // test of correct number of arguments
        DieWithUserMessage("Parmeter(s)", "<Server Port>");

    in_port_t servPort = atoi(argv[1]); // local port
    
    // create socket for incoming connections
    int servSock = -1;
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithSystemMessage("socket() failed", " ");

    // construcet local adress structure
    struct sockaddr_in servAddr; // local address
    memset(&servAddr, 0, sizeof(servAddr)); // zero out structure
    servAddr.sin_family = AF_INET; // ipv4 address family
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // any incoming interface
    servAddr.sin_port = htons(servPort); // local port

    // bind to the local address
    if (bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
        DieWithSystemMessage("bind() failed", " ");

    // mark the socket so it will listen for incoming connections
    if (listen(servSock, MAXPENDING) < 0)
        DieWithSystemMessage("listen() failed", " ");
    
    for (;;) {
        struct sockaddr_in clntAddr; // client address
        // set length of client address structure (int-out parameter)
        socklen_t clntAddrLen = sizeof(clntAddr);

        // wait for a client to connect
        int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &clntAddrLen);
        if (clntSock < 0)
            DieWithSystemMessage("accept() failed", " ");

        // clntSock is connected to a client
        
        char clntName[INEF_ADDRESTRLEN]; // string to contain client address
        if (inet_ntop(AF_INEF, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
            // std::cout<<"Handling client "<<clntName<<ntohs(clntAddr.sin_port);
            ;
        else
            puts("unable to get client address");

            HandleTCPClient(clntSock);
    }
    // not reached
}
