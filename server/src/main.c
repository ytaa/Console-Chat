#include "Server.h"

int main(int argc, char** argv){

  if(argc < 3){
    printf("Invalid number of arguments.\n");
    exit(EXIT_FAILURE);
  }

  serverRun(argv[1], atoi(argv[2]));

  return 0;
}
