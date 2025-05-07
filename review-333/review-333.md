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

1. `man`：1 - 用户命令；2 - 系统调用；3 - C 标准库函数
2. `void perror(const char *buffer)`：打印错误信息，buffer 是错误信息的前缀。
    ```c
    if ((fd = open("/home/username/nofile",O_RDONLY)) == -1) {
        perror("Error");
        // Error: open: No such file or directory
        exit(1);
    }
    ```

# Files in POSIX

1. 文件权限

![alt text](image-1.png)

2. 传入结构体指针的函数的要求

```c
struct stat buf;  // 在栈上分配内存 
stat(fname, &buf);
```

```c
struct stat *buf;
stat(fname, buf);  // 错误，buf 没有分配内存
buf = malloc(sizeof(struct stat));  // 分配内存后调用 stat
```

POSIX API：

### 文件操作相关
- **`int open(const char *pathname, int oflag);`**
  - **解释**：打开或创建一个文件。`pathname` 是文件路径，`oflag` 是打开文件的方式（read only `O_RDONLY`；write only `O_WRONLY`；read/write `O_RDWR`）。返回文件描述符，若失败返回 -1。
- **`int open(const char *pathname, int oflag, mode_t mode);`**
  - **解释**：与上一个函数类似，但当创建文件时，`mode` 参数用于指定文件的权限。返回文件描述符，若失败返回 -1。
- **`int close(int fd);`**
  - **解释**：关闭一个已打开的文件描述符 `fd`。成功返回 0，失败返回 -1。
- **`int dup(int fd);`**
  - **解释**：复制文件描述符 `fd`，返回一个新的文件描述符，该新描述符与原描述符共享同一个文件。

### 文件读写相关
- **`ssize_t read(int fd, void *buf, size_t n);`**
  - **解释**：从文件描述符 `fd` 指向的文件中读取最多 `n` 个字节到缓冲区 `buf`。返回实际读取的字节数，若到达文件末尾返回 0，失败返回 -1。
- **`ssize_t write(int fd, void *buf, size_t n);`**
  - **解释**：将缓冲区 `buf` 中的 `n` 个字节写入文件描述符 `fd` 指向的文件。返回实际写入的字节数，失败返回 -1。

### 文件权限与属性相关
- **`mode_t umask(mode_t mask);`**
  - **解释**：设置文件创建掩码。`mask` 是掩码值，函数返回之前的掩码值。掩码用于限制文件的默认权限。
- **`mode_t chmod(const char *path, mode_t mode);`**
  - **解释**：改变文件 `path` 的权限为 `mode`。成功返回 0，失败返回 -1。
- **`int chown(const char *path, uid_t owner, gid_t group);`**
  - **解释**：改变文件 `path` 的所有者为 `owner`，所属组为 `group`。成功返回 0，失败返回 -1。

### 文件定位相关
- **`off_t lseek(int fd, off_t offset, int flag);`**
  - **解释**：移动文件描述符 `fd` 的读写指针。`offset` 是偏移量，`flag` 指定偏移的基准（如从文件开头、当前位置等）。返回新的偏移量，失败返回 -1。

### 文件状态相关
- **`int stat(const char *path, struct stat *statbuf);`**
  - **解释**：获取文件 `path` 的状态信息，存入 `statbuf` 指向的结构体中。成功返回 0，失败返回 -1。

### 文件链接相关
- **`int link(const char *oldPath, const char *newPath);`**
  - **解释**：创建文件 `oldPath` 的硬链接 `newPath`。成功返回 0，失败返回 -1。
- **`int unlink(const char *pathname);`**
  - **解释**：删除文件 `pathname` 的链接。如果文件没有其他链接，则文件被删除。成功返回 0，失败返回 -1。
- **`int symlink(const char *target, const char *linkpath);`**
  - **解释**：创建符号链接 `linkpath`，指向目标 `target`。成功返回 0，失败返回 -1。

### 目录操作相关
- **`int mkdir(const char *path, mode_t mode);`**
  - **解释**：创建目录 `path`，权限为 `mode`。成功返回 0，失败返回 -1。
