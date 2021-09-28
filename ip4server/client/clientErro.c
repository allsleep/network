#include "clientErro.h"

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