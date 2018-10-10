#include "ErrorHandling.h"

int errorNumber = ERR_NUM_SUCCESS;
char *errorMessage = ERR_MSG_SUCCESS;

int errorCheck(){
  if(errorNumber != ERR_NUM_SUCCESS){
    logPrint("%s%s\n", ERR_PREFIX, errorMessage);
    int currentErrorNumber = errorNumber;
    errorReset();
    return currentErrorNumber;
  }
  return ERR_NUM_SUCCESS;
}
void errorFatal(const char *errorPrefix){
  perror(errorPrefix);
  exit(EXIT_FAILURE);
}
void errorReset(){
  errorNumber = ERR_NUM_SUCCESS;
  errorMessage = ERR_MSG_SUCCESS;
}
