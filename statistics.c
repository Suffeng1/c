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




void analyzeStatistics();
void printAllScores(int studentId){
    loadStudentsFromFile();
    loadScoresFromFile();

    organizeScores()







}

void calculateAverageScore(int studentId);
void checkGraduation();
