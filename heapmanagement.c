// Program to manage a heap and it's malloc and free operations. Use best fit strategy for allocation of memory.

#include <stdio.h>
#include <stdlib.h>

#define MAXMEM 100

typedef struct Node
{
        int offset;
        int mem;
        struct Node* next;
} Node;

Node* mymalloc(int mem, int offset)
{
        Node *ptr;
        ptr = (Node*)malloc(sizeof(Node));
        ptr -> mem = mem;
        ptr -> offset = offset;
        ptr -> next = NULL;
        return ptr;
}

void allocinlist(Node* ptr, Node **alloclist)
{
        Node *temp, *prev = NULL;
        temp = *alloclist;
        while(temp != NULL && ptr -> offset > temp -> offset)
        {
                prev = temp;
                temp = temp -> next;
        }
        if(prev == NULL)
        {
                ptr -> next = *alloclist;
                *alloclist = ptr;
        }
        else
        {
                prev -> next = ptr;
                ptr -> next = temp;
        }
}

void BestFit(Node **alloclist, Node **freelist, int mem)
{
        Node *temp, *ptr, *prev, *tempprev = NULL;
        temp = *freelist;
        int mindiff = -1;
        while(temp != NULL)
        {
                if(temp -> mem - mem >= 0)
                {
                        if(mindiff == -1)
                        {
                                mindiff = temp -> mem - mem;
                                ptr = temp;
                                prev = tempprev;
                        }
                        else if(temp -> mem - mem < mindiff)
                        {
                                mindiff = temp -> mem - mem;
                                ptr = temp;
                                prev = tempprev;
                        }
                }
                tempprev = temp;
                temp = temp -> next;
        }
        if(mindiff == -1)
                printf("Insufficient memory to allocate this data!\n");
        else
        {
                if(mindiff == 0)
                {
                        if(prev == NULL)
                                *freelist = (*freelist) -> next;
                        else
                                prev -> next = ptr -> next;
                }
                else
                {
                        temp = mymalloc(mindiff, ((ptr -> offset) + mem));
                        if(prev == NULL)
                                *freelist = temp;
                        else
                                prev -> next = temp;
                        temp -> next = ptr -> next;
                        ptr -> mem -= mindiff;
                }
                allocinlist(ptr, alloclist);
                printf("Memory allocated successfully\n");
        }
}

void free_up(Node *ptr, Node **freelist)
{
        Node *temp;
        int found = 0;
        if (*freelist == NULL)
        {
                *freelist = ptr;
        }
        else if(ptr -> offset < (*freelist) -> offset)
        {
                ptr -> next = *freelist;
                *freelist = ptr;
        }
        else
        {
                temp = *freelist;
                while(temp -> next != NULL && found == 0)
                {
                        if(temp -> next -> offset > ptr -> offset)
                                found = 1;
                        else
                                temp = temp -> next;
                }
                ptr -> next = temp -> next;
                temp -> next = ptr;
        }
        
}

void mergefree(Node *freelist)
{
        Node *temp, *ptr;
        temp = freelist;
        while(temp -> next != NULL)
        {
                if(temp -> offset + temp -> mem == temp -> next ->offset)
                {
                        ptr = temp -> next;
                        temp -> mem += ptr -> mem;
                        temp -> next = ptr -> next;
                        free(ptr);
                }
                else
                        temp = temp -> next;
        }
}

void traverseAllocList(Node *alloclist)
{
        Node *temp;
        temp = alloclist;
        printf("Allocated list :\n");
        if(temp == NULL)
                printf("Alloc List is empty!\n");
        else
                while(temp != NULL)
                {
                        printf("Offset: %d, Memory: %d\n", temp -> offset, temp -> mem);
                        temp = temp->next;
                }
}

void traverseFreeList(Node *freelist)
{
        Node *temp;
        temp = freelist;
        printf("Free list :\n");
        if(temp == NULL)
                printf("Free List is empty!\n");
        else
                while(temp!=NULL)
                {
                        printf("Offset: %d Memory: %d\n", temp -> offset, temp -> mem);
                        temp = temp -> next;
                }
}

int main()
{
        Node *alloclist = NULL, *freelist, *temp;
        int mem = MAXMEM, offset = 0, choice, i, yesno = 1, found;
        freelist = mymalloc(mem, offset);
        while(yesno)
        {
                printf("\n1: Allocate memory\n2: Free up memory\n3: Traverse allocated list\n4: Traverse free list\n");
                printf("Choose any one of above and enter : ");
                scanf("%d", &choice);
                switch(choice)
                {
                        case 1: printf("Enter amount of space you want to allocate : ");
                                scanf("%d", &mem);
                                BestFit(&alloclist, &freelist, mem);
                                break;
                        case 2: found = 0;
                                Node *prev = NULL;
                                temp = alloclist;
                                printf("Enter offset of memory block to free up : ");
                                scanf("%d", &offset);
                                while(temp != NULL && found == 0)
                                {
                                        if(temp -> offset == offset)
                                                found = 1;
                                        else
                                        {
                                                prev = temp;
                                                temp = temp -> next;
                                        }
                                }
                                if(found == 0)
                                        printf("Node does not exist\n");
                                else
                                {
                                        if(prev != NULL)
                                                prev -> next = temp -> next;
                                        else
                                                alloclist = alloclist -> next;
                                        temp -> next = NULL;
                                        free_up(temp, &freelist);
                                        mergefree(freelist);
                                        printf("Memory freed up successully\n");
                                }
                                break;
                        case 3: traverseAllocList(alloclist);
                                break;
                        case 4: traverseFreeList(freelist);
                                break;
                        default: printf("Invalid choice!\n");
                }
                printf("Enter 1 to repeat or 0 to quit : ");
                scanf("%d", &yesno);
        }
        return 0;
}