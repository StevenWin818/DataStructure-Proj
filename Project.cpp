#include <bits/stdc++.h>
// ��������ڵ�
typedef struct Node
{
    int id;             // ѧ��
    char name[50];      // ����
    char gender[10];    // �Ա�
    double temperature; // ����
    int hour;           // ����ͼ��ݵ�ʱ�䣨ʱ��
    int minute;         // ����ͼ��ݵ�ʱ�䣨�֣�
    struct Node *next;  // ָ����һ���ڵ��ָ��
} Node;

// ��������
typedef struct LinkedList
{
    Node *head; // �����ͷ�ڵ�
    int size;   // ����Ĵ�С���ڵ�����
} LinkedList;

// ��ʼ������
LinkedList *init_list()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        printf("�ڴ����ʧ�ܣ��޷���ʼ������\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// ���ѧ����Ϣ
void add(LinkedList *list)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("�ڴ����ʧ�ܡ�\n");
        return;
    }
    printf("������ѧ�ţ�");
    scanf("%d", &(new_node->id));
    printf("������������");
    scanf("%s", new_node->name);
    printf("�������Ա�");
    scanf("%s", new_node->gender);
    do
    {
        printf("���������£�");
        scanf("%lf", &(new_node->temperature));
        if (new_node->temperature < 35 || new_node->temperature > 42)
            printf("���������쳣��������35-42֮������¡�\n");
    } while (new_node->temperature < 35 || new_node->temperature > 42);


    do{
        printf("���������ͼ��ݵ�ʱ�䣨ʱ����");
        scanf("%d", &(new_node->hour));
        if (new_node->hour < 0 || new_node->hour > 23)
            printf("ʱ�䣨ʱ�������쳣��������0-23֮���ʱ�䡣\n");
    } while(new_node->hour < 0 || new_node->hour > 23);

    do
    {
        printf("���������ͼ��ݵ�ʱ�䣨�֣���");
        scanf("%d", &(new_node->minute));
        if (new_node->minute < 0 || new_node->minute >= 60)
            printf("ʱ�䣨�֣������쳣��������0-59֮���ʱ�䡣\n");
    } while (new_node->minute < 0 || new_node->minute >= 60);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

//�������
// ����ָ��
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
// �鲢����
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
// �鲢������
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

// ����ѧ��
Node *search(LinkedList *list, int id)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            printf("ѧ�ţ�%d\n", current->id);
            printf("������%s\n", current->name);
            printf("�Ա�%s\n", current->gender);
            printf("���£�%.1f\n", current->temperature);
            printf("����ͼ��ݵ�ʱ�䣺%02d:%02d\n", current->hour, current->minute);
            printf("--------------------\n");
            return current;
        }
        current = current->next;
    }
    printf("δ�ҵ�ѧ��Ϊ%d��ѧ����\n", id);
    return NULL;
}

// ɾ��ѧ����Ϣ
void dele(LinkedList *list, int id)
{
    Node *to_delete = search(list, id);
    if (to_delete == NULL)    return;
    
    printf("ȷ��Ҫɾ��ѧ��Ϊ%d��ѧ����(y/n)\n", id);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y')
    {
        printf("ȡ��ɾ����\n");
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
    printf("ѧ��Ϊ%d��ѧ���ѱ�ɾ����\n", id);
}

// ͳ�����¸���37�ȵ�ѧ������
void statistics(LinkedList *list)
{
    Node *current = list->head;
    int count = 0;
    printf("���¸��ڻ����37�ȵ�ѧ����Ϣ���£�\n");
    while (current != NULL)
    {
        if (current->temperature >= 37.0)
        {
            count++;
            printf("ѧ�ţ�%d\n", current->id);
            printf("������%s\n", current->name);
            printf("�Ա�%s\n", current->gender);
            printf("���£�%.1f\n", current->temperature);
            printf("����ͼ��ݵ�ʱ�䣺%02d:%02d\n", current->hour, current->minute);
            printf("--------------------\n");
        }
        current = current->next;
    }
    printf("���¸��ڻ����37�ȵ�ѧ��������%d\n", count);
}

// ���������ļ�
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

// ���ļ���������
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
            printf("�ڴ����ʧ�ܡ�\n");
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

// ��ӡȫ��ѧ����Ϣ
void print(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("ѧ�ţ�%d\n", current->id);
        printf("������%s\n", current->name);
        printf("�Ա�%s\n", current->gender);
        printf("���£�%.1f\n", current->temperature);
        printf("����ͼ��ݵ�ʱ�䣺%02d:%02d\n", current->hour, current->minute);
        printf("--------------------\n");
        current = current->next;
    }
}

// Ŀ¼����
void menu()
{
    printf("+++++++++++++++++++++++++++++++\n");
    printf("+------ͼ�����Ա����ϵͳ-----+\n");
    printf("+--1.���ѧ����Ϣ-------------+\n");
    printf("+--2.�����¶�ѧ������---------+\n");
    printf("+--3.��ѧ������---------------+\n");
    printf("+--4.��ӡȫ��ѧ����Ϣ---------+\n");
    printf("+--5.ɸѡ���¸���37��ѧ��-----+\n");
    printf("+--6.ɾ��ָ��ѧ��-------------+\n");
    printf("+--7.�˳�����-----------------+\n");
    printf("+++++++++++++++++++++++++++++++\n");
}

// ������
int main()
{
    LinkedList *list = init_list();
    load(list);
    while (1)
    {
        menu();
        int choice;
        printf("���������ѡ��");
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
            printf("������Ҫ���ҵ�ѧ����ѧ�ţ�");
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
            printf("������Ҫɾ����ѧ����ѧ�ţ�");
            scanf("%d", &id);
            dele(list, id);
            break;
        case 7:
            save(list);
            printf("�˳�����\n");
            return 0;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }
        save(list);
        printf("\n���س����Լ���...\n");
        getchar();       
        getchar();       
        system("cls"); 
    }
    return 0;
}
