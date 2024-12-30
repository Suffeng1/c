// 实现学生信息的增删改查功能。
// 读取和保存学生信息到文件。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "student.h"

typedef struct Student {
    char studentID[20]; // 学号
    char studentName[100];      // 姓名
    char gender[10];     // 性别
    char birthDate[20]; // 出生年月
    char phone[20];      // 电话
    char email[100];     // E-mail
    struct Student* next;// 指向下一个学生信息的指针
    struct Score* last; // 指向最后一个成绩信息的指针
} Student;

Student* studentHead = NULL; // 指向学生信息链表的头指针

void manageStudent() {
    freeStudentList();
    loadStudentsFromFile("students.txt");
    // printStudentList();
    int choice;
    do {
        printf("学生信息管理系统\n");
        printf("1. 增加学生信息\n");
        printf("2. 删除学生信息\n");
        printf("3. 修改学生信息\n");
        printf("4. 查看学生信息\n");
        printf("5. 退出系统\n");
        printf("请选择(1-5): ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                viewStudents();
                break;
            case 5:
                freeStudentList();
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
            }
    }while (choice!= 5);
}

void loadStudentsFromFile(const char* filename) {
    freeStudentList();
    // if (studentHead == NULL) {
    // printf("链表已清空！\n");
    // }

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line,sizeof(line),fp)){
        // printf("读取的行内容: %s\n", line);

        Student* student = (Student*)malloc(sizeof(Student));
        if (student == NULL) {
            printf("内存分配失败！\n");
            fclose(fp);
            return;
        }
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s",student->studentID,student->studentName,student->gender,student->birthDate,student->phone,student->email);

        //插入到链表头
        student->next = studentHead;
        studentHead = student;

    }
    fclose(fp);
    printf("学生信息加载成功！\n");
}

void freeStudentList(){
    Student* curr = studentHead;
    while (curr != NULL){
        Student* temp = curr;
        curr = curr->next;
        free(temp);
    }
    studentHead = NULL;
}

void printStudentList() {
    Student* curr = studentHead;
    while (curr != NULL) {
        printf("学号: %s, 姓名: %s, 性别: %s, 出生日期: %s, 电话: %s, 邮箱: %s\n",
               curr->studentID, curr->studentName, curr->gender, curr->birthDate, curr->phone, curr->email);
        curr = curr->next;
    }
}


void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student));

    if (newStudent == NULL) {
        printf("内存分配失败！\n");
        return;
    }

    printf("请输入学号: ");
    scanf("%s", newStudent->studentID);
    printf("请输入姓名: ");
    scanf("%s", newStudent->studentName);
    printf("请输入性别: ");
    scanf("%s", newStudent->gender);
    printf("请输入出生年月: ");
    scanf("%s", newStudent->birthDate);
    printf("请输入电话: ");
    scanf("%s", newStudent->phone);
    printf("请输入E-mail: ");
    scanf("%s", newStudent->email);


    // 保存学生信息到文件
    FILE* fp = fopen("students.txt", "a+");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    fprintf(fp, "%s,%s,%s,%s,%s,%s\n", newStudent->studentID, newStudent->studentName, newStudent->gender, newStudent->birthDate, newStudent->phone, newStudent->email);

    newStudent -> next = studentHead;
    studentHead = newStudent;
    printf("学生信息添加成功！\n");
    fclose(fp);

}

void deleteStudent() {

    char studentID[20];
    printf("请输入要删除的学生学号: ");
    scanf("%s", studentID);

    // 遍历链表，找到要删除的学生信息
    Student* prev = NULL;
    Student* curr = studentHead;
    while (curr!= NULL) {
        if (strcmp(curr->studentID, studentID) == 0) {
            // 找到了要删除的学生信息
            if (prev == NULL) {
                // 要删除的学生信息是链表头部
                studentHead = curr->next;
            } else {
                // 要删除的学生信息不是链表头部
                prev->next = curr->next;
            }

            //删除文件中的信息
            removeContent("students.txt", studentID);
            printf("学生信息删除成功！\n");

            // 释放内存
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("没有找到要删除的学生信息！\n");
}

void updateStudent() {

    char studentID[20];
    printf("请输入要修改的学生学号: ");
    scanf("%s", studentID);

    // 遍历链表，找到要修改的学生信息
    Student* curr = studentHead;
    while (curr!= NULL) {
        if (strcmp(curr->studentID, studentID) == 0) {
            printf("请输入新的学生信息:\n");
            printf("姓名: ");
            scanf("%s", curr->studentName);
            printf("性别: ");
            scanf("%s", curr->gender);
            printf("出生年月: ");
            scanf("%s", curr->birthDate);
            printf("电话: ");
            scanf("%s", curr->phone);
            printf("E-mail: ");
            scanf("%s", curr->email);

            //生成新内容
            char* newContent = createContent(curr,NULL,NULL);
            if (newContent == NULL) {
                printf("内存分配失败！\n");
                return;
            }
            // 保存修改后的信息到文件
            editContent("students.txt",curr->studentID,newContent);
            printf("学生信息修改成功！\n");
            free(newContent);
            return;
        curr = curr->next;
        }
    }
    printf("没有找到要修改的学生信息！\n");

}

void viewStudents() {

    char studentID[20];
    printf("请输入要查看的学生学号: ");
    scanf("%s", studentID);

    // 遍历链表，找到要查看的学生信息
    Student* curr = studentHead;
    while (curr != NULL) {
        if (strcmp(curr->studentID, studentID) == 0) {
            printf("学号: %s\n", curr->studentID);
            printf("姓名: %s\n", curr->studentName);
            printf("性别: %s\n", curr->gender);
            printf("出生年月: %s\n", curr->birthDate);
            printf("电话: %s\n", curr->phone);
            printf("E-mail: %s\n", curr->email);
            return;
        }
        curr = curr->next;
    }
    printf("没有找到要查看的学生信息！\n");
    free(curr);
}
