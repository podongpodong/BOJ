//바로 트리에 연결되지 않는 경우가 있음.
/* 반례
10
1 3
5 4
3 2
2 7
5 7
9 10
5 10
6 8
1 6
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
    int data;
    struct _node *left;
    struct _node *right;
}Tnode;

Tnode* SetNode(int data);
void LinkedTree(Tnode *parent, Tnode *child);
Tnode* Search(Tnode *bt, int target);

void Traversal(Tnode *bt, int target); //중위 순회

int main()
{
    Tnode *Root = SetNode(1);

    int cnt;
    scanf("%d", &cnt);
    for(int i = 0; i<cnt-1; i++)
    {
        int num1, num2;
        scanf("%d %d", &num1, &num2);

        Tnode *snode1 = Search(Root, num1);
        Tnode *snode2 = Search(Root, num2);

        if(snode1 != NULL)
        {
            Tnode *input = SetNode(num2);
            LinkedTree(snode1, input);
        }
        else if(snode2 != NULL)
        {
            Tnode *input = SetNode(num1);
            LinkedTree(snode2, input);
        }
    }
    for(int i = 2; i<=cnt; i++)
    {
        Traversal(Root, i);
    }
    

    return 0;

}

Tnode* SetNode(int data)
{
    Tnode *nd = (Tnode*)malloc(sizeof(Tnode));
    nd->data = data;
    nd->left = NULL;
    nd->right = NULL;

    return nd;
}

void LinkedTree(Tnode *parent, Tnode *child)
{
    if(parent->left == NULL)
    {
        parent->left = child;
    }
    else if(parent->right == NULL)
    {
        parent->right = child;
    }
}

Tnode* Search(Tnode *bt, int target)
{
    if(bt != NULL)
    {
        if(bt->data == target) return bt;
        else
        {
            Tnode *tmp = Search(bt->left, target);
            if(tmp != NULL) return tmp;

            return Search(bt->right, target);
        }
    }
    return NULL;
}

void Traversal(Tnode *bt,  int target)//중위 순회
{
    if(bt->left == NULL && bt->right == NULL) return; //종료조건 bt가 NULL이면 리턴

    if(bt->left == NULL) 
    {
        if(bt->right->data == target) printf("%d\n", bt->data);
        Traversal(bt->right, target);
    }
    else if(bt->right == NULL)
    { 
        if(bt->left->data == target) printf("%d\n", bt->data);
        Traversal(bt->left, target);
    }
    else
    {
        if(bt->left->data == target || bt->right->data == target) printf("%d\n", bt->data);
        Traversal(bt->right, target);
        Traversal(bt->left, target);
    }

}