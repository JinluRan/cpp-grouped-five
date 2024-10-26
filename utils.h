#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include "cJSON.h"

#define BUFFER_SIZE 1024

char* getJsonKey(char *key);

char* getCurrentPath();

int getLatestExpN(char *path);

char* getPath(int type, int exp = 0, int n_exp = -1);

char** getFilesName(char *path);