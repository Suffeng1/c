# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g

# 源文件和目标文件
SRCS = main.c student.c course.c score.c utils.c statistics.c globals.c
OBJS = $(SRCS:.c=.o)

# 可执行文件名
TARGET = main

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译源文件生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(OBJS) $(TARGET)




debug: $(TARGET)
	gdb $(TARGET)

# 伪目标
.PHONY: all clean
