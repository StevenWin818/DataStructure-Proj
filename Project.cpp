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
    // TODO: 从键盘输入学生信息，创建新的节点，添加到链表中
}

// 按体温排序
void sort(LinkedList *list)
{
    // TODO: 使用适当的排序算法（如冒泡排序、快速排序等）对链表进行排序
}

// 查找学生
Node *search(LinkedList *list, int id)
{
    // TODO: 使用二分查找法按照学号进行查找
}

// 统计体温高于37度的学生人数
void statistics(LinkedList *list)
{
    // TODO: 遍历链表，统计体温高于或等于37度的学生人数
}

// 保存链表到文件
void save(LinkedList *list)
{
    // TODO: 将链表的内容保存到data.txt文件中
}

// 从文件加载链表
void load(LinkedList *list)
{
    // TODO: 从data.txt文件中读取内容，加载到链表中
}

// 删除学生信息
void dele(LinkedList *list, int id)
{
    // TODO: 调用search函数查找学生信息，然后删除该节点
}

// 打印所有学生信息
void print(LinkedList *list)
{
    // TODO: 遍历链表，打印每个节点的信息
}

// 主函数
int main()
{
    LinkedList *list = init_list();
    // TODO: 加载文件，调用目录，实现每项功能
    return 0;
}
