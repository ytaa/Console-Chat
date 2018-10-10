#include "LogHandling.h"

unsigned int logConfig = 0;
FILE *logFile = NULL;
bool logImportant = false;

void logPrint(const char *format, ...){
  va_list vaList;
  va_start(vaList, format);
  if(logConfig&LOG_OPTION_WRITE_TO_STDOUT){
    if(logImportant || (~(logConfig&LOG_OPTION_MIN_TO_STDOUT))){
      vprintf(format, vaList);
    }
  }
  if(logConfig&LOG_OPTION_WRITE_TO_FILE){
    if(logFile){
      if(logImportant || logConfig&LOG_OPTION_MIN_TO_FILE == 0){
          vfprintf(logFile, format, vaList);
      }
    }
  }
  va_end(vaList);
}
void logSetConfig(unsigned int newConfiguration){
  logConfig = newConfiguration;
}
void logAddConfig(unsigned int newOption){
  logConfig |= newOption;
}
void logDelConfig(unsigned int unwantedOption){
  logConfig &= (~unwantedOption);
}
void logSetFile(const char *filePath){
  if(logFile){
    fclose(logFile);
  }
  if(logConfig&LOG_OPTION_FILE_APPEND){
    logFile = fopen(filePath, "a");
  }
  else{
    logFile = fopen(filePath, "w");
  }
  if(!logFile){
    errorNumber = LOG_ERR_NUM_FILE_OPEN_FAILED;
    errorMessage = LOG_ERR_MSG_FILE_OPEN_FAILED;
    return;
  }
  logAddConfig(LOG_OPTION_WRITE_TO_FILE);
}
void logSetImportant(){
  logImportant = true;
}
void logSetUnimportant(){
  logImportant = false;
}
void logClose(){
  fclose(logFile);
}
