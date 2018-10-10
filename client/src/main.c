#include "Client.h"

int main(int argc, char** argv){
  if(argc < 3){
    logPrint("Invalid number of arguments.\n");
    exit(EXIT_FAILURE);
  }
  clientRun(argv[1], atoi(argv[2]));
  return 0;
}
