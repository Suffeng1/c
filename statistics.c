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

void manageScore(){
    while(1){
        int choice;
        printf("1. 统计并打印学生所有课程的成绩及平均分。\n");
        printf("2. 统计学生已修的总学分。\n");
        printf("3. 判断学生是否达到毕业要求。\n");
        printf("4. 退出。\n");
        printf("请选择：");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                analyzeStatistics();
                break;
            case 2:
                calculateTotalCredits();
                break;
            case 3:
                checkGraduation();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("输入错误，请重新输入。\n");
                break;
        }
    }
}


void analyzeStatistics();
void printAllScores(char studentId){
    loadScoresFromFile();

    score *p = scoresHead;
    while(p!= NULL){
        if(p -> studentId == studentId){
            printf("%s 课程的成绩为：%s\n", p -> courseName, p -> score);
        }
        p = p -> next;
    }
}

void calculateAverageScore(char studentId){
    loadScoresFromFile();
    score *p = scoresHead;
    int sum = 0;
    int count = 0;
    while(p!= NULL){
        if(p -> studentId == studentId){
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
void printAllCredits(char studentId){
    loadScoresFromFile();
    score *p = scoresHead;
    int totalCredits = 0;

    while(p!= NULL){
        if(p -> studentId == studentId){
            totalCredits += atoi(p -> credits);
        }
        p = p -> next;
    }

    if(totalCredits == 0){
        printf("该学生还没有修任何课程。\n");
    }else{
        printf("该学生已修的总学分为：%d\n", totalCredits);
        }
}
void checkGraduation(char studentId){
    loadScoresFromFile();

    score *p = scoresHead;

    int totalCredits = 0;
}

