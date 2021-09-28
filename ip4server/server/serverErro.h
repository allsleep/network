#ifndef __SERVER_ERRO_H
#define __SERVER_ERR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void DieWithUserMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg , const char *detail);
void HandleTCPClient(int clntSocket);

#endif