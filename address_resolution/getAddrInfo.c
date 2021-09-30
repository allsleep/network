#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "../ip4server/client/clientErro.h"

void PrintSocketAddress(const struct sockaddr *address, FILE *stream){
    if (address == NULL || stream == NULL)
        return;
    
    void *numericAddress; // pointer to binary address
    // buffer to contain result , IPv6 sufficient to hold IPv4
    char addrBuffer[INET6_ADDRSTRLEN];
    in_port_t port; // port to print

    // set pointer to address based on address family
    switch (address->sa_family) {
        case AF_INET:
            numericAddress = &((struct sockaddr_in *) address)->sin_addr;
            port = ntohs(((struct sockaddr_in *) address)->sin_port);
            break;
        case AF_INET6:
            numericAddress = &((struct sockaddr_in6 *) address)->sin6_addr;
            port = ntohs(((struct sockaddr_in6 *) address)->sin6_port);
            break;
        default:
            fputs("unknow type", stream);
            return;
    }
    // convert binary to printable address
    if (inet_ntop(address->sa_family, numericAddress, addrBuffer, sizeof(addrBuffer)) == NULL)
       fputs("invailed address", stream);
    else{
        fprintf(stream, "%s", addrBuffer);
        if(port != 0)
            fprintf(stream, "-%u", port);
    }
}

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
    for (struct addrinfo *addr = addrList; addr != NULL; addr = addr->ai_next){
        PrintSocketAddress(addr->ai_addr, stdout);
        fputc('\n', stdout);
    }

    freeaddrinfo(addrList); // free allocate memory
    exit(0);
}
