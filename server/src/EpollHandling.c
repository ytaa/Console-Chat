#include "EpollHandling.h"

void epollInit(){
  epollfd = epoll_create1(0);
  struct epoll_event epollEvent;
  if (epollfd == -1) {
  	 logPrint("Error 'epoll_create1': %m\n");
  	 serverStop();
     exit(EXIT_FAILURE);
  }
  epollEvent.events = EPOLLIN;
  epollEvent.data.fd = serverSocket;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &epollEvent) == -1) {
   logPrint("Error 'epoll_ctl': %m\n");
   serverStop();
   exit(EXIT_FAILURE);
  }
}

void epollRun(){
  while(serverRunning) {
     int nfds = epoll_wait(epollfd, events, EPOLL_MAX_EVENTS, 0);
     if (nfds == -1) {
         logPrint("Error 'epoll_wait': %m\n");
         serverStop();
         exit(EXIT_FAILURE);
     }

     for (int n = 0; n < nfds; ++n) {
         if (events[n].data.fd == serverSocket) {
           epollNewConnection(serverSocket);
         }
         else {
           if(events[n].events & (EPOLLRDHUP | EPOLLHUP)){
             epollCloseConnection(events[n].data.fd);
           }
           else if(events[n].events & EPOLLIN){
             epollIn(events[n].data.fd);
           }
         }
     }
  }
}

int epollMakeSocketNonBlocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      logPrint("Error 'fcntl': %m\n");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      logPrint("Error 'fcntl': %m\n");
      return -1;
    }

  return 0;
}

void epollNewConnection(int serverSocket){
  struct sockaddr_in client_address;
  struct epoll_event epollEvent;
  int client_address_len = sizeof(client_address);
  int eventSocket = accept(serverSocket,
                     (struct sockaddr *) &client_address, &client_address_len);
  if (eventSocket == -1) {
      logPrint("Error 'accept': %m\n");
      exit(EXIT_FAILURE);
  }
  epollMakeSocketNonBlocking(eventSocket);

  logPrint("------------------------------------------\n");
  logPrint("OPENING NEW CONNECTION\n");
  logPrint("Client fd: %d\n", eventSocket);

  //register new socket to epoll
  epollEvent.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP;
  epollEvent.data.fd = eventSocket;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, eventSocket,
              &epollEvent) == -1) {
      logPrint("Error 'epoll_ctl': %m\n");
      exit(EXIT_FAILURE);
  }
}

void epollCloseConnection(int eventSocket){
  logPrint("------------------------------------------\n");
  logPrint("CLOSING CONNECTION\n");
  epoll_ctl(epollfd, EPOLL_CTL_DEL, eventSocket, NULL);
  close (eventSocket);
}

void epollIn(int eventSocket){
  char msgBuffer[256];
  int recCharIndex = 0;
  char recCharBuffer = 0;
  while(read(eventSocket, &recCharBuffer, 1) > 0){
    msgBuffer[recCharIndex++] = recCharBuffer;
    if(recCharBuffer == '\0'){
      break;
    }
  }
  logPrint("%d -> '%s'\n", eventSocket, msgBuffer);
  write(eventSocket, msgBuffer, strlen(msgBuffer)+1);
}
