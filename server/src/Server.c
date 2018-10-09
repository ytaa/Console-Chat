#include "Server.h"

bool serverRunning = false;
int serverSocket = 0;

void serverRun(char *server_address, unsigned short server_port){
	//server aaddress
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = inet_addr(server_address);
	addr_in.sin_port = htons(server_port);
	printf("\n");
	//fill in server info
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSocket == -1){
		printf("Error 'socket': %m\n");
		serverStop();
    exit(EXIT_FAILURE);
  }
  //setting server to nonblocking
  epollMakeSocketNonBlocking(serverSocket);
  if(bind(serverSocket, (struct sockaddr*)&addr_in, sizeof(addr_in)) < 0){
		printf("Error 'bind': %m\n");
		serverStop();
    exit(EXIT_FAILURE);
  }
  printf("Server up\n");
  if(listen(serverSocket, 5) == -1){
	 printf("Error 'listen': %m\n");
	 serverStop();
   exit(EXIT_FAILURE);
  }

  printf("Listening..\n");
	serverRunning = true;

	epollInit();

	//changing progam action for SIG_INT
	sigset_t blocking_sig_set;
	sigemptyset(&blocking_sig_set);
	struct sigaction sig_int_action;
	sig_int_action.sa_handler = serverActionSigint;
	sig_int_action.sa_mask = blocking_sig_set;
	sig_int_action.sa_flags = 0;
	sigaction(SIGINT, &sig_int_action, NULL);

	epollRun();

  serverStop();

  return;
}

void serverStop(){
	//serverRunning = false;
  close(serverSocket);
  printf("------------------------------------------\n");
  printf("Server down\n");
	printf("------------------------------------------\n\n");
}

void serverActionSigint(int signal){
  printf("\n");
  serverRunning = false;
}
