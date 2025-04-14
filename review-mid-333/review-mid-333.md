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

2. `int fclose( FILE *stream );` 成功返回0，失败返回EOF。

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
