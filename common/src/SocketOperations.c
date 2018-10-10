#include "SocketOperations.h"

double socketMaxReadTimeout = SOCKET_DEFAULT_MAX_READ_TIMEOUT;

int socketRead(int socket, void *receiveBuffer, int expectedSize){
  clock_t lastReadTime = clock();
  clock_t currentReadTime;

  int receivedDataSize = 0;
  int currentReadDataSize = 0;

  while(receivedDataSize < expectedSize){
    currentReadDataSize = read(socket, receiveBuffer + receivedDataSize
      , expectedSize-receivedDataSize);
    if(currentReadDataSize > 0){
      clock_t lastReadTime = clock();
      receivedDataSize += currentReadDataSize;
    }
    else{
      currentReadTime = clock();
      double deltaTime = (double)(currentReadTime - lastReadTime)
      /CLOCKS_PER_SEC*1000.f;
      if(deltaTime > socketMaxReadTimeout){
        errorSet(SOCKET_ERR_NUM_READ_TIMEOUT, SOCKET_ERR_MSG_READ_TIMEOUT);
        return receivedDataSize;
      }
    }
  }

  return receivedDataSize;
}

int socketWrite(int socket, const void *sendBuffer, int bufferSize){
  return write(socket, sendBuffer, bufferSize);
}

void socketMakeNonBlocking(int socket){
  int fcntlFlags;
  fcntlFlags = fcntl (socket, F_GETFL, 0);
  if (fcntlFlags == -1){
    errorSet(SOCKET_ERR_NUM_FCNTL_FAILED, SOCKET_ERR_MSG_FCNTL_FAILED);
    return;
  }
  fcntlFlags |= O_NONBLOCK;
  fcntlFlags = fcntl (socket, F_SETFL, fcntlFlags);
  if (fcntlFlags == -1){
    errorSet(SOCKET_ERR_NUM_FCNTL_FAILED, SOCKET_ERR_MSG_FCNTL_FAILED);
    return;
  }
}
