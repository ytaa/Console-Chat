#pragma once

#include <arpa/inet.h>

#include "EpollHandling.h"

#define SERVER_MINIMAL_OUTPUT 1
#define SERVER_ALREADY_EXISTING 2
#define SERVER_LOGS_TO_FILE 2*2
#define SERVER_LOGS_APPEND 2*2*2
#define SERVER_INTERACTIVE 2*2*2*2

#define SERVER_IP_BUFFER_SIZE 20
#define SERVER_PORT_BUFFER_SIZE 10

extern int serverSocket;
extern int server_options;
extern bool serverRunning;

void serverRun(char *server_address, unsigned short server_port);
void serverStop();
void serverActionSigint(int signal);
