#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include "cJSON.h"

#define BUFFER_SIZE 1024

char* getJsonKey(char *key) {
    FILE *fp = fopen("config.json", "r");
    if (fp == NULL) {
        printf("config.json文件不存在，请检查文件是否存在。\n");
        return NULL;
    }

    char readBuffer[BUFFER_SIZE];
    fread(readBuffer, BUFFER_SIZE, 1, fp);
    fclose(fp);

    cJSON *json = cJSON_Parse(readBuffer);
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item == NULL) {
        printf("config.json文件中不存在%s键，请检查文件是否正确。\n", key);
        return NULL;
    }

    return item->valuestring;
}

char* getCurrentPath() {
    char *path = (char *)malloc(256);
    getcwd(path, 256);
    return path;
}

int getLatestExpN(char *path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    int latestExpN = -1; // 初始化为-1，表示没有找到有效的实验编号

    // 构建搜索模式
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\Exp*", path);

    // 查找文件和目录
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        perror("FindFirstFile");
        return -1; // 出现错误时返回-1
    }

    do {
        // 检查是否是目录
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // 以 "Exp" 开头的文件夹名称
            if (strncmp(findFileData.cFileName, "Exp", 3) == 0) {
                // 提取实验编号
                int expN = atoi(findFileData.cFileName + 3); // 从"Exp"后面开始转换
                if (expN > latestExpN) {
                    latestExpN = expN; // 更新最新的实验编号
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    return latestExpN; // 返回最新编号
}

char* getPath(int type, int exp = 0, int n_exp = -1) {
    char key[32];
    switch (type) {
        case 1:
            strcpy(key, "multi_text_path");
            break;
        case 2:
            strcpy(key, "analysed_path");
            break;
        case 3:
            strcpy(key, "html_path");
            break;
        case 4:
            strcpy(key, "gathered_html_path");
            break;
        default:
            return NULL;
    }
    char *single_text_path = getJsonKey(key);
    if (single_text_path == NULL) {
        return NULL;
    }
    char *path = (char *)malloc(256);
    sprintf(path, "%s/%s", getCurrentPath(), single_text_path);

    // 如果exp，则添加实验编号
    if (exp != 0) {
        // exp=1表示获取最新的实验
        // exp=2表示获取最新的实验+1
        // exp=3表示获取n_exp指定的实验
        char expPath[256];
        switch (exp) {
            case 1:
                exp = getLatestExpN(path);
                break;
            case 2:
                exp = getLatestExpN(path) + 1;
                break;
            case 3:
                exp = n_exp;
                break;
            default:
                exp = getLatestExpN(path);
                break;
        }
        sprintf(expPath, "%s/Exp%d", path, exp);
        strcpy(path, expPath);
    }

    return path;
}

char** getFilesName(char *path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    int fileCount = 0;

    // 构建搜索模式
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.txt", path);

    // 查找文件和目录
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        perror("FindFirstFile");
        return NULL; // 出现错误时返回NULL
    }

    do {
        // 检查是否是文件
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            fileCount++;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    // 申请文件名数组的内存
    char **filesName = (char **)malloc((fileCount+1) * sizeof(char *));
    for (int i = 0; i < fileCount+1; i++) {
        filesName[i] = (char *)malloc(MAX_PATH);
    }
    // 第一个元素存储文件数量
    sprintf(filesName[0], "%d", fileCount);

    // 重新查找文件
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        perror("FindFirstFile");
        return NULL; // 出现错误时返回NULL
    }

    int i = 0;
    do {
        // 检查是否是文件
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strcpy(filesName[i+1], findFileData.cFileName);
            i++;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    return filesName;
}