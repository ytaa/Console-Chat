#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#include "LogHandling.h"

#define MAX_MSG_LEN 256

void clientRun(char *serverAddress, unsigned short serverPort);
