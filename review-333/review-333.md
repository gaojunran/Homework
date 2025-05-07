# Number Systems

## 任意数转十进制

![alt text](<CleanShot 2025-04-14 at 16.59.15@2x.png>)

## 十进制转任意数

![alt text](<CleanShot 2025-04-14 at 16.54.17@2x.png>)

![alt text](<CleanShot 2025-04-14 at 16.59.40@2x.png>)

## 转换成二进制补码

![alt text](<CleanShot 2025-04-14 at 16.55.27@2x.png>)

## 浮点表示

Mantissa：

![alt text](<CleanShot 2025-04-14 at 17.00.43@2x.png>)

![alt text](<CleanShot 2025-04-14 at 17.05.24@2x.png>)

# Fundamentals of C Language

## 数据类型

![alt text](<CleanShot 2025-04-14 at 17.38.10@2x.png>)

![alt text](<CleanShot 2025-04-14 at 17.38.21@2x.png>)

## 按位运算

![alt text](<CleanShot 2025-04-14 at 17.39.21@2x.png>)

# Arrays. Strings Structures

1. `const char* greet = "Hello"`: 以这种方式定义的字符串存在于只读存储区，不能修改其内容

2. `char greet[] = "Hello"`: 以这种方式定义的字符串存在于栈区，但等效于`char* const greet`，不可以修改指针指向

3. 字符串函数

    ![alt text](<CleanShot 2025-04-14 at 17.46.28@2x.png>)

4. `struct`, `typedef`
    ```c
    struct Point {
      int x;
      int y;
    }  // define
    struct Point p1;  // declare
    p1 = {1, 2};  // initialize
    
    typedef struct Point {
      int x;
      int y;
    } Point;  // define and typedef

    typedef struct {
      int x;
      int y;
    } Point;  // define and typedef

    Point p1 = {1, 2};  // declare and initialize

    typedef struct node {
      int value;
      struct node* next;
    } Node, *NodePtr;
    ```

# Dynamic Memory Allocation. Linked Lists

## 链表操作

```c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int number;
    struct node *next;
};

void insert_node(struct node **head, struct node **tail, int value) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->number = value;
    new_node->next = NULL;

    if (*tail == NULL) {
        *head = *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

void print_list(struct node *head) {
    int count = 0;
    struct node *current = head;
    while (current != NULL) {
        count++;
        printf("%d -> ", current->number);
        current = current->next;
    }
    printf("NULL\n");
    printf("List size: %d\n", count);
    printf("List capacity: %lu\n", count * sizeof(struct node));
}

void free_list(struct node *head) {
    struct node *current = head;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

struct node *last_occur(struct node *h, int x) {
    struct node *last = NULL;
    struct node *current = h;

    while (current != NULL) {
        if (current->number == x) {
            last = current;
        }
        current = current->next;
    }

    return last;
}

void delete_node(struct node **ph, int x) {
    struct node *current = *ph;
    struct node *previous = NULL;

    if (current != NULL && current->number == x) {
        *ph = current->next;
        free(current);
        return;
    }

    while (current != NULL && current->number != x) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return;

    previous->next = current->next;
    free(current);
}
```

# Files. Input and Output

1. `FILE * fopen( const char *filename, const char *mode );`

![alt text](<CleanShot 2025-04-14 at 18.20.27@2x.png>)

2. `int fclose(FILE *stream);` 成功返回0，失败返回EOF。

3. `int getchar(void)`：从标准输入读取一个字符，返回该字符的ASCII码，如果到达文件末尾或发生错误，返回EOF（-1）。

4. `int putchar(int c)`：将字符c输出到标准输出，返回c，如果发生错误，返回EOF。

5. `int fgetc(FILE *stream)`：从文件流中读取一个字符，返回该字符的ASCII码，如果到达文件末尾或发生错误，返回EOF（-1）。

6. `int fputc(int c, FILE *stream)`：将字符c输出到文件流，返回c，如果发生错误，返回EOF。

7. `int fscanf(FILE *stream, const char *format, ...)`：从文件流中读取数据，按照format格式解析，返回成功读取的参数个数，如果到达文件末尾或发生错误，返回EOF。

8. `int fprintf(FILE *stream, const char *format, ...)`：将数据按照format格式写入文件流，返回成功写入的参数个数，如果发生错误，返回EOF。

9. `int ferror(FILE *stream)`：检查文件流是否有错误，如果有错误返回非零值，否则返回0。

10. `int feof(FILE *stream)`：检查文件流是否到达文件末尾，如果到达文件末尾返回非零值，否则返回0。

11. `int fflush(FILE *stream)`：刷新文件流，将缓冲区中的数据写入文件，如果成功返回0，否则返回EOF。

![alt text](<CleanShot 2025-04-14 at 18.29.31@2x.png>)

# More about Strings and Pointer Arithmetic

1. `char *gets(char *str)`：从标准输入读取一行字符串，直到遇到**换行符或文件结束符**，**将换行符替换为空字符**，并返回指向str的指针。如果发生错误，返回NULL。

2. `int puts(const char *str)`：将字符串str输出到标准输出，**并在末尾添加换行符**。返回非负值。

3. `char *fgets(char *str, int n, FILE *stream)`：从文件流中读取一行字符串，直到遇到**换行符或文件结束符**，**保留换行符**，并返回指向str的指针。如果发生错误，返回NULL。

4. `int fputs(const char *str, FILE *stream)`：将字符串str输出到文件流，**不添加换行符**。返回非负值。

5. `char *strncpy(char *dest, const char *src, size_t n)`：将src的前n个字符复制到dest，如果src的长度小于n，则用空字符填充dest。返回dest。

