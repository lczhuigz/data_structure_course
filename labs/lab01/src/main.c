#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct student {
    char number[14];   // 学号
    char name[20];     // 姓名
    int  sex;          // 0-女，1-男
    char tel[14];      // 手机号
    char qq[12];       // QQ号
    struct student *next;
} Student;

/* ================= 基本工具函数 ================= */

/* 清空输入缓冲区 */
void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* 创建新结点 */
Student* createNode(const char *number, const char *name, int sex,
                    const char *tel, const char *qq) {
    Student *node = (Student*)malloc(sizeof(Student));
    if (node == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }

    strncpy(node->number, number, sizeof(node->number) - 1);
    node->number[sizeof(node->number) - 1] = '\0';

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    node->sex = sex;

    strncpy(node->tel, tel, sizeof(node->tel) - 1);
    node->tel[sizeof(node->tel) - 1] = '\0';

    strncpy(node->qq, qq, sizeof(node->qq) - 1);
    node->qq[sizeof(node->qq) - 1] = '\0';

    node->next = NULL;


    return node;
}

/* ================= 链表初始化 ================= */

/* 只创建一个带头结点的空链表 */
Student* initList(void) {
    Student *head = (Student*)malloc(sizeof(Student));
    if (head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->next = NULL;


    return head;
}

/* 释放整条链表 */
void freeList(Student *head) {
    Student *p = head;
    while (p != NULL) {
        Student *q = p;
        p = p->next;
        free(q);
    }
}

/* ================= 增删改查 ================= */

/* 在指定位置插入学生，pos 从 1 开始；成功返回 1 */
int insertAtPosition(Student *head, int pos,
                     const char *number, const char *name, int sex,
                     const char *tel, const char *qq) {
    if (pos < 1) return 0;

    Student *p = head;
    int i = 0;
    while (p != NULL && i < pos - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL) return 0;   // 位置越界

    Student *node = createNode(number, name, sex, tel, qq);
    node->next = p->next;
    p->next = node;


    return 1;
}

/* 按位置查找，位置从 1 开始 */
Student* getByPosition(Student *head, int pos) {

    if (pos < 1) return NULL;

    Student *p = head->next;
    int i = 1;
    while (p != NULL && i < pos) {
        p = p->next;
        i++;
    }

    return p;
}

/* 尾插，用于初始化时批量添加 */
int appendStudent(Student *head, const char *number, const char *name,
                  int sex, const char *tel, const char *qq) {
    Student *p = head;
    while (p->next != NULL) p = p->next;

    Student *node = createNode(number, name, sex, tel, qq);
    p->next = node;


    return 1;
}

/* 删除指定位置的学生，pos 从 1 开始；成功返回 1 */
int deleteAtPosition(Student *head, int pos) {

    if (pos < 1) return 0;

    Student *p = head;
    int i = 0;
    while (p != NULL && i < pos - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL || p->next == NULL) return 0;

    Student *q = p->next;
    p->next = q->next;
    free(q);


    return 1;
}

/* 修改指定位置的学生信息，pos 从 1 开始；成功返回 1 */
int updateAtPosition(Student *head, int pos,
                     const char *number, const char *name, int sex,
                     const char *tel, const char *qq) {
    Student *p = getByPosition(head, pos);

    if (p == NULL) return 0;

    strncpy(p->number, number, sizeof(p->number) - 1);
    p->number[sizeof(p->number) - 1] = '\0';

    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';

    p->sex = sex;

    strncpy(p->tel, tel, sizeof(p->tel) - 1);
    p->tel[sizeof(p->tel) - 1] = '\0';

    strncpy(p->qq, qq, sizeof(p->qq) - 1);
    p->qq[sizeof(p->qq) - 1] = '\0';


    return 1;
}

/* 按姓名查找，返回结点指针 */
Student* searchByName(Student *head, const char *name) {

    Student *p = head->next;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) return p;
        p = p->next;
    }


    return NULL;
}



/* 统计学生个数 */
int countStudents(Student *head) {

    int count = 0;
    Student *p = head->next;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;
}

/* ================= 显示 ================= */

void printOne(Student *p) {
    printf("%s\t%s\t%s\t%s\t%s\n",
           p->number,
           p->name,
           p->sex == 0 ? "女" : "男",
           p->tel,
           p->qq);
}

void showAll(Student *head) {
    printf("------------------------------------------------------------\n");
    if (head->next == NULL) {
        printf("当前学生表为空。\n");
        printf("------------------------------------------------------------\n");
        return;
    }

    printf("序号\t学号\t姓名\t性别\t手机号\t\tQQ号\n");
    Student *p = head->next;
    int i = 1;
    while (p != NULL) {
        printf("%d\t", i++);
        printOne(p);
        p = p->next;
    }
    printf("------------------------------------------------------------\n");
}

