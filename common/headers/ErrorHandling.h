#pragma once

#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "LogHandling.h"
#include "ErrorHandling.h"

#define ERR_PREFIX "Error: "
#define ERR_NUM_SUCCESS 0
#define ERR_MSG_SUCCESS "Operation succeeded"

extern int errorNumber;
extern char *errorMessage;

int errorCheck();
void errorFatal(const char *);
void errorSet(int newErrorNumber, char *newErrorMessage);
void errorReset();
