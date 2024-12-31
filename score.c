// 实现学生成绩的增删改查功能。
// 读取和保存成绩信息到文件。

#include <stdio.h>

#include "globals.h"
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "score.h"



void manageScore() {
	freeScoreList();
	loadScoresFromFile("scores.txt");

	int choice;
	do {
		printf("学生成绩管理系统\n");
		printf("1. 增加学生成绩\n");
		printf("2. 删除学生成绩信息\n");
		printf("3. 修改学生成绩信息\n");
		printf("4. 查找学生成绩信息\n");
		printf("5. 退出系统\n");
		printf("请选择(1—5) ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				addScore();
				break;
			case 2:
				deleteScore();
				break;
			case 3:
				updateScore();
				break;
			case 4:
				viewScores();
				break;
			case 5:
				freeScoreList();
				break;
			default:
				printf("输入错误请重新输入\n");
				break;
		}
	} while (choice != 5);

}
void printScoresList() {
	Score* stu;
	stu = scoreHead;
	while (stu != NULL) {
		printf("%s,%s,%s,%s", stu->courseID, stu->studentID, stu->studentName, stu->score);
		stu = stu->next;
	}
}

void loadScoresFromFile(const char *filename) {
	freeScoreList();


	printScoresList();

	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("无法打开文件：%s\n", filename);
		return;
	}

	char line[1024];
	while (fgets(line, sizeof(line), fp)) {
		Score *scorenew = (Score *)malloc(sizeof(Score));
		if (scorenew == 0) {
			printf("内存分配失败！");
			fclose(fp);
			return;

		}
		sscanf(line, "%[^,],%[^,],%[^,],%s", scorenew-> courseID, scorenew->studentID,scorenew-> studentName, scorenew-> score);

		scorenew-> next = scoreHead;
		scoreHead = scorenew;
	}
	fclose(fp);
	printf("学生成绩加载成功！\n");

}

void freeScoreList() {
	Score* curr = scoreHead;
	while (curr != NULL) {
		Score* temp = curr;
		curr = curr-> next;
		free(temp);
	}
	scoreHead = NULL;
}


void addScore() {
	Score* newScore = (Score *)malloc(sizeof(Score));
	printf("请输入新学生课程号:");
	scanf("%s", newScore->courseID);
	printf("请输入新学生学号:");
	scanf("%s", newScore->studentID);
	printf("请输入新学生姓名:");
	scanf("%s", newScore->studentName);
	printf("请输入新学生相应课程成绩:");
	scanf("%s", newScore->score);
	FILE *fp = fopen("scores.txt", "a+");
	if (fp == NULL) {
		printf("文件加载失败!\n");
		return;
	}
	fprintf(fp, "%s,%s,%s,%s\n", newScore->courseID, newScore->studentID, newScore->studentName, newScore->score);

	newScore -> next = scoreHead;
	scoreHead = newScore;
	printf("学生成绩信息添加成功！\n");
	fclose(fp);

}

void deleteScore() {
	char studentID[10];
	char courseID[10];
	printf("请输入您想删除成绩成绩的学号:\n");
	scanf("%s", studentID);
	printf("请输入您想删除成绩成绩的课程号:\n");
	scanf("%s", courseID);
	Score* curr;
	Score* pre;
	pre = NULL;
	curr = scoreHead;
	while (curr != NULL) {
		if (strcmp(curr->studentID, studentID) == 0 && strcmp(curr->courseID, courseID) == 0) {
			if (pre == NULL) {
				scoreHead = curr->next;
			} else {
				pre->next = curr->next;
			}
			removeContentForTwoFields("scores.txt", studentID, courseID);
			printf("学生成绩信息删除成功!");
			free(curr);
			free(pre);
			return;
		}
		pre = curr;
		curr = curr->next;
	}
	printf("未找到相应学生成绩信息!");
}

void updateScore() {
	char line1[10];
	char line2[10];
	printf("请输入您想修改学生信息的学号:");
	scanf("%s", line1);
	printf("请输入您想修改学生信息的课程号:");
	scanf("%s", line2);

	Score* curr;
	curr = scoreHead;
	while (curr != NULL) {
		if (strcmp(curr->studentID, line1) == 0 && strcmp(curr->courseID, line2) == 0) {
			printf("请输入新修改学生的信息:\n");
			printf("请输入新修改学生课程号:");
			scanf("%s", curr->courseID);
			printf("请输入新修改学生学号:");
			scanf("%s", curr->studentID);
			printf("请输入新修改学生的姓名:");
			scanf("%s", curr->studentName);
			printf("请输入新修改学生的成绩:");
			scanf("%s", curr->score);

			char* newContent = createContent(NULL, curr, NULL);
			if (newContent == NULL) {
				printf("内存分配失败！\n");
				return;
			}
			editContentForTwoFields("scores.txt", curr->courseID, curr->studentID, newContent);
			printf("学生成绩信息修改成功！\n");
			free(newContent);
			return;
		}
		curr = curr->next;

	}
	printf("未找到相应学生信息!\n");
}

void viewScores() {
	char line[10];
	printf("请输入要查找学生的学号:\n");
	scanf("%s", line);
	Score* curr;
	curr = scoreHead;
	while (curr != NULL) {
		if (strcmp(curr->studentID, line) == 0) {
			printf("课程号：%s", curr->courseID);
			printf("学号：%s", curr->studentID);
			printf("学生姓名：%s", curr->studentName);
			printf("成绩：%s\n", curr->score);

		}
		curr = curr->next;
	}
	printf("未找到相应学生信息！");
	free(curr);
}
