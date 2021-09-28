#include "serverErro.h"

#define BUFSIZE 64

void DieWithUserMessage(const char *msg, const char *detail){
    fputs(msg, stderr);
    fputs(": ", stderr);
    fputs(detail, stderr);
    fputc('\n', stderr);
    exit(1);
}

void DieWithSystemMessage(const char *msg, const char *detail){
    perror(msg);
    perror(detail);
    exit(1);
}

void HandleTCPClient(int clntSocket){
    char buffer[BUFSIZE]; // buffer for echo string
    
    // receive message from client
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0)
        DieWithSystemMessage("recv() failed", " ");

    // send received string and received again until end of stream
    while (numBytesRcvd > 0){
    // echo message back to client
        ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);

        if(numBytesSent < 0)
            DieWithSystemMessage("send() failed", " ");
        else if (numBytesSent != numBytesRcvd)
            DieWithUserMessage("send()", "sent unexcepted unmber of bytes");

        // see if there is more data to receive
        numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
        if (numBytesRcvd < 0)
            DieWithSystemMessage("recv() failed", " ");
    }

    close(clntSocket); //close client socket
}