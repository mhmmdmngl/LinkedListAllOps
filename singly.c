#include <stdio.h>
#include <malloc.h>

//Our base structure for singly list nodes.
struct node{
    int data;
    //this variable is points next node. Actually most critical thing in singly linked list
    struct node* next;
};

struct node* start = NULL;
struct node* last = NULL;

//This function just generate new node with data and returns it.
struct node* createNewNode(int data)
{
    //This line use malloc function, which generates size for our 'struct node'
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    //We just create a node here, we don't link here with other nodes...
    newNode->next = NULL;
    return newNode;
}

/* ****************  Add Operations  **************** */
//This function adds node to last position of out linked list
void addLast(int data)
{
    struct node* toBeAdd = createNewNode(data);
    //We check if there is none node in our linked list and if its NULL we assing it to start node
    if(start == NULL)
    {
        start = toBeAdd;
    }
    else
    {
        struct node* temp = start;
        //We traverse here to find last position of our linked list.
        //We have to stop if next pointer is NULL.
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = toBeAdd;
    }
}
void betterWayToAddLast(int data)
{
    //this function is a better way to add data to the last position.
    //But if you are computer science student, probably your lecturers want to you code other function
    //Because of traverse operation.
    struct node* toBeAdd = createNewNode(data);
    if(start == NULL)
    {
        start = toBeAdd;
        last = toBeAdd;
    }
    else
    {
        last->next = toBeAdd;
    }
}
void addFirst(int data)
{
    struct node* toBeFirst = createNewNode(data);
    if(start == NULL)
        start = toBeFirst;
    else
    {
        // 10 => 20 => 30 => NULL (Let's add 5 to first position)
        // we have to store 10 to temporary variable, because new start node must point to 10
        struct node* temp = start;
        start = toBeFirst;
        toBeFirst->next = temp;
    }
}
void addAnyWhereBefore(int data, int beforeThisData)
{
    // 10 => 20 => 30 => 40  if we use addAnyWhereBefore(777, 30) our linked List will become
    // 10 => 20 => (777) => 30 => 40
    struct node* toBeAddAnyWhere = createNewNode(data);
    if(start == NULL)
        return;
    // if beforeThisData is start node, our new node must be first node...
    if(start->data == beforeThisData)
    {
        addFirst(data);
        return;
    }
    struct node* temp = start;
    //We have to store node at the temp before of 'beforeThisData'
    // 10 => 20 => 30 => 40  if we use addAnyWhereBefore(777, 30) our temp must be (20) after traverse
    while(temp->next->data != beforeThisData)
    {
        temp = temp->next;
        //we have to check temp variable's next pointer after traverse operation made...
        if(temp->next == NULL)
            break;
    }
    //if temp->next is NULL it means beforeThisData variable don't exists in our list...
    if(temp->next == NULL )
    {
        printf("\nWe couldn't find %d node", beforeThisData);
        return;
    }
    struct node* storeThis = temp->next;
    temp->next = toBeAddAnyWhere;
    toBeAddAnyWhere->next = storeThis;
}
void addAnyWhereAfter(int data, int afterThisData)
{
// 10 => 20 => 30 => 40  if we use addAnyWHereAfter(777, 30) our linked List will become
    // 10 => 20 => 30 => (777) => 40
    struct node* toBeAddAnyWhere = createNewNode(data);
    if(start == NULL)
        return;
    // if beforeThisData is start node, our new node must be first node...
    if(start->data == afterThisData)
    {
        start->next = toBeAddAnyWhere;
        return;
    }
    struct node* temp = start;
    //We have to store node at the temp 'afterThisData'
    // 10 => 20 => 30 => 40  if we use addAnyWHereAfter(777, 30) our temp must be (30) after traverse
    while(temp->data != afterThisData)
    {
        temp = temp->next;
        //we have to check temp variable's next pointer after traverse operation made...
        if(temp->next == NULL)
            break;
    }
    //if temp->next is NULL it means beforeThisData variable don't exists in our list...
    if(temp->next == NULL )
    {
        if(temp->next->data == afterThisData)
        {
            addLast(data);
            return;
        }
        printf("\nWe couldn't find %d node", afterThisData);
        return;
    }
    struct node* storeThis = temp->next;
    temp->next = toBeAddAnyWhere;
    toBeAddAnyWhere->next = storeThis;
}
/* ****************  End of Add Operations  **************** */

