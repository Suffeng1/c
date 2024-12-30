#include <stdio.h>
#include "student.h"
#include "course.h"
#include "score.h"
#include "statistics.h"

int main() {
    int choice;
    do {
        printf("1. 学生信息管理\n");
        printf("2. 课程信息管理\n");
        printf("3. 成绩信息管理\n");
        printf("4. 成绩统计分析\n");
        printf("5. 判断毕业资格\n");
        printf("6. 退出系统\n");
        printf("请输入选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1: manageStudent(); break;
            case 2: manageCourse(); break;
            case 3: manageScore(); break;
            // case 4: analyzeStatistics(); break;
            // case 5: checkGraduation(); break;
            case 6: printf("退出系统。\n"); break;
            default: printf("无效输入，请重新选择。\n");
        }
    } while (choice != 6);

    return 0;
}
