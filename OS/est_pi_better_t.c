#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct data
{
    int flag;
    int interval;
};

void* pointgen(void *d2)
{
    // srand(time(NULL)); 
    struct data* d = malloc(sizeof(struct data));
    d = d2;
    int inl = d -> interval;
    float x, y;
    int counter = 0;
    float dist;
    for(int i = 0; i < inl; i ++)
    {
        x =  (double)(rand() % (inl + 1)) / inl;
        y = (double)(rand() % (inl + 1)) / inl;
        
        dist = x*x + y*y;
        if(dist <= 1)
        {
            counter ++;
        } 
    }
    d -> flag = counter;
    pthread_exit(d);
    
}


int main()
{
    int interval;
    srand(time(NULL)); 
    printf("Enter the value of interval (the decimal precision for random coordinates): ");
    scanf("%d", &interval);
    int pc = 0;
    struct data *mem1;
    void *mem;
    pthread_t tid[interval];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int i = 0; i < interval; i ++)
    {
        struct data *d = malloc(sizeof(struct data));
        d -> interval = interval;
        pthread_create(&tid[i], &attr, pointgen, d);
    }
    
    for(int i = 0; i < interval; i ++)
    {
        pthread_join(tid[i], &mem);
        mem1 = mem;
        pc += mem1 -> flag;
        free(mem);
    }
    
    printf("The value of pi is : %lf", 4.0*pc/interval/interval);
    
    printf("\n");
    return(0);
}