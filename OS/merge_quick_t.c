#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct dataq
{
    int beg, end, m;
    int *a;
};

struct datam
{
    int beg, end, m;
    int *a;
};

void merges(int a[], int beg, int end)
{
    int mid = (beg + end)/2;
    int c[end - beg];
    int k = 0, i = beg, j = mid;
    while(i < mid && j < end)
    {
        if(a[i] < a[j])
        {
            c[k] = a[i];
            i ++;
            k ++;
        }
        else
        {
            c[k] = a[j];
            k ++;
            j ++;
        }
    }
    while(i < mid)
    {
        c[k] = a[i];
        i ++;
        k ++;
    }
    while(j < end)
    {
        c[k] = a[j];
        j ++;
        k ++;
    }

    for(int q = beg; q < end; q ++)
    {
        a[q] = c[q - beg];
    }
}

void* merge(void* data)
{
    struct datam *d = malloc(sizeof(struct datam));
    d = data;
    int b, e, n;
    int *arr;
    b = d -> beg;
    e = d -> end;
    n = d -> m;
    arr = d -> a;

    if(b == e || b == e - 1)
    {
        pthread_exit(0);
    }
    else
    {
        struct dataq *d1 = malloc(sizeof(struct dataq));
        struct dataq *d2 = malloc(sizeof(struct dataq));
        
        int y = (b + e)/2;

        d1 -> beg = b;
        d1 -> end = y;
        d1 -> m = n;
        d1 -> a = arr;

        d2 -> beg = y;
        d2 -> end = e;
        d2 -> m = n;
        d2 -> a = arr;



        pthread_t tid1, tid2;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid1, &attr, merge, d1);
        pthread_create(&tid2, &attr, merge, d2);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        merges(arr, b, e);
    }
    pthread_exit(0);
}

int pivot(int x, int n, int a[n], int beg, int end)
{
    int pos;
    int c;
    for(int k = 0; k < n; k ++)
    {
        c = a[k];
        if(a[k] == x)
        {   
            pos = k;
            break;
        }
    }
    int i = beg;
    int j = end - 1;
    int temp;
    temp = a[pos];
    a[pos] = a[beg];
    a[beg] = temp;
    while(i < j)
    {
        for(i = beg; i < end; i ++)
        {
            if(a[i] > x)
                break;
        }
        for(j = end - 1; j > beg; j --)
        {
            if(a[j] < x)
                break;
        }
        if(i < j)
        {
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    temp = a[j];
    a[j] = a[beg];
    a[beg] = temp;
    return(j);
}

void *quick(void* data)
{
    
    struct dataq *d = malloc(sizeof(struct dataq));
    d = data;
    int b, e, n;
    int *arr;
    b = d -> beg;
    e = d -> end;
    n = d -> m;
    arr = d -> a;

    if(b == e || b == e - 1)
    {
        pthread_exit(0);
    }

    int y = pivot(arr[b], n, arr, b, e);
    struct dataq *d1 = malloc(sizeof(struct dataq));
    struct dataq *d2 = malloc(sizeof(struct dataq));
    if(b == y)
    {
        y = b + 1;
    }
    d1 -> beg = b;
    d1 -> end = y;
    d1 -> m = n;
    d1 -> a = arr;

    d2 -> beg = y;
    d2 -> end = e;
    d2 -> m = n;
    d2 -> a = arr;



    pthread_t tid1, tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid1, &attr, quick, d1);
    pthread_create(&tid2, &attr, quick, d2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_exit(0);
}

int main()
{
    int m = 7;
    // int a[] = {5, 3, 6, 8, 1, 2, 1};
    // int a[5] = {1, 2, 3, 4, 5};
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    struct dataq *d1 = malloc(sizeof(struct dataq));
    struct datam *d2 = malloc(sizeof(struct datam));
    printf("Enter the number of elements inthe array : ");
    scanf("%d", &m);
    int a[m], b[m];
    printf("Enter the array elements : \n");
    for(int i = 0; i < m; i ++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    d1 -> beg = 0;
    d1 -> end = m;
    d1 -> m = m;
    d1 -> a = &a[0];

    d2 -> beg = 0;
    d2 -> end = m;
    d2 -> m = m;
    d2 -> a = &b[0];
    

    pthread_create(&tid[0], &attr, quick, d1);
    pthread_join(tid[0], NULL);

    printf("The sorted array through quick sort : ");

    for(int i = 0; i < m; i ++)
    {
        printf("%d\t", a[i]);
    }

    printf("\n");

    pthread_create(&tid[1], &attr, merge, d2);
    pthread_join(tid[1], NULL);

    printf("The sorted array through merge sort : ");

    for(int i = 0; i < m; i ++)
    {
        printf("%d\t", b[i]);
    }    
    
    printf("\n");
    return(0);
}



