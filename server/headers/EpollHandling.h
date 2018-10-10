#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

#include "Server.h"
#include "SocketOperations.h"

#define EPOLL_MAX_EVENTS 10
#define MAX_MSG_LEN 256
#define MAX_READ_TIMEOUT_MS 1000.f

struct epoll_event events[EPOLL_MAX_EVENTS];
int epollfd;

void epollInit();
void epollRun();
void epollNewConnection(int serverSocket);
void epollCloseConnection(int eventSocket);
void epollIn(int eventSocket);
