#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUCKET_SIZE 500000
#define TRUE 1
#define FALSE 0
typedef struct _node{
    char value[25];
    struct _node *next;
}Node;

typedef struct _bucket{
    Node *head;
}Bucket;

void HashInit(Bucket *hashtable);
int Hashing(char *value);
void Insert(Bucket *hashtable, char *value);

int Check(Bucket *hashtable, char *value);

void Swap(char **result, int idx1, int idx2);
int Partition(char **result, int left, int right);
void QuickSort(char **result, int left, int right);

int main()
{
    Bucket *hashtable = (Bucket*)malloc(sizeof(Bucket)*BUCKET_SIZE);
    HashInit(hashtable);

    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i<n; i++)
    {
        char name[21];
        scanf("%s", name);
        Insert(hashtable, name);
    }
    
    char **result;
    result = (char**)malloc(sizeof(char*) * n);
    int num = 0;

    for(int i = 0; i<m; i++)
    {
        char name[21];
        scanf("%s", name);

        if(Check(hashtable, name))
        {
            result[num] = (char *)malloc(sizeof(char) * (strlen(name)+1));
            strcpy(result[num], name);
            num += 1;
        }
    }

    QuickSort(result, 0, num-1);
    printf("%d\n", num);
    for(int i = 0; i<num; i++) printf("%s\n", result[i]);

    return 0;
}

void HashInit(Bucket *hashtable)
{
    for(int i = 0; i<BUCKET_SIZE; i++)
        hashtable[i].head = NULL;
}

int Hashing(char *value)
{
    unsigned long long result = 0;
    for(int i = 0; i<strlen(value); i++)
    {
        unsigned long long pow = 1;
        for(int j = 0; j<i; j++) 
            pow *= 23;
        result += value[i] * pow;
    }

    return result%BUCKET_SIZE;
}

void Insert(Bucket *hashtable, char *value)
{
    int idx = Hashing(value);

    Node *newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->value, value);

    if(hashtable[idx].head == NULL)
    {
        newnode->next = NULL;
        hashtable[idx].head = newnode;
    }
    else
    {
        newnode->next = hashtable[idx].head;
        hashtable[idx].head = newnode;
    }
}

int Check(Bucket *hashtable, char *value)
{
    int idx = Hashing(value);
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

void Swap(char **result, int idx1, int idx2)
{
    char *temp = result[idx1];
    result[idx1] = result[idx2];
    result[idx2] = temp;
}

int Partition(char **result, int left, int right)
{
    char *pivot = result[left];
    int low = left+1;
    int high = right;

    while(low <= high)
    {
        while(strcmp(pivot, result[low]) > 0 && low<=right) low++;

        while(strcmp(pivot, result[high]) < 0 && high >= (left+1)) high--;

        if(low<=high) Swap(result, low, high);
    }

    Swap(result, left, high);
    return high;
}

void QuickSort(char **result, int left, int right)
{
    if(left<=right)
    {
        int pivot = Partition(result, left, right);
        QuickSort(result, left, pivot-1);
        QuickSort(result, pivot+1, right);
    }
}