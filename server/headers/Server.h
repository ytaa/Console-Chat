#pragma once

#include <arpa/inet.h>

#include "EpollHandling.h"
#include "LogHandling.h"
#include "SocketOperations.h"

extern int serverSocket;
extern bool serverRunning;

void serverRun(char *server_address, unsigned short server_port);
void serverStop();
void serverActionSigint(int signal);
