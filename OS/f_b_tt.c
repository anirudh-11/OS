#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct data
{
    int beg, end, n, x;
    int *a;
};

struct datab
{
    int *a;
    int m;
    int ele;
    int b, e;
};

struct retval
{
    int p;
    int c;
};

void* bs(void* param)
{
    struct datab *d = malloc(sizeof(struct datab));
    d = param;
    int beg = d -> b;
    int end = d -> e;
    int *a = d -> a;
    int mid;
    int c = 0;
    struct retval *ret = malloc(sizeof(struct retval));
    (ret -> c) = 0;
    ret -> p = -1;

    while(beg <= end)
    {
        mid = (beg + end)/2;
        if(a[mid] == d -> ele)
        {
            (ret -> c) ++;
            ret -> p = mid;
            pthread_exit(ret);
        }
        else if(a[mid] > d -> ele)
        {
            (ret -> c) ++;
            end = mid - 1;
        }
        else
        {
            (ret -> c) ++;
            beg = mid + 1;
        }
    }
    pthread_exit(ret);
}


int min(int n, int m)
{
    if(m < n)
    {
        return(m);
    }
    else
    {
        return(n);
    }
    
}

struct retval *fibonaccisearch(int n, int a[n], int x, int beg, int end)
{
    int f0 = 0;
    int f1 = 1;
    int f2 = 1;
    int t;
    struct retval *ret = malloc(sizeof(struct retval));
    ret -> c = 0;
    ret -> p = -1;
    while(f2 < end)
    {
        f0 = f1;
        f1 = f2;
        f2 = f1 + f0; 
    }

    int offset = beg -1;

    while(f2 > 1)
    {
        int i = min(f0 + offset, end - 1);
        if(a[i] == x)
        {
            ret -> p = i;
            (ret -> c) ++;
            pthread_exit(ret);
        }

        else if(a[i] > x)
        {
            f2 = f0;
            f1 = f1 - f0;
            f0 = f2 - f1;
            (ret -> c) ++;
        }

        else
        {
            f2 = f1;
            f1 = f0;
            f0 = f2 - f1;
            offset = i;
            (ret -> c) ++;
        }
    }

    if(f1 == 1 && a[offset + 1] == x)
    {
        ret -> c ++;
        ret -> p = offset + 1;
        pthread_exit(ret); 
    }
    else 
    {
        ret -> c ++;
        ret -> p = -1;
        pthread_exit(ret);
    }

}


void *runner(void *param)
{
    struct data *d = malloc(sizeof(struct data));
    d = param;
    int b = d -> beg;
    int e = d -> end;
    int n = d -> n;
    int x = d -> x;
    int *a = d -> a;
    struct retval *ret = malloc(sizeof(struct retval));
    ret = fibonaccisearch(n, a, x, b, e);
    pthread_exit(ret);

}



void sort(int n, int a[n])
{
    int t;
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n - i - 1; j ++)
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


int main()
{
    int n = 100;
    clock_t t;
    double timetaken;
    while(n < 1000)
    {
        int a[n];
        printf("For input size %d\n", n);
        for(int i = 0; i < n; i ++)
        {
            a[i] = rand() % 10000;
        }
        sort(n, a);
        int x;
        x = rand() % 10000;
        pthread_t tid[4];
        pthread_attr_t attr;
        pthread_attr_init(&attr);;
        printf("Fibonacci Search : ");
        t = clock();
        for(int i = 0; i < 4; i++)
        {
            struct data *d = malloc(sizeof(struct data));
            d -> x = x;
            d -> n = n;
            d -> a = a;
            d -> beg = i*n/4;
            d -> end = d -> beg + n/4;
            pthread_create(&tid[i], &attr, runner, d);
            // free(d);
        }
        struct retval *mem = malloc(sizeof(struct retval));
        void *mem1;
        int flag = 0;
        int c = 0;
        for(int i = 0; i < 4; i++)
        {
            pthread_join(tid[i], &mem1);
            mem = mem1;
            c = c + mem -> c;
            if(mem -> p != -1 && flag == 0)
            {
                printf("The element is found at %d", mem -> p);
                flag = 1;
            }
        }

        if(flag == 0)
        {
            printf("The element is not found");
        }
        t = clock() - t;
        timetaken = ((double)t) / CLOCKS_PER_SEC;
        printf(" and the total number of comparison taken is %d and the time taken to excecute is : %f\n", c, timetaken);

        printf("Binary Search : ");
        t = clock();
        for(int i = 0; i < 4; i++)
        {
            struct datab *d = malloc(sizeof(struct data));
            d -> ele = x;
            d -> m = n;
            d -> a = a;
            d -> b = i*n/4;
            d -> e = d -> b + n/4;
            pthread_create(&tid[i], &attr, bs, d);
            // free(d);
        }
        flag = 0;
        c = 0;
        for(int i = 0; i < 4; i++)
        {
            pthread_join(tid[i], &mem1);
            mem = mem1;
            c = c + mem -> c;
            if(mem -> p!= -1 && flag == 0)
            {
                printf("The element is found at %d", mem -> p);
                flag = 1;
            }
        }
        
        if(flag == 0)
        {
            printf("The element is not found");
        }
        t = clock() - t;
        timetaken = ((double)t) / CLOCKS_PER_SEC;
        printf(" and the number of comparisons are : %d and time taken to complete is : %f\n", c, timetaken);
        printf("\n\n");
        n ++;
    }
    // for(int i = 0; i < 4; i ++)
    // {
    //     printf("The element is found at : %d", fibonaccisearch(n, a, x, i*n/4, (i + 1)*n/4));
    // }
    return(0);
} 