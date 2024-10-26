#include <stdio.h>
#include <stdlib.h>

void singleFile() {
    // 读取文件路径
    char path[256] = {0};
    printf("请输入文件路径：\n");
    scanf("%s", path);

    // 判断文件是否存在
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("文件不存在\n");
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

    // 调用raw_processor.exe处理文件
    char cmd[300] = {0};
    if (path[0] == '\"') {
        sprintf(cmd, "raw_processor.exe %s %d", path, mode);
    } else {
        sprintf(cmd, "raw_processor.exe \"%s\" %d", path, mode);
    }
    system(cmd);

    // 调用analysis_processor.exe生成统计结果html
    

    return;
}

void multiFiles() {
    return;
}

int main() {

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
            exit(0);
        default:
            printf("输入错误，请重新输入\n");
    }
    return 0;
} 
