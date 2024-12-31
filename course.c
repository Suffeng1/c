// 实现课程信息的增删改查功能。
// 读取和保存课程信息到文件。

#include <stdio.h>
#include "globals.h"
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "course.h"


void loadCoursesFromFile(const char* filename){
    freeCourses();
    FILE *fp = fopen(filename,"r");
    if(fp == NULL){
        printf("文件打开失败！\n");
        return;
    }
    char line[100];
    while(fgets(line,sizeof(line),fp)){
        Course* course=(Course*)malloc(sizeof(Course));
        if(course==NULL){
            printf("内存分配失败！");
            fclose(fp);
            return;
        }
        sscanf(line,"%[^,],%[^,],%[^,],%s\n",course->courseID,course->courseName,course->credit,course->courseType);
        course->next=courseHead;
        courseHead=course;

    }
    fclose(fp);

}
void manageCourse(){
    freeCourses();
    loadCoursesFromFile("course.txt");
    int choice;
    do{

        printf("课程维护系统\n");
        printf("1. 增加课程信息\n");
        printf("2. 删除课程信息\n");
        printf("3. 修改课程信息\n");
        printf("4. 查看课程信息\n");
        printf("5. 退出系统\n");
        printf("请选择(1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCourse();
                break;
            case 2:
                deleteCourse();
                break;
            case 3:
                updateCourse();
                break;
            case 4:
                viewCourses();
                break;
            case 5:
                freeCourses();
                break;
            case 0:
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
    }while(choice!=5);

}

void addCourse(){
    Course* newcourse=(Course*)malloc(sizeof(Course));
    if(newcourse==NULL){
        printf("内存分配失败！");
        return;
    }
    printf("请输入课程号：");
    scanf("%s",newcourse->courseID);
    printf("请输入课程名称：");
    scanf("%s",newcourse->courseName);
    printf("请输入学分：");
    scanf("%s",newcourse->credit);
    printf("请输入课程类别:");
    scanf("%s",newcourse->courseType);
    //将课程信息写入文件
    FILE *fp = fopen("course.txt","a+");
    if(fp == NULL){
        printf("文件打开失败！");
        return;
    }

    fprintf(fp,"%s,%s,%s,%s\n",newcourse->courseID,newcourse->courseName,newcourse->credit,newcourse->courseType);

    newcourse -> next = courseHead;
    courseHead = newcourse;
    printf("课程信息添加成功！");
    fclose(fp);

}

void updateCourse(){
    char courseID[10];
    printf("请输入要修改的课程号：\n");
    scanf("%s",courseID);
    Course* curr=courseHead;
    while(curr!=NULL){
        if(strcmp(curr->courseID,courseID)==0){
            printf("请输入新的课程号：\n");
            scanf("%s",curr->courseID);
            printf("请输入新的课程名称：\n");
            scanf("%s",curr->courseName);
            printf("请输入新的学分：\n");
            scanf("%s",curr->credit);
            printf("请输入新的课程类别：\n");
            scanf("%s",curr->courseType);
            char*newContent = createContent(NULL,NULL,curr);
            if(newContent==NULL){
                printf("内存分配失败！");
                return;
            }
            editContent("course.txt",curr->courseID,newContent);
            printf("修改成功！\n");
            free(newContent);
            return;

        }
        curr=curr->next;
    }
    printf("未找到该课程信息\n");

}
void viewCourses(){char courseID[10];
    printf("请输入要查看的课程号：\n");
    scanf("%s",courseID);
    Course* curr=courseHead;
    while(curr!=NULL){
        if(strcmp(curr->courseID,courseID)==0){
            printf("%s,%s,%s,%s\n",curr->courseID,curr->courseName,curr->credit,curr->courseType);
            return;
        }
        curr=curr->next;
    }
    printf("未找到该课程信息\n");

}

void printcourses(){
    Course* curr=courseHead;
    while(curr!=NULL){
        printf("%s,%s,%s,%s\n",curr->courseID,curr->courseName,curr->credit,curr->courseType);
        curr=curr->next;
    }
}







void deleteCourse(){
    printf("请输入要删除的课程号：\n");
    char courseID[10];
    scanf("%s",courseID);



    Course* curr=courseHead ;
    Course* prev=NULL;
    while(curr!=NULL){

        if(strcmp(curr->courseID,courseID)==0){
            if(prev==NULL){
                courseHead=curr->next;
            }else{
                prev->next = curr->next;
            }
            removeContent("course.txt",courseID);
            printf("删除成功！");

            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("未找到该课程信息!\n");
}
void freeCourses(){
    Course* curr=courseHead;
    while(curr!=NULL){
        Course* temp=curr;
        curr=curr->next;
        free(temp);
    }
    courseHead=NULL;

}