6. `char *strchr(const char *str, int c)`：在字符串str中查找字符c，**返回指向该字符的指针**，如果未找到，返回NULL。

7. `char *strstr(const char *haystack, const char *needle)`：在字符串haystack中查找字符串needle，**返回指向该字符串的指针**，如果未找到，返回NULL。

8. `int sprintf(char *str, const char *format, ...)`：将数据按照format格式写入字符串str，返回成功写入的字符个数，如果发生错误，返回EOF。

# More Memory Management

![alt text](<CleanShot 2025-04-14 at 19.03.17@2x.png>)

1. `void * memmove(void *dst, const void *src, size_t len);`: 将src指向的内存块中的len个**字节**复制到dst指向的内存块中，如果dst和src重叠，则保证复制正确。返回dst。

具体地，如果 源地址 < 目标地址，而且 区域有重叠，memmove 会从后往前拷贝，避免数据被覆盖。如果 源地址 > 目标地址 或者 没有重叠，它就可以从前往后正常拷贝。

2. `void* calloc(size_t num, size_t size);`: 分配num个大小为size的内存块，并将所有字节初始化为0。返回指向分配的内存块的指针，如果分配失败，返回NULL。

3. `void* realloc(void *ptr, size_t size);`: 重新分配ptr指向的内存块的大小为size，如果ptr为NULL，则相当于malloc(size)。如果ptr不为NULL，则原来的内存块会被释放，并返回指向新分配的内存块的指针。如果size为0，则原来的内存块会被释放，并返回NULL。

# Bit Fields. Bitwise Operators


1. Bit Field Size 通常应该是`unsigned`类型的，而且遵循结构体对齐规则：

    - 一旦一个`unsigned int`字段无法完全容纳在当前 4 字节中，编译器会自动换到新的单元。
    - 实际结构体大小由编译器决定，会受 对齐和打包策略 影响。

2. 不能对 Bit Field 取地址。

3. 按位运算：

    - 将最高位（第 8 位）的位设为 0 ：`x &= 0x7F;`
    - 将最高位（第 8 位）的位设为 1 ：`x |= 0x80;`
    - 找出两个二进制数中不同的位：`x ^ y;`（结果中`1`表示不同的位）
    - 反转二进制数中的所有位：`~x;`
    - 把前 4 位设为`1101`，后四位不变：`x = (x & 0x0F) | 0xD0;`
    - 反转第2、5、8位，其它位不变：`x ^= 0x92`。（与`1`做异或操作等同于反转）

4. 对于右移操作（`>>`）：
    - 通常相当于除以 2 的幂。例如，`x >> 1` 相当于 `x / 2^1`。
    - 如果被移位的值的符号位是 0（即该值是非负数），那么右移后空出来的高位用 0 填充。
    - 如果符号位是 1（即该值是负数），那么右移后空出来的高位用什么填充是与实现相关的。在大多数情况下，空位会用 1 填充。

5. 对于左移操作（`<<`）：

    - 通常相当于乘以 2 的幂。例如，`x << 1` 相当于 `x * 2^1`。
    - 但可能会导致高位溢出。

# The C Preprocessor

1. 带参数的`#define`宏：

    ```c
    #define SQR(x) ((x) * (x))
    ```
    确保宏参数被括号包围，以保证正确的运算顺序。
2. `#define`中的`#`

    ```c
    #define PRINT(x) printf(#x "\n")

    PRINT(Hello); // #x is “Hello”
    ```

3. `#define`中的`##`

    ```c
    #define CONCAT(a, b) a ## b

    int main(void) {
        int xy = 10;
        printf("%d", CONCAT(x, y)); // 10
        return 0;
    }
    ```
4. 其他宏

    ```c
    #if DEBUG == 1
    printf("Token = %s\n", tok);
    #elif DEBUG == 2 
    printf("No. of words = \n", nw);
    #else
    printf("No debug info\n");
    #endif
    ```

    ```c
    #define DEBUG 1
    #undef DEBUG  // 取消 DEBUG 的定义
    #ifdef DEBUG
    printf("No. of words = \n", nw); 
    #endif
    ```

    ```c
    #ifndef STRUCT_H  // 确保头文件只被引入一次
    #define STRUCT_H
    #include "struct_def.h"
    #endif
    ```

    ```c
    #ifndef INTEL
    #error Wrong architecture  // 在预处理阶段报错
    #endif
    ```

5. `#pragma`指令

    ```c
    #pragma soft-float
    /* 告知编译器，目标系统没有硬件浮点单元，
    应当使用软件库实现浮点运算  */
    #pragma MC68000
    /* 生成适用于Motorola 68000 CPU的机器代码. */
    #pragma pack(1)  
    /* 要求编译器在内存中紧密排列结构体成员，
    不进行任何填充。 */
    ```

6. 预定义宏

    ```c
     #include <stdio.h>
    int main() {
    printf("File :%s\n", __FILE__ ); // main.c
    printf("Date :%s\n", __DATE__ ); // Apr 14 2025
    printf("Time :%s\n", __TIME__ ); // 18:20:27
    printf("Line :%d\n", __LINE__ ); // 7
    }
    printf("ANSI :%d\n", __STDC__ ); // 1
    ```
7. 链接多个文件

```bash
gcc main.c max.c avg.c
```

或者：

```bash
# 只编译不链接
gcc -c main.c && gcc -c max.c && gcc -c avg.c
# 链接
gcc main.o max.o avg.o
```
8. 生成可执行文件的过程

![alt text](image.png)

# Programming at the Kernel Level
