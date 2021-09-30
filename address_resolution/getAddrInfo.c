#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[]){
    if (argc != 3)
        return -1; // DieWithUserMessage("parameter", "<address/name> <port/service>")

    char *addrString = argv[1]; // server address/name
    char *portString = argv[2];

    // tell the system what kind of address we want
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC; // any addres family
    addrCriteria.ai_socktype = SOCK_STREAM; // only stream sockets
    addrCriteria.ai_protocol = IPPROTO_TCP; // only tcp protocol

    // get address associated with the specified name/service
    struct addrinfo *addrList; // holder for list of addresses returned
    // modify servAddr contents to reference linked list of address
    int rtnVal = getaddrinfo(addrString, portString, &addrCriteria, &addrList);
    if (rtnVal != 0)
        return -1; // DieWithUserMessage("getaddrinfo() failed", "gai_strerror(rtnVal)");
    
    // display returned addresses
    for (struct addrinfo *addr = addrList; addr != NULL, addr = addr->ai_next){
        PrintSocketAddress(addr->ai_addr, stdout);
        fputc('\n', stdout);
    }

    freeaddrinfo(addrList); // free allocate memory
    exit(0);
}