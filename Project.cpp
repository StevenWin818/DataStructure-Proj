#include <bits/stdc++.h>
// 定义链表节点
typedef struct Node
{
    int id;             // 学号
    char name[50];      // 姓名
    char gender[10];    // 性别
    double temperature; // 体温
    int hour;           // 进入图书馆的时间（时）
    int minute;         // 进入图书馆的时间（分）
    struct Node *next;  // 指向下一个节点的指针
} Node;

// 定义链表
typedef struct LinkedList
{
    Node *head; // 链表的头节点
    int size;   // 链表的大小（节点数）
} LinkedList;

// 初始化链表
LinkedList *init_list()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        printf("内存分配失败，无法初始化链表。\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// 添加学生信息
void add(LinkedList *list)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("内存分配失败。\n");
        return;
    }
    printf("请输入学号：");
    scanf("%d", &(new_node->id));
    printf("请输入姓名：");
    scanf("%s", new_node->name);
    printf("请输入性别：");
    scanf("%s", new_node->gender);
    do
    {
        printf("请输入体温：");
        scanf("%lf", &(new_node->temperature));
        if (new_node->temperature < 35 || new_node->temperature > 42)
            printf("体温输入异常，请输入35-42之间的体温。\n");
    } while (new_node->temperature < 35 || new_node->temperature > 42);


    do{
        printf("请输入进入图书馆的时间（时）：");
        scanf("%d", &(new_node->hour));
        if (new_node->hour < 0 || new_node->hour > 23)
            printf("时间（时）输入异常，请输入0-23之间的时间。\n");
    } while(new_node->hour < 0 || new_node->hour > 23);

    do
    {
        printf("请输入进入图书馆的时间（分）：");
        scanf("%d", &(new_node->minute));
        if (new_node->minute < 0 || new_node->minute >= 60)
            printf("时间（分）输入异常，请输入0-59之间的时间。\n");
    } while (new_node->minute < 0 || new_node->minute >= 60);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

//排序操作
// 链表分割函数
Node *split(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}
// 归并排序
Node *merge(Node *l1, Node *l2)
{
    Node dummy;
    Node *tail = &dummy;
    while (l1 && l2)
    {
        if (l1->temperature > l2->temperature)
        {
            tail->next = l1;
            l1 = l1->next;
        }
        else
        {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
// 归并排序函数
Node *mergeSort(Node *head)
{
    if (head == NULL || head->next == NULL)    return head;
    Node *mid = split(head);
    return merge(mergeSort(head), mergeSort(mid));
}
void sort(LinkedList *list)
{
    list->head = mergeSort(list->head);
}

// 查找学生
Node *search(LinkedList *list, int id)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            printf("学号：%d\n", current->id);
            printf("姓名：%s\n", current->name);
            printf("性别：%s\n", current->gender);
            printf("体温：%.1f\n", current->temperature);
            printf("进入图书馆的时间：%02d:%02d\n", current->hour, current->minute);
            printf("--------------------\n");
            return current;
        }
        current = current->next;
    }
    printf("未找到学号为%d的学生。\n", id);
    return NULL;
}

// 删除学生信息
void dele(LinkedList *list, int id)
{
    Node *to_delete = search(list, id);
    if (to_delete == NULL)    return;
    
    printf("确定要删除学号为%d的学生吗？(y/n)\n", id);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y')
    {
        printf("取消删除。\n");
        return;
    }
    if (list->head == to_delete)
        list->head = to_delete->next;
    else
    {
        Node *prev = list->head;
        while (prev->next != to_delete)
            prev = prev->next;
        prev->next = to_delete->next;
    }
    free(to_delete);
    printf("学号为%d的学生已被删除。\n", id);
}

// 统计体温高于37度的学生人数
void statistics(LinkedList *list)
{
    Node *current = list->head;
    int count = 0;
    printf("体温高于或等于37度的学生信息如下：\n");
    while (current != NULL)
    {
        if (current->temperature >= 37.0)
        {
            count++;
            printf("学号：%d\n", current->id);
            printf("姓名：%s\n", current->name);
            printf("性别：%s\n", current->gender);
            printf("体温：%.1f\n", current->temperature);
            printf("进入图书馆的时间：%02d:%02d\n", current->hour, current->minute);
            printf("--------------------\n");
        }
        current = current->next;
    }
    printf("体温高于或等于37度的学生人数：%d\n", count);
}

// 保存链表到文件
void save(LinkedList *list)
{
    FILE *file = fopen("data.txt", "w");
    if (file == NULL)    return;
    Node *current = list->head;
    while (current != NULL)
    {
        fprintf(file, "%d %s %s %.1f %d %d\n", current->id, current->name, current->gender, current->temperature, current->hour, current->minute);
        current = current->next;
    }
    fclose(file);
}

// 从文件加载链表
void load(LinkedList *list)
{
    FILE *file = fopen("data.txt", "r");
    if (file == NULL)    return;
    Node *current = list->head;
    while (!feof(file))
    {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL)
        {
            printf("内存分配失败。\n");
            return;
        }
        fscanf(file, "%d %s %s %lf %d %d\n", &(new_node->id), new_node->name, new_node->gender, &(new_node->temperature), &(new_node->hour), &(new_node->minute));
        new_node->next = NULL;
        if (current == NULL)    list->head = new_node;
        else    current->next = new_node;
        current = new_node;
    }
    fclose(file);
}

// 打印全部学生信息
void print(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("学号：%d\n", current->id);
        printf("姓名：%s\n", current->name);
        printf("性别：%s\n", current->gender);
        printf("体温：%.1f\n", current->temperature);
        printf("进入图书馆的时间：%02d:%02d\n", current->hour, current->minute);
        printf("--------------------\n");
        current = current->next;
    }
}

// 目录函数
void menu()
{
    printf("+++++++++++++++++++++++++++++++\n");
    printf("+------图书馆人员管理系统-----+\n");
    printf("+--1.添加学生信息-------------+\n");
    printf("+--2.按体温对学生排序---------+\n");
    printf("+--3.对学生查找---------------+\n");
    printf("+--4.打印全部学生信息---------+\n");
    printf("+--5.筛选体温高于37的学生-----+\n");
    printf("+--6.删除指定学生-------------+\n");
    printf("+--7.退出程序-----------------+\n");
    printf("+++++++++++++++++++++++++++++++\n");
}

// 主函数
int main()
{
    LinkedList *list = init_list();
    load(list);
    while (1)
    {
        menu();
        int choice;
        printf("请输入你的选择：");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add(list);
            break;
        case 2:
            sort(list);
            break;
        case 3:
            printf("请输入要查找的学生的学号：");
            int id;
            scanf("%d", &id);
            search(list, id);
            break;
        case 4:
            print(list);
            break;
        case 5:
            statistics(list);
            break;
        case 6:
            printf("请输入要删除的学生的学号：");
            scanf("%d", &id);
            dele(list, id);
            break;
        case 7:
            save(list);
            printf("退出程序。\n");
            return 0;
        default:
            printf("无效的选择，请重新输入。\n");
        }
        save(list);
        printf("\n按回车键以继续...\n");
        getchar();       
        getchar();       
        system("cls"); 
    }
    return 0;
}
