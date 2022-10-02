#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUCKET_SIZE 26
#define Len 500000
#define TRUE 1
#define FALSE 0

typedef struct _node{
    int key; //학번
    char value[20]; //이름
    struct _node *next;
}Node;

typedef struct _bucket{
    int numOfdata; // 같은 색인의 데이터가 몇개 있는지 확인하는 용도
    Node *head;// 충돌이 일어나는 데이터를 연결리스트로 연결
}Bucket;

Node* CreateNode(int key, char *value);
int Hashing(int key);
void Init(Bucket *hashtable);
void Add(Bucket *hashtable, int key, char *value);

int Check(Bucket *hashtable, int key, char *value);
void Qsort(char **result, int L, int R);

int main()
{
    char name[20];

    Bucket hashtable[BUCKET_SIZE];
    Init(hashtable);

    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i<n; i++)
    {
        scanf("%s", name);

        Add(hashtable, name[0], name);
    }

    char *result[Len];
    int num = 0;

    for(int i = 0; i<m; i++)
    {
        scanf("%s", name);

        if(Check(hashtable, name[0], name))
        {
            result[num] = (char *)malloc(sizeof(char) * strlen(name));
            strcpy(result[num], name);
            num +=1;
        }

    }

    Qsort(result, 0, num-1);
    printf("%d\n", num);
    for(int i = 0; i<num; i++) printf("%s\n", result[i]);
    
}
Node* CreateNode(int key, char *value)
{
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->key = key;
    strcpy(newnode->value, value);
    newnode->next = NULL;

    return newnode;
}

int Hashing(int key)
{
    return (key-97)%BUCKET_SIZE;
}

void Init(Bucket *hashtable)
{
    for(int i = 0; i<BUCKET_SIZE; i++) 
        hashtable[i].head = NULL;
}

void Add(Bucket *hashtable, int key, char *value)
{
    int idx = Hashing(key);
    Node *input = CreateNode(key,value);

    if(hashtable[idx].head == 0)
    {
        hashtable[idx].head = input;
    }
    else
    {
        Node *cur = hashtable[idx].head;
        while(cur->next != NULL)
            cur = cur->next;
        
        cur->next = CreateNode(key,value);

    }
}

int Check(Bucket *hashtable, int key, char *value)
{
    int idx = Hashing(key);
    if(hashtable[idx].head != NULL)
    {
        Node *cur = hashtable[idx].head;
        while(cur != NULL)
        {
            if(strcmp(cur->value, value) == 0) return TRUE;
            cur = cur->next;
        }
    }

    return FALSE;
}

void Qsort(char **result, int L, int R)
{
    int left = L, right = R;
    char *pivot = result[(left+right)/2];
    char *temp;

    do
    {
        while(strcmp(result[left], pivot) < 0) 
            left++;

        while(strcmp(result[right], pivot) > 0) 
            right--;

        if(left<=right)
        {
            temp = result[left];
            result[left] = result[right];
            result[right] = temp;

            left++;
            right--;
        }
    }while(left<=right);

    if(left < R)
        Qsort(result, left, R);
    
    if(L < right)
        Qsort(result, L, right);
}