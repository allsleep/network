#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char* argv[]){

    if (argc < 3 || argv > 4) ;
    // address echo port
    char *server = argv[1];     
    char *echoString = argv[2];
    
}