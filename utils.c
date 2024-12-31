//提供通用功能，例如文件操作、输入校验、通用排序等。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utils.h"



//ui操作
void clearScreen() {
    printf("\033[H\033[J");
}

void pause() {
    printf("按任意键继续...");
    getchar();
    getchar();
}


// 文件操作
void removeContent(const char* filename,const char* contentToRemove) {
    //打开文件
    FILE* fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }

    //创建临时文件
    FILE* tempfile = tmpfile();
    if (tempfile == NULL) {
        printf("创建临时文件失败！\n");
        fclose(fp);
        return;
    }

    //读取文件内容
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("内存分配失败！\n");
        fclose(fp);
        fclose(tempfile);
        return;
    }

    //逐行读取文件内容并写入临时文件
    while (fgets(buffer, fileSize + 1, fp)!= NULL) {
        char* match = strstr(buffer, contentToRemove);
        if (match == NULL) {
            fputs(buffer, tempfile);
        }
    }
    //关闭文件
    fclose(fp);
    //重新打开文件并清空写入
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        free(buffer);
        return;
    }

    //从临时文件中读取内容，并且写回原来文件
    rewind(tempfile);
    while (fgets(buffer, fileSize + 1, tempfile)!= NULL) {
        fputs(buffer, fp);
    }
    //关闭临时文件
    fclose(tempfile);
    //关闭原文件
    fclose(fp);
    //释放内存
    free(buffer);
}

void removeContentForTwoFields(const char* filename, const char* field1, const char* field2) {
    // 打开原文件
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }

    // 创建临时文件
    FILE* tempfile = tmpfile();
    if (tempfile == NULL) {
        printf("创建临时文件失败！\n");
        fclose(fp);
        return;
    }

    char line[1024];

    // 逐行读取文件内容并检查字段匹配
    while (fgets(line, sizeof(line), fp) != NULL) {
        char fileField1[50], fileField2[50], fileField3[50], fileField4[50];

        // 假设文件的每一行格式为: field1,field2,field3,field4
        sscanf(line, "%[^,],%[^,],%[^,],%s", fileField1, fileField2, fileField3, fileField4);

        // 检查字段匹配
        int match1 = (field1 != NULL) && (strcmp(fileField1, field1) == 0);
        int match2 = (field2 != NULL) && (strcmp(fileField2, field2) == 0);

        // 如果字段匹配，则跳过写入临时文件
        if (!(match1 && (field2 == NULL || match2))) {
            fputs(line, tempfile);
        }
    }

    // 关闭原文件
    fclose(fp);

    // 重新打开原文件用于写入，并清空内容
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法重新打开文件：%s\n", filename);
        fclose(tempfile);
        return;
    }

    // 将临时文件的内容写回原文件
    rewind(tempfile);
    while (fgets(line, sizeof(line), tempfile) != NULL) {
        fputs(line, fp);
    }

    // 关闭临时文件和原文件
    fclose(tempfile);
    fclose(fp);

    printf("内容删除成功！\n");
}

void editContent(const char* filename, const char* id, const char* newContent) {
    //打开文件
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }

    //创建临时文件
    FILE* tempfile = tmpfile();
    if (tempfile == NULL) {
        printf("创建临时文件失败！\n");
        fclose(fp);
        return;
    }

    //读取文件内容
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("内存分配失败！\n");
        fclose(fp);
        fclose(tempfile);
        return;
    }

    //逐行读取文件内容并写入临时文件
    while (fgets(buffer, fileSize + 1, fp)!= NULL) {
        char* match = strstr(buffer, id);
        if (match == NULL) {
            fputs(buffer, tempfile);
        }else{
            fputs(newContent, tempfile);
            fputs("\n",tempfile);
        }
    }
    //关闭文件
    fclose(fp);
    //重新打开文件并清空写入
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        free(buffer);
        return;
    }

    //从临时文件中读取内容，并且写回原来文件
    rewind(tempfile);
    while (fgets(buffer, fileSize + 1, tempfile)!= NULL) {
        fputs(buffer, fp);
    }
    //关闭临时文件
    fclose(tempfile);
    //关闭原文件
    fclose(fp);
    //释放内存
    free(buffer);
}

void editContentForTwoFields(const char* filename, const char* field1, const char* field2, const char* newContent) {
    // 打开原文件
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }

    // 创建临时文件
    FILE* tempfile = tmpfile();
    if (tempfile == NULL) {
        printf("创建临时文件失败！\n");
        fclose(fp);
        return;
    }

    char line[22];

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), fp) != NULL) {
        char fileField1[50], fileField2[50], fileField3[50], fileField4[50];

        // 假设文件的每一行格式为: field1,field2,field3,field4
        sscanf(line, "%[^,],%[^,],%[^,],%s", fileField1, fileField2, fileField3, fileField4);

        // 检查字段匹配
        int match1 = (field1 != NULL) && (strcmp(fileField1, field1) == 0);
        int match2 = (field2 != NULL) && (strcmp(fileField2, field2) == 0);

        // 如果匹配，则替换为新内容；否则写回原内容
        if (match1 && (field2 == NULL || match2)) {
            fputs(newContent, tempfile);
            fputs("\n", tempfile);
        } else {
            fputs(line, tempfile);
        }
    }

    // 关闭原文件
    fclose(fp);

    // 重新打开原文件用于写入，并清空内容
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法重新打开文件：%s\n", filename);
        fclose(tempfile);
        return;
    }

    // 将临时文件的内容写回原文件
    rewind(tempfile);
    while (fgets(line, sizeof(line), tempfile) != NULL) {
        fputs(line, fp);
    }

    // 关闭临时文件和原文件
    fclose(tempfile);
    fclose(fp);

    printf("内容编辑成功！\n");
}

char* createContent(Student* student,Score* score,Course* course){
    //判断生成结构体类型
    int structType;
    if (student != NULL){
        structType = 0;
    }else if (score != NULL){
        structType = 1;
    }else if (course != NULL){
        structType = 2;
    }else{
        printf("未知结构体类型！\n");
        return NULL;
    }


    char* newContent = (char*)malloc(1024);
    if (newContent == NULL){
        printf("内存分配失败！\n");
        return NULL;
    }
    newContent[0] = '\0';

    switch (structType){
        case 0:
            //生成学生信息
            sprintf(newContent, "%s,%s,%s,%s,%s,%s\n",student->studentID,student->studentName,student->gender,student->birthDate,student->phone,student->email);
            break;
        case 1:
            //生成成绩信息
            sprintf(newContent, "%s,%s,%s,%s\n",score->courseID,score->studentID,score->studentName,score->score);
            break;
        case 2:
            //生成课程信息
            sprintf(newContent, "%s,%s,%s,%s\n",course->courseID,course->courseName,course->credit,course->courseType);
            break;
        default:
            printf("未知结构体类型！\n");
            free(newContent);
            return NULL;
    }

    return newContent;

}


