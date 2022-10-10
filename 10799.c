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
void Pop(Stack *stack);

int main()
{
    Stack stack;
    Init(&stack);

    char str[Len];
    scanf("%s", str);

    int idx = 0;
    int stick = 0, razer = 0;
    for(int i = 0; i<strlen(str); i++)
    {
        if(str[i] == '(')
        {
            Push(&stack, str[i], idx);
            idx++;
        }
        else
        {
            if(Peek(&stack) == idx-1)
            {
                Push(&stack, str[i], idx);
                idx++;
                razer += 1;
            }
            else
            {
                Push(&stack, str[i], idx);
                idx++;
                stick += 1;
            }
        }
    }
    printf("%d, %d", razer, stick);

    return 0;
}

void Init(Stack *stack)
{
    stack->head = NULL;
}

void Pop(Stack *stack)
{
    Node *rnode = stack->head;

    stack->head = stack->head->next;
    free(rnode);
}

char Peek(Stack *stack)
{
    return stack->head->idx;
}

void Push(Stack *stack, char data, int idx)
{
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;

    newnode->next = stack->head;
    stack->head = newnode;
}

