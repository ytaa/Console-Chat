#include "Client.h"

void clientRun(char *serverAddress, unsigned short serverPort){
	struct sockaddr_in serveAddrIn;

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}
	serveAddrIn.sin_family = AF_INET;
  serveAddrIn.sin_addr.s_addr = inet_addr(serverAddress);
	serveAddrIn.sin_port = htons(serverPort);
	if(connect(serverSocket, (struct sockaddr*)&serveAddrIn, sizeof(serveAddrIn)) != -1) {
		logPrint("connected\n");
    char msgBuffer[MAX_MSG_LEN];
    while(1){
      logPrint("write your message: ");
      scanf("%[^\n]s", msgBuffer);
      msgBuffer[MAX_MSG_LEN-1]='\0';
      if(strcmp(msgBuffer, "exit")==0){
        break;
      }
  		if( write(serverSocket, msgBuffer, strlen(msgBuffer)+1) > 0) {
  			logPrint("-> '%s'\n", msgBuffer);
  		}
      int recCharIndex = 0;
      char recCharBuffer = 0;
      while(read(serverSocket, &recCharBuffer, 1) > 0){
        msgBuffer[recCharIndex++] = recCharBuffer;
        if(recCharBuffer == '\0'){
          break;
        }
      }
      logPrint("<- '%s'\n", msgBuffer);
      char cleanup;
      while ((cleanup = getchar()) != '\n' && cleanup != EOF) { }
    }
	}
  logPrint("closing connection\n");
	close(serverSocket);
}
