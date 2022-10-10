//1. 스택을 구현

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Len 100000
typedef struct _node{
    int idx;
    char data;
    struct _node *next;
}Node;

typedef struct _stack{
    Node *head;
}Stack;

void Init(Stack *stack);
void Push(Stack *stack, char data, int idx);
char Peek(Stack *stack);
int Pop(Stack *stack);

int main()
{
    Stack stack;
    Init(&stack);

    char str[Len];
    scanf("%s", str);

    int idx = 0;
    int stick = 0;
    int result = 0;
    for(int i = 0; i<strlen(str); i++)
    {
        if(str[i] == '(')
        {
            Push(&stack, str[i], idx);
        }
        else if(Peek(&stack) == idx - 1)
        {
            int trash = Pop(&stack);
        }
        else
        {
            int temp = Pop(&stack);
            printf("stick : %d\n", (idx-temp-1)/2);
        }
        idx++;
    }
    printf("%d \n", stick);
    return 0;
}

void Init(Stack *stack)
{
    stack->head = NULL;
}

int Pop(Stack *stack)
{
    Node *rnode = stack->head;
    int ridx = stack->head->idx;

    stack->head = stack->head->next;
    free(rnode);
    return ridx;
}

char Peek(Stack *stack)
{
    return stack->head->idx;
}

void Push(Stack *stack, char data, int idx)
{
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->idx = idx;

    newnode->next = stack->head;
    stack->head = newnode;
}