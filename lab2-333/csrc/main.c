#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUMBERS 100

// 定义节点结构
typedef struct Node {
    float value; // 节点存储的值
    struct Node* next; // 指向下一个节点的指针
} Node;

// 生成随机浮点数
float generate_random() {
    return (float)(rand() % 2001 - 1000) / 10.0; // 生成范围在 -100.0 到 100.0 的随机浮点数
}

// 插入节点到链表头部
void insert_node(Node** h, Node** t, float value) {
    // 创建一个新节点
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = value;
    temp->next = NULL;

    // 如果链表为空
    if (*h == NULL) {
        *h = temp;
        *t = temp;
    } else {
        // 链表不为空，将新节点插入到头部
        temp->next = *h;
        *h = temp;
    }
}

// 打印链表并写入文件或标准输出
void fprint_list(Node* h, const char* filename) {
    FILE* output;
    if (filename != NULL) {
        output = fopen(filename, "w");
        if (output == NULL) {
            perror("Failed to create file");
            exit(EXIT_FAILURE);
        }
    } else {
        output = stdout;
    }

    if (h == NULL) {
        fprintf(output, "The list is empty.\n");
    } else {
        fprintf(output, "Values in the list are:\n");
        Node* current = h;
        while (current != NULL) {
            fprintf(output, "[%.2f], ", current->value);
            current = current->next;
        }
        fprintf(output, "\n");
    }

    if (filename != NULL) {
        fclose(output);
    }
}

// 释放链表内存
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_positive> <file_ext>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 解析命令行参数
    unsigned int num_positive = atoi(argv[1]);
    char file_ext[100];
    strcpy(file_ext, argv[2]);

    // 初始化随机数生成器
    srand((unsigned int)time(NULL));

    // 初始化链表指针
    Node* pos = NULL;
    Node* pos_tail = NULL;
    Node* pos_frac = NULL;
    Node* pos_frac_tail = NULL;
    Node* neg = NULL;
    Node* neg_tail = NULL;
    Node* neg_frac = NULL;
    Node* neg_frac_tail = NULL;

    unsigned int count = 0;
    while (count < num_positive) {
        float random_value = generate_random();
        if (random_value >= 1.0) {
            insert_node(&pos, &pos_tail, random_value);
            count++;
        } else if (random_value > 0.0 && random_value < 1.0) {
            insert_node(&pos_frac, &pos_frac_tail, random_value);
        } else if (random_value > -1.0 && random_value < 0.0) {
            insert_node(&neg, &neg_tail, random_value);
        } else if (random_value <= -1.0) {
            insert_node(&neg_frac, &neg_frac_tail, random_value);
        } else {
            fprintf(stderr, "Unexpected value generated: %.2f\n", random_value);
            return EXIT_FAILURE;
        }
    }

    // 打印并保存链表
    fprint_list(pos, strcat(strcpy((char[100]){}, "pos."), file_ext));
    fprint_list(pos_frac, strcat(strcpy((char[100]){}, "pos_frac."), file_ext));
    fprint_list(neg, strcat(strcpy((char[100]){}, "neg."), file_ext));
    fprint_list(neg_frac, strcat(strcpy((char[100]){}, "neg_frac."), file_ext));

    // 释放链表内存
    free_list(pos);
    free_list(pos_frac);
    free_list(neg);
    free_list(neg_frac);

    return EXIT_SUCCESS;
}
