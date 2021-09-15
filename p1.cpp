#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
   
    if (agrc < 3 || argc > 4)
        DieWithUserMessage("Parameter(s)",
            "<Server Address> <Echo Word> [<Server Port>]");
    
    char *servIP = argv[1];
    char *echoString = argv[2];
    
    // third parm is optional, default parm is 7 that unknow port
    in_port_t servPort = (argv == 4)? atoi(argv[3]) : 7;

    // create a reliable, stream socket using tcp
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0)
        DieWithSystemMessage("socket() failed");
    
    // construct the server address structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;

    // convert address
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if (rtnVal == 0)
        DieWithSystemMessage("inet_pton() failed", "invalid address string");
    else if (rtnVal < 0)
        DieWithUserMessage("inget_potn() failed");

    servAddr.sin_port = htons(servPort);

    // establish the connect to the echo server
    if (connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
        DieWithUserMessage("connect() failed");
    
    size_t echoStringLen = strlen(echoString);

    // send the string to the server
    ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
    if (numBytes < 0)
        DieWithSystemMessage("send() failed");
    else if (numBytes != echoStringLen)
        DieWithUserMessage("send()", "send unexperted number of bytes");

    // recive the same string back from the serve
    unsigned int totalBytesRcvd = 0;
    fputs("Received: ", stdout);
    while (totalBytesRcvd < echoStringLen){
        char buffer[BUFSIZE];
        numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
        if (numBytes < 0)
            DieWithSystemMessage("recv() failed");
        else if (numBytes == 0)
            DieWithUserMessage("recv()", "connection closed prematurely");

        totalBytesRcvd += numBytes;
        buffer[numBytes] = '\0';
        fputs(buffer, stdout);
    }

    fputc('\n', stdout);

    close(sock);
    exit(0);
}















