// 实现学生成绩的增删改查功能。
// 读取和保存成绩信息到文件。

#include <stdio.h>
#include "utils.h"
#include "score.h"

typedef struct Score{
    char courseID[10];//课程号
    char studentID[10];//学生学号
    char studentName[20];//学生姓名
    char score[5];//成绩
}Score;

void manageScore(){
    loadScoresFromFile();

}
void addScore(){
    loadStudentsFromFile();






}
void deleteScore();
void updateScore();
void viewScores();