/* ****************  Delete Operations  **************** */
void deleteFromLast()
{
    if(start == NULL)
        return;
    struct node* temp = start;
    //why temp->next->next? let's assume we have list like 10 => 20 => 30 => 40
    //if we want to delete 40, we have to make 30 => next to null. it means we have to traverse to 30 not 40!
    while(temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void deleteFirstNode()
{
    if(start == NULL)
        return;
    if(start->next == NULL)
        start = NULL;
    else
    {
        // Let's assume we have list like 10 => 20 => 30 and we want to delete 10
        // if we delete 10, 20 must be become our new start node... otherwise our list will become broken.
        struct node* toBeFirst = start->next;
        free(start);
        start = toBeFirst;
    }
}

void deleteGivenNodeS(int data)
{
    if(start == NULL)
        return;
    if(start->data == data)
        deleteFirstNode();
    struct node* temp = start;
    while(temp != NULL)
    {
        if(temp->next != NULL)
        {
            if(temp->next->data == data)
            {
                struct node* bind = temp->next->next;
                struct node* tobeDeleted = temp->next;
                free(tobeDeleted);
                temp->next = bind;
            }
        }
        else
        {
            if(temp->data == data)
                deleteFromLast();
        }
        temp = temp->next;

    }
}

void reverse()
{
    struct node* prev = NULL;
    struct node* current = start;
    struct node* next = NULL;
    // 10 => 20 => 30 => 40 => NULL
    // in every step, every node's next pointer must point previous node.
    // and we have to update start node and last node...
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    start = prev;
}
//This function just prints our linked list...
void printLinkedList(struct node* first)
{
    struct node* temp = first;
    printf("\n%d",temp->data);
    temp = temp->next;
    while(temp != NULL)
    {
        printf(" => %d", temp->data);
        temp = temp->next;
    }
    printf(" => NULL");
}

void menu()
{
    while(1 == 1)
    {
        int option, data, position;
        printf("\n1-) Add Last");
        printf("\n2-) Add First");
        printf("\n3-) Add Before");
        printf("\n4-) Add After");
        printf("\n5-) Delete Last Node");
        printf("\n6-) Delete First Node");
        printf("\n7-) Delete Given Nodes");
        printf("\n8-) Reverse Linked List");
        printf("\n Select your choise ... ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("enter data for insert last ... ");
                scanf("%d", &data);
                addLast(data);
                printLinkedList(start);
                break;
            case 2:
                printf("enter data for insert first ... ");
                scanf("%d", &data);
                addFirst(data);
                printLinkedList(start);
                break;
            case 3:
                printf("enter data for insert before position... ");
                scanf("%d", &data);
                printf("which node to insert before on");
                scanf("%d", &position);
                addAnyWhereBefore(data, position);
                printLinkedList(start);
                break;
            case 4:
                printf("enter data for insert After position... ");
                scanf("%d", &data);
                printf("which node to insert After on");
                scanf("%d", &position);
                addAnyWhereAfter(data, position);
                printLinkedList(start);
                break;
            case 5:
                deleteFromLast();
                printLinkedList(start);
                break;
            case 6:
                deleteFirstNode();
                printLinkedList(start);
                break;
            case 7:
                printf("Which node data do you want to delete?... ");
                scanf("%d", &data);
                deleteGivenNodeS(data);
                printLinkedList(start);
                break;
            case 8:
                reverse();
                printLinkedList(start);
                break;
        }

    }
}

int main() {
    menu();
}