/* ================= 录入工具 ================= */

/* 从键盘读入一条学生信息 */
void inputStudent(char *number, char *name, int *sex,
                  char *tel, char *qq) {
    printf("请输入学号：");
    scanf("%13s", number);

    printf("请输入姓名：");
    scanf("%19s", name);

    printf("请输入性别（0-女，1-男）：");
    scanf("%d", sex);

    printf("请输入手机号：");
    scanf("%13s", tel);

    printf("请输入QQ号：");
    scanf("%11s", qq);

    clearInput();
}

/* ================= 菜单 ================= */

void showMenu(void) {
    printf("\n================ 学生信息管理系统 ================\n");
    printf("  1. 显示所有学生\n");
    printf("  2. 按位置插入学生\n");
    printf("  3. 删除指定位置学生\n");
    printf("  4. 修改指定位置学生\n");
    printf("  5. 按姓名查找学生\n");
    printf("  6. 按位置查找学生\n");
    printf("  7. 统计学生个数\n");
    printf("  0. 退出\n");
    printf("===================================================\n");
    printf("请输入你的选择：");
}

int main(void) {
    /* 1. 初始化空链表 */
    Student *head = initList();

    /* 2. 把原来写死在 initList 里的数据，改为这里调用插入函数添加 */
    appendStudent(head, "2013002", "李思", 0, "1391012197", "88796532");
    appendStudent(head, "2013003", "陈琪", 0, "1378945001", "23789123");
    appendStudent(head, "2013004", "王强", 1, "1363456785", "66543783");
    appendStudent(head, "2013005", "赵括", 1, "1353440897", "656792");
    appendStudent(head, "2013006", "刘刚", 1, "1338654321", "198315");

    printf("已初始化 5 个学生信息：\n");
    showAll(head);

    int choice;
    do{
        showMenu();
        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("输入无效，请重新输入。\n");
            continue;
        }
        clearInput();

        if (choice == 0) {
            printf("退出系统，再见！\n");
            break;
        }

        switch (choice) {
        case 1:
            showAll(head);
            break;

        case 2: {
            int pos;
            char number[14], name[20], tel[14], qq[12];
            int sex;

            printf("请输入插入位置（1 ~ %d）：", countStudents(head) + 1);
            scanf("%d", &pos);
            clearInput();

            inputStudent(number, name, &sex, tel, qq);

            if (insertAtPosition(head, pos, number, name, sex, tel, qq)) {
                printf("插入成功！\n");
                showAll(head);
            } else {
                printf("插入失败：位置越界。\n");
            }
            break;
        }

        case 3: {
            int pos;
            printf("请输入要删除的位置（1 ~ %d）：", countStudents(head));
            scanf("%d", &pos);
            clearInput();

            if (deleteAtPosition(head, pos)) {
                printf("删除成功！\n");
                showAll(head);
            } else {
                printf("删除失败：位置越界。\n");
            }
            break;
        }

        case 4: {
            int pos, sex;
            char number[14], name[20], tel[14], qq[12];

            printf("请输入要修改的位置（1 ~ %d）：", countStudents(head));
            scanf("%d", &pos);
            clearInput();

            if (getByPosition(head, pos) == NULL) {
                printf("修改失败：位置越界。\n");
                break;
            }

            inputStudent(number, name, &sex, tel, qq);

            if (updateAtPosition(head, pos, number, name, sex, tel, qq)) {
                printf("修改成功！\n");
                showAll(head);
            }
            break;
        }

        case 5: {
            char name[20];
            printf("请输入要查找的姓名：");
            scanf("%19s", name);
            clearInput();

            Student *s = searchByName(head, name);
            if (s != NULL) {
                printf("找到学生：\n");
                printf("学号：%s\t姓名：%s\t性别：%s\t手机号：%s\tQQ号：%s\n",
                       s->number, s->name,
                       s->sex == 0 ? "女" : "男",
                       s->tel, s->qq);
            } else {
                printf("未找到姓名为“%s”的学生。\n", name);
            }
            break;
        }

        case 6: {
            int pos;
            printf("请输入要查找的位置（1 ~ %d）：", countStudents(head));
            scanf("%d", &pos);
            clearInput();

            Student *s = getByPosition(head, pos);
            if (s != NULL) {
                printf("学号：%s\t姓名：%s\n", s->number, s->name);
            } else {
                printf("查找失败：位置越界。\n");
            }
            break;
        }

        case 7:
            printf("当前学生总人数：%d\n", countStudents(head));
            break;

        default:
            printf("无效选择，请重新输入。\n");
            break;
        }
    }while(choice != 0);

    freeList(head);


    return 0;
}