- **`int rmdir(const char *path);`**
  - **解释**：删除空目录 `path`。成功返回 0，失败返回 -1。
- **`DIR *opendir(const char *path);`**
  - **解释**：打开目录 `path`，返回目录流指针。失败返回 `NULL`。
- **`int closedir(DIR *dir);`**
  - **解释**：关闭目录流 `dir`。成功返回 0，失败返回 -1。
- **`struct dirent *readdir(DIR *dir);`**
  - **解释**：从目录流 `dir` 中读取下一个目录项，返回目录项指针。若无更多目录项，返回 `NULL`。
- **`void rewinddir(DIR *dir);`**
  - **解释**：将目录流 `dir` 的位置重置到目录的开头。
- **`int chdir(const char *path);`**
  - **解释**：将当前工作目录更改为 `path`。成功返回 0，失败返回 -1。
- **`char *getcwd(char *buf, size_t size);`**
  - **解释**：获取当前工作目录的路径，存入 `buf`，`size` 是缓冲区大小。成功返回 `buf`，失败返回 `NULL`。

# Processes

以下是这些函数的原型和简要解释：

### 用户和进程标识相关
- **`uid_t getuid(void);`**
  - **解释**：获取调用进程的实际用户ID（UID）。返回值为调用进程的实际用户ID。
- **`uid_t geteuid(void);`**
  - **解释**：获取调用进程的有效用户ID（EUID）。返回值为调用进程的有效用户ID。
- **`pid_t getpid(void);`**
  - **解释**：获取调用进程的进程ID（PID）。返回值为调用进程的进程ID。
- **`pid_t getppid(void);`**
  - **解释**：获取调用进程的父进程ID（PPID）。返回值为调用进程的父进程ID。

### 进程控制相关
- **`pid_t fork(void);`**
  - **解释**：创建一个新进程，新进程是调用进程的副本。`fork` 的返回值有三种情况：
    - 在子进程中返回 0。
    - 在父进程中返回子进程的进程ID。
    - 如果出错，返回 -1。
- **`pid_t wait(int *status);`**
  - **解释**：等待任意子进程终止，并获取其状态信息。`status` 是一个指向整型变量的指针，用于存储子进程的退出状态。可能的 `status` 值包括：
    - 子进程正常退出时的状态码。
    - 子进程被信号终止时的信号编号。
    - 子进程是否被暂停或继续运行。
    - 如果 `status` 为 `NULL`，则不获取状态信息。
    - 成功返回子进程的PID，失败返回 -1。
- **`pid_t waitpid(pid_t pid, int *wstatus, int options);`**
  - **解释**：等待指定的子进程终止，并获取其状态信息。`pid` 指定要等待的子进程的PID，`wstatus` 是一个指向整型变量的指针，用于存储子进程的退出状态，`options` 是等待选项，可能的值包括：
    - `WNOHANG`：非阻塞模式，如果子进程尚未终止，立即返回。
    - `WUNTRACED`：报告被暂停的子进程。
    - `WCONTINUED`：报告被继续运行的子进程。
    - 成功返回子进程的PID，失败返回 -1。

### 进程执行相关
- **`int execl(const char *path, const char *arg, ...);`**
  - **解释**：用指定的程序替换调用进程的映像。`path` 是程序路径，`arg` 是程序的参数列表，以 `NULL` 结尾。成功则不会返回，失败返回 -1。
- **`int execv(const char *path, char *const argv[]);`**
  - **解释**：与 `execl` 类似，但参数通过数组 `argv` 传递。`path` 是程序路径，`argv` 是参数数组，以 `NULL` 结尾。成功则不会返回，失败返回 -1。
- **`int execlp(const char *file, const char *arg, ...);`**
  - **解释**：与 `execl` 类似，但会在环境变量 `PATH` 中搜索程序。`file` 是程序名，`arg` 是参数列表，以 `NULL` 结尾。成功则不会返回，失败返回 -1。
- **`int execvp(const char *file, char *const argv[]);`**
  - **解释**：与 `execv` 类似，但会在环境变量 `PATH` 中搜索程序。`file` 是程序名，`argv` 是参数数组，以 `NULL` 结尾。成功则不会返回，失败返回 -1。
