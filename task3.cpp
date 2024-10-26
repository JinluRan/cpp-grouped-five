#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void gatherHtml(char* htmlFile, int exp_n, char **fileNames) {
    // 重新审查

    // 生成html文件
    FILE *html = fopen(htmlFile, "w");
    if (html == NULL) {
        printf("生成html文件失败\n");
        return;
    }

    // 写入html文件
    fprintf(html, "<html>\n");
    fprintf(html, "<head>\n");
    fprintf(html, "<title>统计结果</title>\n");
    fprintf(html, "</head>\n");
    fprintf(html, "<body>\n");
    fprintf(html, "<h1>统计结果</h1>\n");
    fprintf(html, "<table border=\"1\">\n");
    fprintf(html, "<tr>\n");
    fprintf(html, "<th>文件名</th>\n");
    fprintf(html, "<th>统计页面路径</th>\n");
    fprintf(html, "</tr>\n");
    int n_files = atoi(fileNames[0]);
    for (int i = 1; i <= n_files; i += 1) {
        fprintf(html, "<tr>\n");
        fprintf(html, "<td>%s</td>\n", fileNames[i]);
        char *url = (char *)malloc(256);
        sprintf(url, "task2_html/Exp%d/%s.html", exp_n, fileNames[i]);
        fprintf(html, "<td><a href=\"%s\">%s</a></td>\n", url, url);
        fprintf(html, "</tr>\n");
    }
    fprintf(html, "</table>\n");
    fprintf(html, "</body>\n");
    fprintf(html, "</html>\n");

    fclose(html);
    return;
}

char *getFileName(char *filePath)
{
    char ch = '\\'; // 其中一个反斜杠是转义字符
    char *q = (char *) malloc(256 * sizeof(char));
    char *p = strrchr(filePath, ch);
    if (p == NULL)
    {
        return NULL;
    }
    strcpy(q, p + 1);
    return q;
}


void singleFileProcess(char *filepath, int mode, int exp) {
    // 获取目标路径
    char *file_name = getFileName(filepath);
    char *task1_dest_path = (char *)malloc(256);
    sprintf(task1_dest_path, "%s\\%s", getPath(2, 3, exp), file_name);
    char *task2_dest_path = (char *)malloc(256);
    sprintf(task2_dest_path, "%s\\%s.html", getPath(3, 3, exp), file_name);

    // task1.exe处理文件
    char cmd[300] = {0};
    sprintf(cmd, "task1.exe %s %s %d", filepath, task1_dest_path, mode);
    system(cmd);

    // task2.exe生成统计结果html
    sprintf(cmd, "task2.exe %s %s %d", filepath, task2_dest_path, mode);
    system(cmd);

    return;
}

void singleFile() {
    // 获取最新实验编号
    char *analysed_path = (char *)malloc(256);
    sprintf(analysed_path, "%s\\%s", getCurrentPath(), getJsonKey("analysed_path"));
    int exp_n = getLatestExpN(analysed_path);

    // 读取文件路径
    char path[256] = {0};
    printf("请输入文件路径：\n");
    scanf("%s", path);

    // 判断文件是否存在
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("文件不存在，请检查文件是否存在或使用绝对路径。\n");
        return;
    }
    fclose(fp);

    // 细节模式 or 概要模式
    int mode;
    do {
        printf("请选择模式：\n");
        printf("\t1. 细节模式\n");
        printf("\t2. 概要模式\n");
        scanf("%d", &mode);
        switch(mode) {
            case 1:
                break;
            case 2:
                break;
            default:
                printf("输入错误，请重新输入\n");
        }
    } while(1);

    
    singleFileProcess(path, mode, exp_n);

    // 获取html文件路径
    char *htmlPath = getPath(3, 1);
    if (htmlPath == NULL) {
        printf("获取html文件路径失败\n");
        return;
    }
    char **filesName = getFilesName(htmlPath);
    if (filesName == NULL) {
        printf("获取html文件名失败\n");
        return;
    }

    // 使用浏览器打开html文件
    char htmlFile[256] = {0};
    sprintf(htmlFile, "%s\\%s", htmlPath, filesName[1]);
    system(htmlFile);

    return;
}

void multiFiles() {
    // 获取最新实验编号
    char *analysed_path = (char *)malloc(256);
    sprintf(analysed_path, "%s\\%s", getCurrentPath(), getJsonKey("analysed_path"));
    int exp_n = getLatestExpN(analysed_path);
    
    // 多文件路径
    char *path = getPath(1, 0);

    // 细节模式 or 概要模式
    int mode;
    do {
        printf("请选择模式：\n");
        printf("\t1. 细节模式\n");
        printf("\t2. 概要模式\n");
        scanf("%d", &mode);
        switch(mode) {
            case 1:
                break;
            case 2:
                break;
            default:
                printf("输入错误，请重新输入\n");
        }
    } while(1);

    char **filesName = getFilesName(path);
    if (filesName == NULL) {
        printf("获取文件名失败\n");
        return;
    }
    int n_files = atoi(filesName[0]);

    for (int i = 1; i <= n_files; i++) {
        char *file_path = (char *)malloc(256);
        sprintf(file_path, "%s\\%s", path, filesName[i]);
        singleFileProcess(file_path, mode, exp_n);
    }

    // 获取html文件路径
    char *htmlPath = getPath(3, 1);
    if (htmlPath == NULL) {
        printf("获取html文件路径失败\n");
        return;
    }
    char **filesName = getFilesName(htmlPath);
    if (filesName == NULL) {
        printf("获取html文件名失败\n");
        return;
    }

    // 生成index.html
    char htmlFile[256] = {0};
    sprintf(htmlFile, "%s\\%s", getCurrentPath(), "index.html");
    gatherHtml(htmlFile, exp_n, filesName);

    // 使用浏览器打开html文件
    system(htmlFile);

    return;
}

int main() {

    while (1) {
        printf("欢迎使用程序设计分组训练任务5程序\n");
        printf("组长：张原鸣 23221214\n");
        printf("组员：郭文杰 \n");
        printf("组员：冉金禄 23251178\n");
        printf("\t1. 对单个英文文档进行统计\n");
        printf("\t2. 对批量英文文档进行统计\n");
        printf("\t0. 退出\n");
        printf("请输入您要执行的程序序号：\n");
        int n;
        scanf("%d", &n);
        switch(n) {
            case 1:
                singleFile();
                break;
            case 2:
                multiFiles();
                break;
            case 0:
                return 0;
            default:
                printf("输入错误，请重新输入\n");
        }
    } 
    return 0;
} 
