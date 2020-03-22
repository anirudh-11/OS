#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
struct dt
{
    char** param;
    int n;
};

int compensator(const void *e1,const void *e2)
{
    return(*(int*) e1 - *(int*) e2);
}

void* median(void* param)
{
    struct dt *data = param;
    int a[data -> n];
    for(int i = 1; i <= data -> n; i++)
    {
        a[i - 1] = atoi(data -> param[i]); 
    }

    qsort(a, data -> n, sizeof(int), compensator);
    
    if((data -> n) % 2 == 0)
        printf("meadian = %f\n", (a[(data -> n) / 2] + a[((data -> n) / 2) - 1]) / 2.0);
    else
        printf("meadian = %d\n", a[(data -> n) / 2]);
    pthread_exit(0);
    
}

void* mode(void* param)
{
    struct dt *data = param;
    int a[data -> n];
    for(int i = 1; i <= data -> n; i++)
    {
        a[i - 1] = atoi(data -> param[i]); 
    }
    struct fr
    {
        int f, d;
    };

    int m = 0;
    int flag;
    struct fr frequncy[data -> n];
    for(int i = 0; i <= data -> n; i++)
    {
        flag = -1;
        for(int j = 0; j < m; j++)
        {
            if(frequncy[j].d == a[i])
            {
                frequncy[j].f ++;
                flag = 1;
                break;
            }
        }
        if(flag == -1)
        {
            frequncy[m].d = a[i];
            frequncy[m].f = 1;
            m ++;
        }
    }
    int max = frequncy[0].f;
    int pos = 0;
    for(int i = 0; i <= m; i++)
    {
        if(max < frequncy[i].f)
        {
            max = frequncy[i].f;
            pos = i;
        }   
    }
    printf("mode = %d\n", a[(pos)]);
    pthread_exit(0);
    
}

void* mean(void* param)
{
    struct dt *data = param;
    float sum = 0;
    for(int i = 1; i <= data -> n; i++)
    {
        sum += atoi(data -> param[i]); 
    }

    printf("mean = %f\n", sum / data -> n);
    pthread_exit(0);
}



int main(int argc, char **argv)
{
    
    pthread_t tid[3];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    struct dt *data = malloc(sizeof(struct dt));
    data -> n = argc - 1;
    data -> param = argv;
    pthread_create(&tid[0], &attr, mean, data);
    pthread_create(&tid[1], &attr, median, data);
    pthread_create(&tid[2], &attr, mode, data);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    return(0);
}