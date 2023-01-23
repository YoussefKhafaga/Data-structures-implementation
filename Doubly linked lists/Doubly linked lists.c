#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} DoublyLinkedList;

DoublyLinkedList* init()
{
    DoublyLinkedList *list =malloc(sizeof(DoublyLinkedList));
    list->head=NULL;
    list->tail=NULL;
}
size_t length(DoublyLinkedList*  list)
{
    size_t count = 0;
    Node *temp;
    temp=list->head;
    while(temp)
    {
        temp=temp->next;
        count++;
    }
    return count;
}
Node* newNode(int value)
{
    Node *n=malloc(sizeof(Node));
    n->data=value;
    n->next=NULL;
    n->prev=NULL;
    return n;
}
/*void addFront(Node node , int value)
{
    Node*n=newNode(value);
    if(node)
    {
        node->prev=n;
    }
    n->next=node;
    return n;
}*/
void addFront(DoublyLinkedList *list,Node *n)
{
    if(!list->head)
    {
        list->head=list->tail=n;
    }
    else{
    n->next=list->head;
    list->head->prev=n;
    list->head=n;
    }
}
void addEnd(DoublyLinkedList *list , Node *n)
{

        if(!list->tail)
    {
        list->head=list->tail=n;
    }
    else{
        n->prev=list->tail;
        list->tail->next=n;
        list->tail=n;
        }
}
DoublyLinkedList* convertArrayToDoublyLinkedList(int array[], int size)
{
    int i;
    DoublyLinkedList *list = init();
    for(i=0;i<size;i++)
    {
        Node *n=newNode(array[i]);
        addEnd(list,n);
    }
    return list;
}
void destroy(DoublyLinkedList* list)
{
    Node *n;
    n=list->head;
    while(n)
    {
        list->head=list->head->next;
        free(n);
        n=list->head;
    }
   // free(list);
}
DoublyLinkedList* copy(DoublyLinkedList* list)
{
    DoublyLinkedList *newlist = init();
    Node *n;
    n=list->head;
    while(n){
        addEnd(newlist,newNode(n->data));
        n=n->next;
                     }
    return newlist;
}

void concatenate(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
   Node *n=list2->head;
        while(n){
        addEnd(list1,n);
        n=n->next;
    }

}
DoublyLinkedList* getDifferenceBetweenLists(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    DoublyLinkedList *newlist = init();
    Node *temp1=list1->head;
    Node *temp2=list2->head;
    while(temp1)
    {
        printf(" %d %d \n",temp1->data,temp2->data);
        if(temp1->data!=temp2->data)
        {
            addEnd(newlist,temp1);
            temp1=temp1->next;
        }
        else if(temp1->data==temp2->data)
        {
            temp1=temp1->next;
            if(temp2->next!=NULL){
                temp2=temp2->next;}
        }
    }
    return newlist;
}
int checkSumofFirstHalfEqualSumOfSecondHalf(DoublyLinkedList*  list)
{
    if (length(list)%2!=0) return 0;
    int i,sum1=0,sum2=0;
    Node *temp1,*temp2;
    temp1=list->head;
    temp2=list->tail;
    for(i=0;i<length(list)/2;i++)
    {
        sum1=sum1+temp1->data;
        sum2=sum2+temp2->data;
        temp1=temp1->next;
        temp2=temp2->prev;
    }
    if(sum1==sum2)
    return 1;
    else return 0;
}
int isPalindrome(DoublyLinkedList * list)
{
    int flag=1;
    Node *temp1,*temp2;
    temp1=list->head;
    temp2=list->tail;
    if(length(list)%2==0||length(list)==3) flag=0;
    else
    {
    while(temp1->next!=temp2->prev)
    {
        if(temp1->data==temp2->data){
        temp1=temp1->next;
        temp2=temp2->prev;}
        else {
            flag=0;
        break;
        }
    }
    }
    return flag;
}
int areEqual(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    int flag=1;
    Node *temp1,*temp2;
    temp1=list1->head;
    temp2=list2->head;
    if(length(list1)==length(list2)){
    while(temp1&&temp2)
    {
    if(temp1->data==temp2->data)
    {
        temp1=temp1->next;
        temp2=temp2->next;
    }
    else flag=0;
    }
    }
    else flag=0;
    return flag;
}

void printlnListForward(DoublyLinkedList * list)
{
    Node *temp;
    temp=list->head;
    while(temp)
    {
        printf("[%d]",temp->data);
        temp=temp->next;
    }
    printf("\n");
}
void printlnListBackward(DoublyLinkedList * list)
{
    if(!list->head) {printf("\n");return;}
    Node *temp;
    temp=list->tail;
    while(temp)
    {
        printf("[%d]",temp->data);
        temp=temp->prev;
    }
    printf("\n");
}
void Investigate(char* title, DoublyLinkedList * list)
{
    printf("%s\n", title);
    printf("List =         ");
    printlnListForward(list);
    printf("Reverse List = ");
    printlnListBackward(list);
    printf("List Length = %u\n", length(list));
    printf("List isPalindrome = %d\n", isPalindrome(list));
    printf("...................................................\n");
}

