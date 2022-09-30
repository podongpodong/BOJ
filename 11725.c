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
    int haveParent;
}Tnode;

Tnode* SetNode(int data);
void LinkedTree(Tnode *parent, Tnode *child);
Tnode* Search(Tnode *bt, int target);

void Traversal(Tnode *bt, int target); //중위 순회

int main()
{ 

    int cnt;
    scanf("%d", &cnt);

    Tnode **nodeArray;
    nodeArray = (Tnode**)malloc(sizeof(Tnode*) * cnt);
    for(int i = 1; i<=cnt; i++)
    {
        nodeArray[i-1] = SetNode(i);
    }

    Tnode *Root = nodeArray[0];

    for(int i = 0; i<cnt-1; i++)
    {
        int num1, num2;
        scanf("%d %d", &num1, &num2);

        Tnode *searchNode1 = Search(Root, num1);
        Tnode *searchNode2 = Search(Root, num2);

        if(searchNode1 != NULL)
        {
            if(nodeArray[num2-1]->haveParent == 1)
            {
                for(int i = 0; i<cnt; i++)
                {
                    if(nodeArray[i]->left == nodeArray[num2-1])
                    {
                        nodeArray[i]->left = NULL;
                        nodeArray[num2-1]->haveParent = 0;
                        LinkedTree(nodeArray[num2-1], nodeArray[i]);
                        break;
                    }
                }
            }
            LinkedTree(searchNode1, nodeArray[num2-1]);
        }
        else if(searchNode2 != NULL)
        {
            if(nodeArray[num1-1]->haveParent == 1)
            {
                for(int i = 0; i<cnt; i++)
                {
                    if(nodeArray[i]->left == nodeArray[num1-1])
                    {
                        nodeArray[i]->left = NULL;
                        nodeArray[num1-1]->haveParent = 0;
                        LinkedTree(nodeArray[num1-1], nodeArray[i]);
                        break;
                    }
                }
            }
            LinkedTree(searchNode2, nodeArray[num1-1]);
        }
        else if(searchNode1 == NULL && searchNode2 == NULL)
        {
            LinkedTree(nodeArray[num1-1], nodeArray[num2-1]);
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
    nd->haveParent = 0;
    return nd;
}

void LinkedTree(Tnode *parent, Tnode *child)
{
    if(parent->left == NULL)
    {
        parent->left = child;
        child->haveParent = 1;
    }
    else if(parent->right == NULL)
    {
        parent->right = child;
        child->haveParent = 1;
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
        if(bt->right->data == target) 
        {
            printf("%d\n", bt->data);
            return;
        }
        Traversal(bt->right, target);
    }
    else if(bt->right == NULL)
    { 
        if(bt->left->data == target)        
        {
            printf("%d\n", bt->data);
            return;
        }
        Traversal(bt->left, target);
    }
    else
    {
        if(bt->left->data == target || bt->right->data == target) 
        {
            printf("%d\n", bt->data);
            return;
        }
        Traversal(bt->right, target);
        Traversal(bt->left, target);
    }

}