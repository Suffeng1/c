// 统计并打印学生所有课程的成绩及平均分。
// 统计学生已修的总学分。
// 判断学生是否达到毕业要求。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "student.h"
#include "course.h"
#include "score.h"
#include "statistics.h"
typedef struct Credit{
    int foundamental;
    int majorRequired;
    int majorElective;
    int practicalCourse;
}Credit;


void analyzeStatistics(){

    int choice;
    do{
        freeScoreList();
        printf("欢迎使用学生信息管理系统！\n");
        printf("1. 统计并打印学生所有课程的成绩及平均分。\n");
        printf("2. 统计学生已修的总学分。\n");
        printf("3. 退出。\n");
        printf("请选择：");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                loadScoresFromFile("scores.txt");
                printAllScores();
                break;
            case 2:
                loadScoresFromFile("scores.txt");

                printAllCredits();
                break;
            case 3:
                break;
            default:
                printf("输入错误，请重新输入。\n");
                break;
        }
    }while (choice!= 3);
}



void printAllScores(){
    char studentId[10];
    printf("请输入学生学号：");
    scanf("%s", studentId);


    Score *p = scoreHead;
    int sum = 0;
    int count = 0;
    while(p!= NULL){
        if(strcmp(p -> studentID, studentId) == 0){
            printf("%s 课程的成绩为：%s\n", p -> courseID, p -> score);
            sum += atoi(p -> score);
            count++;
        }
        p = p -> next;
    }
    if(count == 0){
        printf("该学生还没有修任何课程。\n");
    }else{
        double average = (double)sum / count;
        printf("该学生的平均分为：%.2f\n", average);
    }

}



void printAllCredits(){
    char studentId[10];
    printf("请输入学生学号：");
    scanf("%s", studentId);

    Score *p = scoreHead;
    Credit credit;
    credit.foundamental = 0;
    credit.majorRequired = 0;
    credit.majorElective = 0;
    credit.practicalCourse = 0;
    while(p!= NULL){
        if((strcmp(p -> studentID, studentId) == 0) && (atoi(p -> score) >= 60)){
            //判断及格


            Course *q = getCreditAndTypeFromCourse(p -> courseID);
            printf("%s 课程的学分为：%s\n", q -> courseName, q -> credit);
            if(strcmp(q -> courseType, "综合实践") == 0){
                credit.practicalCourse += atoi(q -> credit);
            }else if(strcmp(q -> courseType, "基础类") == 0){
                credit.foundamental += atoi(q -> credit);
            }else if(strcmp(q -> courseType, "专业选修课") == 0){
                credit.majorElective += atoi(q -> credit);
            }else if(strcmp(q -> courseType, "专业基础类") == 0){
                credit.majorRequired += atoi(q -> credit);
            }
        }
        p = p -> next;
    }
    printf("该学生已修的总学分为：\n");
    printf("综合实践：%d\n", credit.practicalCourse);
    printf("基础类：%d\n", credit.foundamental);
    printf("专业选修课：%d\n", credit.majorElective);
    printf("专业基础类：%d\n", credit.majorRequired);
}



void checkGraduation(){
    freeScoreList();
    loadScoresFromFile("scores.txt");
    char studentId[10];
    printf("请输入学生学号：");
    scanf("%s", studentId);
    Credit credit = {0, 0, 0, 0};
    Score *p = scoreHead;
    while(p!= NULL){
        if(strcmp(p -> studentID, studentId) == 0 && (atoi(p -> score) >= 60)){
            Course *q = getCreditAndTypeFromCourse(p -> courseID);
            if(strcmp(q -> courseType, "综合实践") == 0){
                credit.practicalCourse += atoi(q -> credit);
            }
            else if(strcmp(q -> courseType, "基础类") == 0){
                credit.foundamental += atoi(q -> credit);
            }
            else if(strcmp(q -> courseType, "专业选修课") == 0){
                credit.majorElective += atoi(q -> credit);
            }
            else if(strcmp(q -> courseType, "专业基础类") == 0){
                credit.majorRequired += atoi(q -> credit);
            }
        }
        p = p -> next;
    }

    if(credit.practicalCourse >= 25 && credit.foundamental >= 20 && credit.majorElective >= 25 && credit.majorRequired >= 30){
        printf("恭喜，%s 已达到毕业要求！\n", studentId);
    }else{
        printf("很遗憾，%s 未达到毕业要求！\n", studentId);
    }
    return;
}

Course* getCreditAndTypeFromCourse(char* courseId){
    loadCoursesFromFile("course.txt");
    Course *p = courseHead;
    while(p!= NULL){
        if(strcmp(p -> courseID, courseId) == 0){
            return p;
        }
        p = p -> next;
    }
    return NULL;
}


