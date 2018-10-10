#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "ErrorHandling.h"

#define LOG_OPTION_WRITE_TO_FILE 1
#define LOG_OPTION_MIN_TO_FILE 2
#define LOG_OPTION_WRITE_TO_STDOUT 2*2
#define LOG_OPTION_MIN_TO_STDOUT 2*2*2
#define LOG_OPTION_FILE_APPEND 2*2*2*2

#define LOG_ERR_NUM_FILE_OPEN_FAILED -1
#define LOG_ERR_MSG_FILE_OPEN_FAILED "Unable to open log file"

extern unsigned int logConfig;
extern FILE *logFile;
extern bool logImportant;

void logPrint(const char *format, ...);
void logSetConfig(unsigned int newConfiguration);
void logAddConfig(unsigned int newOption);
void logDelConfig(unsigned int unwantedOption);
void logSetFile(const char *filePath);
void logSetImportant();
void logSetUnimportant();
void logClose();
