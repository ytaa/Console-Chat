#include "Server.h"

bool serverRunning = false;
int serverSocket = 0;

void serverRun(char *server_address, unsigned short server_port){
	//server aaddress
	logAddConfig(LOG_OPTION_WRITE_TO_STDOUT);
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = inet_addr(server_address);
	addr_in.sin_port = htons(server_port);
	logPrint("\n");
	//fill in server info
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSocket == -1){
		logPrint("Error 'socket': %m\n");
		serverStop();
    exit(EXIT_FAILURE);
  }
  //setting server to nonblocking
  epollMakeSocketNonBlocking(serverSocket);
  if(bind(serverSocket, (struct sockaddr*)&addr_in, sizeof(addr_in)) < 0){
		logPrint("Error 'bind': %m\n");
		serverStop();
    exit(EXIT_FAILURE);
  }
  logPrint("Server up\n");
  if(listen(serverSocket, 5) == -1){
	 logPrint("Error 'listen': %m\n");
	 serverStop();
   exit(EXIT_FAILURE);
  }

  logPrint("Listening..\n");
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
  logPrint("------------------------------------------\n");
  logPrint("Server down\n");
	logPrint("------------------------------------------\n\n");
}

void serverActionSigint(int signal){
  logPrint("\n");
  serverRunning = false;
}
