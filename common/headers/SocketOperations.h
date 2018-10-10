#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "ErrorHandling.h"

#define SOCKET_DEFAULT_MAX_READ_TIMEOUT 2000 //ms

#define SOCKET_ERR_NUM_FCNTL_FAILED -1
#define SOCKET_ERR_MSG_FCNTL_FAILED "Unable to make socket nonblocking"
#define SOCKET_ERR_NUM_READ_TIMEOUT -2
#define SOCKET_ERR_MSG_READ_TIMEOUT "Socket read timeout"

extern double socketMaxReadTimeout;

int socketRead(int socket, void *receiveBuffer, int expectedSize);
int socketWrite(int socket, const void *sendBuffer, int bufferSize);
void socketMakeNonBlocking(int socket);