- **`int execle(const char *path, const char *arg, ..., char *const envp[]);`**
  - **解释**：与 `execl` 类似，但允许指定新的环境变量。`path` 是程序路径，`arg` 是参数列表，`envp` 是环境变量数组，以 `NULL` 结尾。成功则不会返回，失败返回 -1。
- **`int execvpe(const char *file, char *const argv[], char *const envp[]);`**
  - **解释**：与 `execvp` 类似，但允许指定新的环境变量。`file` 是程序名，`argv` 是参数数组，`envp` 是环境变量数组，以 `NULL` 结尾。成功则不会返回，失败返回 -1。

# Pipes and Signals

常见的信号：

![alt text](image-2.png)

以下是这些函数的原型和简要解释：

### 管道和文件描述符操作
- **`int pipe(int filedes[2]);`**
  - **解释**：创建一个管道。`filedes` 是一个包含两个文件描述符的数组，其中 `filedes[0]` 用于读取，`filedes[1]` 用于写入。成功返回 0，失败返回 -1。
- **`int dup2(int fd, int fdnew);`**
  - **解释**：将文件描述符 `fd` 复制到 `fdnew`。如果 `fdnew` 已经打开，则先关闭它。成功返回 `fdnew`，失败返回 -1。
- **`int mkfifo(const char *path, mode_t mode);`**
  - **解释**：创建一个命名管道（FIFO）。`path` 是管道的路径，`mode` 是管道的权限。成功返回 0，失败返回 -1。

### 文件控制操作
- **`int fcntl(int fd, int cmd, ...);`**
  - **解释**：对文件描述符 `fd` 进行控制操作。`cmd` 是命令类型，可能的值包括：
    - `F_DUPFD`：返回一个新的文件描述符，它是 `fd` 的副本，并且大于等于 `arg`。
    - `F_GETFD`：获取文件描述符标志。
    - `F_SETFD`：设置文件描述符标志。
    - `F_GETFL`：获取文件状态标志。
    - `F_SETFL`：设置文件状态标志。
    - 其他命令可能需要额外的参数，具体取决于 `cmd` 的值。成功返回值取决于命令，失败返回 -1。

### 信号处理
- **`int kill(pid_t pid, int signal);`**
  - **解释**：向进程 `pid` 发送信号 `signal`。`pid` 可以是：
    - 大于 0：向进程ID为 `pid` 的进程发送信号。
    - 等于 0：向调用进程所在的进程组发送信号。
    - 等于 -1：向调用进程有权发送信号的所有进程发送信号。
    - 小于 -1：向进程组ID为 `-pid` 的进程组发送信号。
    - 成功返回 0，失败返回 -1。
- **`int raise(int signal);`**
  - **解释**：向调用进程自身发送信号 `signal`。成功返回 0，失败返回 -1。
- **`int sigaction(int signal, const struct sigaction *action, struct sigaction *oldaction);`**
  - **解释**：用于设置和获取信号的处理方式。`signal` 是要处理的信号，`action` 是指向新信号处理方式的指针，`oldaction` 是指向旧信号处理方式的指针（如果需要获取旧的处理方式）。
    - **`struct sigaction`** 结构体的成员包括：
      - `void (*sa_handler)(int)`：信号处理函数指针，用于处理信号。
      - `void (*sa_sigaction)(int, siginfo_t *, void *)`：用于支持实时信号的处理函数指针，可以接收额外的信号信息。
      - `sigset_t sa_mask`：在信号处理函数执行期间需要屏蔽的信号集合。
      - `int sa_flags`：信号处理的标志，可能的值包括：
        - `SA_RESTART`：使被信号中断的系统调用自动重新开始。
        - `SA_NOCLDSTOP`：当子进程停止时，不向父进程发送 `SIGCHLD`。
        - `SA_SIGINFO`：使用 `sa_sigaction` 而不是 `sa_handler`。
        - 其他标志。
      - `void (*sa_restorer)(void)`：已废弃，不应使用。
    - 成功返回 0，失败返回 -1。
