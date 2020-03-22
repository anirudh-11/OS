#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct data
{
    int *a;
    int m;
    int ele;
    int b, e;
};

void sort(int m, int a[m])
{
    int t;
    for(int i = 0; i < m; i ++)
    {
        for(int j = 0; j < m - i - 1; j ++)
        {
            if(a[j] > a[j + 1])
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

void* bs(void* param)
{
    struct data *d = malloc(sizeof(struct data));
    d = param;
    int beg = d -> b;
    int end = d -> e;
    int *a = d -> a;
    int mid;
    void *ret = malloc(sizeof(int));
    int flag = 0;
    while(beg <= end)
    {
        mid = (beg + end)/2;
        if(a[mid] == d -> ele)
        {
            printf("Found at position %d\n", mid);
            pthread_t tid[2];
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            for(int i = 0; i < 2; i ++)
            {
                struct data *d1 = malloc(sizeof(struct data));
                d1 = d;
                if(i == 1)
                    d1 -> e = mid - 1;
                else
                    d1 -> b = mid + 1;
                pthread_create(&tid[i], &attr, bs, d1);
            }
            for(int i = 0; i < 2; i ++)
            {
                pthread_join(tid[i], NULL);
            }
            flag = 1;
            *(int *)ret = flag;
            pthread_exit(ret);
        }
        else if(a[mid] > d -> ele)
        {
            end = mid - 1;
        }
        else
        {
            beg = mid + 1;
        }
    }
    *(int *)ret = flag;
    pthread_exit(ret);
}


int main()
{
    int m;
    printf("Enter the array size : ");
    scanf("%d", &m);
    int a[m];
    printf("Enter the elements : \n");
    for(int i = 0; i < m; i ++)
    {
        scanf("%d", &a[i]);
    }
    sort(m, a);
    pthread_t tid[4];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int ele;
    printf("Enter the element to be searched : ");
    scanf("%d", &ele);
    for(int i = 0; i < 4; i++)
    {
        struct data *d = malloc(sizeof(struct data));
        d -> ele = ele;
        d -> m = m;
        d -> a = a;
        d -> e = (i + 1)*m/4;
        d -> b = d -> e - m/4;
        pthread_create(&tid[i], &attr, bs, d);
        // free(d);
    }
    void *mem;
    int flag = 0;
    for(int i = 0; i < 4; i++)
    {
        pthread_join(tid[i], &mem);
        if(*(int *)mem == 1)
        {
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("Element is not found\n");
    }
    printf("\n");
    return(0);
}