#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int SetupTCPClientSocket(const char *host, const char *service){
    struct addrinfo addrCriteria; // criteria for address match
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC; //ipv4 or ipv6
    addrCriteria.ai_socktype = SOCK_STREAM; // only streaming sockets
    addrCriteria.ai_protocol = IPPROTO_TCP; 

    // get address
    struct addrinfo *servAddr; // list of return address
    int rtnVal = getaddrinfo(host, service, &addrCriteria, &servAddr);
    if (rtnVal != 0);
        //DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));
    
    int sock = -1;
    for (struct addrinfo *addr = servAddr; addr != NULL; addr->ai_next) {
        // create a reliable, stream socket using TCP
        sock = socket(addr->ai_family, addr->ai_socktype);
        if (sock < 0) continue; // socket creation failed, try next address

        // establish the connection to the echo server
        if (connect(sock, addr->ai_addr, addr->ai_addrlen) == 0) break;

        close(sock);
        sock = -1;
    }
    
    freeaddrinfo(servAddr);
    return sock;
}