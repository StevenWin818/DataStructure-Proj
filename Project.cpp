#include <bits/stdc++.h>
// ??????
typedef struct Node
{
    int id;             // ??
    char name[50];      // ??
    char gender[10];    // ??
    double temperature; // ??
    int hour;           // ???????????
    int minute;         // ???????????
    struct Node *next;  // ??????????
} Node;

// ????
typedef struct LinkedList
{
    Node *head; // ??????
    int size;   // ??????????
} LinkedList;

// ?????
LinkedList *init_list()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        printf("??????????????\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// ??????
void add(LinkedList *list)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("??????\n");
        return;
    }
    printf("??????");
    scanf("%d", &(new_node->id));
    printf("??????");
    scanf("%s", new_node->name);
    printf("??????");
    scanf("%s", new_node->gender);
    do
    {
        printf("??????");
        scanf("%lf", &(new_node->temperature));
        if (new_node->temperature < 35 || new_node->temperature > 42)
            printf("??????????35-42?????\n");
    } while (new_node->temperature < 35 || new_node->temperature > 42);


    do{
        printf("???????????????");
        scanf("%d", &(new_node->hour));
        if (new_node->hour < 0 || new_node->hour > 23)
            printf("?????????????0-23?????\n");
    } while(new_node->hour < 0 || new_node->hour > 23);

    do
    {
        printf("???????????????");
        scanf("%d", &(new_node->minute));
        if (new_node->minute < 0 || new_node->minute >= 60)
            printf("?????????????0-59?????\n");
    } while (new_node->minute < 0 || new_node->minute >= 60);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// ????????
void print(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("???%d\n", current->id);
        printf("???%s\n", current->name);
        printf("???%s\n", current->gender);
        printf("???%.1f\n", current->temperature);
        printf("?????????%02d:%02d\n", current->hour, current->minute);
        printf("--------------------\n");
        current = current->next;
    }
}

//????
// ??????
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
// ????
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
// ??????
Node *mergeSort(Node *head)
{
    if (head == NULL || head->next == NULL)    return head;
    Node *mid = split(head);
    return merge(mergeSort(head), mergeSort(mid));
}
void sort(LinkedList *list)
{
    list->head = mergeSort(list->head);
    printf("???,????\n");
    print(list);
}


// ??????37??????
void statistics(LinkedList *list)
{
    Node *current = list->head;
    int count = 0;
    printf("???????37?????????\n");
    while (current != NULL)
    {
        if (current->temperature >= 37.0)
        {
            count++;
            printf("???%d\n", current->id);
            printf("???%s\n", current->name);
            printf("???%s\n", current->gender);
            printf("???%.1f\n", current->temperature);
            printf("?????????%02d:%02d\n", current->hour, current->minute);
            printf("--------------------\n");
        }
        current = current->next;
    }
    printf("???????37???????%d\n", count);
}

// ???????
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

// ???????
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
            printf("??????\n");
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


// ????
void menu()
{
    printf("+++++++++++++++++++++++++++++++\n");
    printf("+------?????????-----+\n");
    printf("+--1.??????-------------+\n");
    printf("+--2.????????---------+\n");
    printf("+--3.?????---------------+\n");
    printf("+--4.????????---------+\n");
    printf("+--5.??????37???-----+\n");
    printf("+--6.??????-------------+\n");
    printf("+--7.????-----------------+\n");
    printf("+++++++++++++++++++++++++++++++\n");
}
Node *search(LinkedList *list, const char *key)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->name, key) == 0 || current->id == atoi(key))
        {
            printf("?????????\n");
            printf("???%d\n", current->id);
            printf("???%s\n", current->name);
            printf("???%s\n", current->gender);
            printf("???%.1f\n", current->temperature);
            printf("?????????%02d:%02d\n", current->hour, current->minute);
            return current;
        }
        current = current->next;
    }
    printf("????????? %s ???\n", key);
    return NULL;
}

// ??delete??
void dele(LinkedList *list, const char *key)
{
    Node *student_to_delete = search(list, key);
    if (student_to_delete == NULL)
        return;
    // ????
    printf("???????????(y/n): ");
    char confirm[2];
    scanf("%1s", confirm);
    if (confirm[0] == 'y' || confirm[0] == 'Y')
    {
        Node *current = list->head;
        Node *prev = NULL;
        while (current != student_to_delete)
        {
            prev = current;
            current = current->next;
        }
        if (prev == NULL)
            list->head = current->next;
        else
            prev->next = current->next;
        list->size--;
        printf("???????\n");
    }
    else
        printf("??????\n");
}

// ???
int main()
{
    LinkedList *list = init_list();
    load(list);
    while (1)
    {
        menu();
        int choice;
        printf("????????");
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
           {
            printf("????????????????");
            char key[20];
            scanf("%s", key);
            search(list, key);
            break;
            }
        case 4:
            print(list);
            break;
        case 5:
            statistics(list);
            break;
        case 6:
            printf("????????????????");
            char key[20];
            scanf("%s", key);
            dele(list, key);
            break;
        case 7:
            save(list);
            printf("????\n");
            return 0;
        default:
            printf("???????????\n");
        }
        save(list);
        printf("\n???????...\n");
        getchar();       
        getchar();       
        system("cls"); 
    }
    return 0;
}