void testConcatenate1(DoublyLinkedList *list1)
{
    puts("\nSTART testConcatenate1\n");
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList* list3,*emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", EmptyList);
    concatenate(list3, emptyList1);
    Investigate("List3<->EmptyList1\n==========================", list3);
    destroy(list3);
    Investigate("List3 (after destroy)\n=====================", list3);
    destroy(emptyList1);
    puts("\nEND testConcatenate1\n");
}

void testConcatenate2(DoublyLinkedList * list1)
{
    puts("\nSTART testConcatenate2\n");
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList * list3, * emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", EmptyList);
    concatenate(emptyList1, list3);
    Investigate("EmptyList1<->List3\n==========================", emptyList1);
    destroy(emptyList1);
    Investigate("EmptyList1 (after destroy)\n=====================", emptyList1);
    puts("\nEND testConcatenate2\n");
}
void testConcatenate3(DoublyLinkedList *list1, DoublyLinkedList *list2)
{
    puts("\nSTART testConcatenate3\n");
    DoublyLinkedList* list3, *list4,* emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    list4 = copy(list2);
    Investigate("list4 = copy(List2)\n==================", list4);
    concatenate(list3, list4);
    Investigate("List3<->List4\n=====================", list3);
    destroy(list3);
    Investigate("list3 (after destroy)\n=====================", list3);
    puts("\nEND testConcatenate3\n");

}

void testConcatenate()
{
    int array1[] = {0, 1, 2, 3, 4, 5, 6};
    int array2[] = {7, 8, 9};

    DoublyLinkedList *list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
    Investigate("List1\n=====", list1);
    DoublyLinkedList *list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
    Investigate("List2\n=====", list2);

    testConcatenate1(list1);
    testConcatenate2(list1);
    testConcatenate3(list1, list2);

    destroy(list1);
    destroy(list2);
}

void testPalindrome()
{
    puts("\nSTART testPalindrome\n");
    int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array4[] = {7, 8, 9, 9, 8, 7};

    DoublyLinkedList* list5 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
    Investigate("List5\n=====", list5);
    DoublyLinkedList *list6 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
    Investigate("List6\n=====", list6);

    destroy(list5);
    destroy(list6);
    puts("\nEND testPalindrome\n");

}

void testAreEqual()
{
    puts("\nSTART testAreEqual\n");
    int array7[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array8[] = {7, 8, 9, 9, 8, 7};
    int array9[] = {0, 1, 2, 3, 4, 5};
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList *list7 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("List7\n=====", list7);
    DoublyLinkedList *list8 = convertArrayToDoublyLinkedList(array8, sizeof(array8)/sizeof(*array8));
    Investigate("List8\n=====", list8);
    DoublyLinkedList *list9 = convertArrayToDoublyLinkedList(array9, sizeof(array9)/sizeof(*array9));
    Investigate("List9\n=====", list9);
    DoublyLinkedList *emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList *emptyList2 = copy(EmptyList);
    Investigate("EmptyList2 = copy(EmptyList)\n===========================", emptyList2);

    printf("areEqual(list7, list7) = %d\n", areEqual(list7, list7));
    printf("areEqual(list7, list8) = %d\n", areEqual(list7, list8));
    printf("areEqual(list7, list9) = %d\n", areEqual(list7, list9));
    printf("areEqual(list8, list7) = %d\n", areEqual(list8, list7));
    printf("areEqual(list7, EmptyList1) = %d\n", areEqual(list7, emptyList1));
    printf("areEqual(EmptyList1, list7) = %d\n", areEqual(emptyList1, list7));
    printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

    destroy(list7);
    destroy(list8);
    destroy(list9);
    puts("\nEND testAreEqual\n");

}

void testDifference()
{
    puts("\nSTART testDifference\n");
    int array10[] = {2, 4, 8,9,13,17,20};
    int array11[] = {2, 8, 17,20};
    DoublyLinkedList *list10 = convertArrayToDoublyLinkedList(array10, sizeof(array10)/sizeof(*array10));
    Investigate("list10\n=====", list10);
    DoublyLinkedList *list11 =convertArrayToDoublyLinkedList(array11, sizeof(array11)/sizeof(*array11));
    Investigate("List11\n=====", list11);
    DoublyLinkedList *list12 = getDifferenceBetweenLists(list10,list11);
    Investigate("list12\n=====", list12);
    destroy(list10);
    destroy(list11);
    destroy(list12);
    puts("\nEND testDifference\n");

}
void testSum()
{
    puts("\nSTART testSum\n");
    int array5[] = {12, 4, 8, 9, 13, 2};
    int array6[] = {2, 18, 17,4};
    int array7[]= {2,3,4};
    DoublyLinkedList *list13 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
    Investigate("list13\n=====", list13);
    DoublyLinkedList *list14 =convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
    Investigate("list14\n=====", list14);
    DoublyLinkedList *list15 =convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("list15\n=====", list15);
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list13) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list13));
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list14) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list14));
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list15) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list15));
    destroy(list13);
    destroy(list14);
    destroy(list15);
    puts("\nEND testSum\n");
}
int main()
{
    testConcatenate();
    testPalindrome();
    testAreEqual();
    testDifference();
    testSum();
    return 0;
}
