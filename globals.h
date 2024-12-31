// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

typedef struct Course{
    char courseID[10];//课程号
    char courseName[50];//课程名称
    char credit[10];//学分
    char courseType[20];//课程类型
    struct Course* next;
}Course;

typedef struct Score {
	char courseID[10];//课程号
	char studentID[10];//学生学号
	char studentName[20];//学生姓名
	char score[5];//成绩
	struct Score *next;
}Score;

typedef struct Student {
    char studentID[20]; // 学号
    char studentName[100];      // 姓名
    char gender[10];     // 性别
    char birthDate[20]; // 出生年月
    char phone[20];      // 电话
    char email[100];     // E-mail
    struct Student* next;// 指向下一个学生信息的指针

}Student;

extern Course* courseHead;   // 定义并初始化全局变量
extern Score* scoreHead;
extern Student* studentHead;

#endif
