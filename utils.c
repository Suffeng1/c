//提供通用功能，例如文件操作、输入校验、通用排序等。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct Student {
    char studentID[20]; // 学号
    char studentName[100];      // 姓名
    char gender[10];     // 性别
    char birthDate[20]; // 出生年月
    char phone[20];      // 电话
    char email[100];     // E-mail
    struct Student* next;// 指向下一个学生信息的指针
    struct Score* last;// 指向最后一个成绩信息的指针
} Student;

typedef struct Score{
    char courseID[10];//课程号
    char studentID[10];//学生学号
    char studentName[20];//学生姓名
    char score[5];//成绩
}Score;

typedef struct Course{
    char courseID[10];//课程号
    char courseName[50];//课程名称
    char credit[10];//学分
    char courseType[20];//课程类型
}Course;

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
            sprintf(newContent, "%s,%s,%s,%s,%s,%s",student->studentID,student->studentName,student->gender,student->birthDate,student->phone,student->email);
            break;
        case 1:
            //生成成绩信息
            sprintf(newContent, "%s,%s,%s,%s",score->courseID,score->studentID,score->studentName,score->score);
            break;
        case 2:
            //生成课程信息
            sprintf(newContent, "%s,%s,%s,%s",course->courseID,course->courseName,course->credit,course->courseType);
            break;
        default:
            printf("未知结构体类型！\n");
            free(newContent);
            return NULL;
    }

    return newContent;

}

void organizeScores(score* scoreHead){
    score* current = scoreHead;
    while (current)
}
