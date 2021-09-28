#ifndef __CLIENT_ERRO_H
#define __CLIENT_ERRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "clientErro.h"

#define BUFSIZE 16

void DieWithUserMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg, const char *detail);

#endif