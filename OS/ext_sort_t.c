#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>

struct data
{
    int* a;
    int k;
    int max; 
};

FILE *inp[10];

// void sort(int n, int a[n])
// {
//     int temp;
//     for(int i = 0; i < n; i ++)
//     {
//         for(int j = 0; j < n - 1 - i; j ++)
//         {
//             if(a[j] > a[j + 1])
//             {
//                 temp = a[j + 1];
//                 a[j + 1] = a[j];
//                 a[j] = temp;
//             }
//         }
//     }
// }

void sort(int n, int a[n])
{
    int temp;
    int i = 0, j = 0;
    for(int i = 0; i < n - 1; i ++)
        for(int j = i + 1; j > 0; j --)
        {
            if(a[j] < a[j - 1])
            {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
            else
            {
                break;
            }
            
        }
}

int min(int n, int a[n])
{
    int pos = 0, min = a[0]; 
    for(int i = 1; i < n; i ++)
    {
        if(min > a[i])
        {
            min = a[i];
            pos = i;
        }
    }
    return(pos);
}

void *runner(void *param)
{
    struct data *d = malloc(sizeof(struct data));
    d = param;
    int count = 0;
    // int *arr = d -> a;
    int k = d -> k;
    // int max = 0;
    int fno = d -> max;
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    char name[12] = "input0.txt";   
    sprintf(&(name[5]), "%d", fno);
    name[6] = '.';
    int arr[k];
    char buf[100];
    int counter = 0;
    int num;
    FILE *fp = fopen(name, "w+");
    // sort(k, arr);
    while(fscanf(fptr, "%s ", buf) != EOF)
    {
        counter ++;
        if(counter > k*(d -> max + 1))
        {
            break;
        }
        else if(counter > k*(d -> max))
        {
            arr[count] = atoi(buf);
            count ++;
        }
    }
    sort(count, arr);
    void *ret = malloc(sizeof(int));
    *(int *)ret = arr[count -1]; 
    for(int i = 0; i < count; i ++)
        fprintf(fp, "%d ", arr[i]);
    fprintf(fp, "\n");
    fclose(fp);
    fclose(fptr);
    pthread_exit(ret);
}

int main()
{
    // FILE* fptr;
    // char buf[100];
    // int k = 3;
    // fptr = fopen("input.txt", "r");
    // int counter = 0;
    // int *la;
    // int fno = 0;
    // char c;
    // int n = 0;
    // int rno = 0;
    // char name[12] = "input0.txt";
    // int max = 0;
    // // int fno = 0;
    // while(fscanf(fptr, "%s", buf) != EOF)
    //     n ++;
    // fclose(fptr);
    // fptr = fopen("input.txt", "r");
    // if(n % k == 0)
    //     rno = n /k;
    // else
    // {
    //     rno = (n /k) + 1; 
    // }
    
    // // fclose(fptr);
    // // FILE *finst[rno];
    // // for(int i = 0; i < rno; i ++)
    // // {
    // //     finst[i] = fopen("input.txt", "r");
    // //     counter = 0;
    // //     while(counter < i*k)
    // //     {
    // //         fscanf(finst[i], "%s", buf);
    // //         counter ++;
    // //     }
    // // }
    // pthread_t tid[rno];
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    // int *arr = malloc(k * sizeof(int));

    // for(int i = 0; i < rno; i ++)
    // {

    // }

    // // while(fscanf(fptr, "%s", buf) != EOF)
    // // {
    // //     // printf("%d ", atoi(buf));
    // //     la = arr;
    // //     if(atoi(buf) > max)
    // //     {
    // //         max = atoi(buf);
    // //     }
    // //     arr[counter] = atoi(buf);
    // //     if(counter == k - 1)
    // //     {
    // //         struct data *d = malloc(sizeof(struct data));
    // //         d -> a = arr;
    // //         d -> k = k;
    // //         d -> max = fno;
    // //         counter = 0;
    // //         pthread_create(&tid[fno], &attr, runner, d);
    // //         fno ++;
    // //         arr = malloc(k * sizeof(int));
    // //     }
    // //     else
    // //         counter ++;
    // // }
    // // if(counter != 0)
    // // {
    // //     struct data *d1 = malloc(sizeof(struct data));
    // //     d1 -> a = la;
    // //     d1 -> k = counter;
    // //     d1 -> max = fno;
    // //     counter = 0;
    // //     pthread_create(&tid[fno], &attr, runner, d1);
    // // }
    // fclose(fptr);
    // for(int i = 0; i < rno; i ++)
    // {
    //     pthread_join(tid[i], NULL);
    // }
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    int n = 0;
    int fno;
    int k = 4;
    char buf[100];
    char name[12] = "input0.txt";
    while(fscanf(fptr, "%s ", buf) != EOF)
        n++;
    fclose(fptr);
    if(n % k == 0)
        fno = n / k;
    else
    {
        fno = n/k + 1;
    }
    pthread_t tid[fno];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int i = 0; i < fno; i ++)
    {
        struct data *d = malloc(sizeof(struct data));
        d -> max = i;
        d -> k = k;
        pthread_create(&tid[i], &attr, runner, d);
    }
    int max = 0;
    void *mem = malloc(sizeof(int));
    for(int i = 0; i < fno; i ++)
    {
        pthread_join(tid[i], &mem);
        if(*(int *)mem > max)
            max = *(int *)mem;
    }
    int comp[fno];
    // fclose(fptr);
    fptr = fopen("input.txt", "w+");
    for(int i = 0; i < fno; i ++)
    {
        sprintf(&(name[5]), "%d", i);
        name[6] = '.';
        inp[i] = fopen(name, "r"); 
        fscanf(inp[i], "%s ", buf);
        comp[i] = atoi(buf);
    }
    int counter = 0;
    int pos = 0;
    while(counter < fno)
    {
        pos = min(fno, comp);
        fprintf(fptr, "%d ", comp[pos]);
        if(fscanf(inp[pos], "%s ", buf) != EOF)
        {
            comp[pos] = atoi(buf);
        }
        else
        {
            comp[pos] = max + 10;
            fclose(inp[pos]);
            counter ++;
        }
    }
    // fclose(inp[pos]);
    fprintf(fptr, "\n");
    fclose(fptr);
    
    printf("\n");
    return(0);
}

// struct d1
// {
//     FILE *fptr;
//     FILE *fp;
//     int t;
// };

// void* runner(void *param)
// {
//     struct d1 *d = malloc(sizeof(struct d1));
//     d = param;
//     d -> fptr = fopen("input.txt", "r");
//     if(d -> t == 0)
//     {
//         d -> fp = fopen("input0.txt", "w+");
//     }
//     else
//     {
//         d -> fp = fopen("input1.txt", "w+");
//     }
    
//     char buf[100];
//     while(fscanf(d -> fptr, "%s", buf) != EOF)
//     {
//         printf("%s", buf);
//         fprintf(d -> fp, "%s ", buf);
//     }
//     fclose(d -> fptr);
//     fclose(d -> fp);
//     pthread_exit(NULL);
// }

// int main()
// {
//     // FILE *fptr1;
//     // fptr1 = fopen("input.txt", "r");
//     // FILE *fptr2 = fopen("input.txt", "r");
//     // fptr2 = fopen("input.txt", "r");
//     // FILE *fp1;
//     // FILE *fp2;
//     // fp1 = fopen("input0.txt", "w+");
//     // fp2 = fopen("input1.txt", "w+");
//     pthread_t tid[2];
//     pthread_attr_t attr;
//     pthread_attr_init(&attr);

//     struct d1 *d = malloc(sizeof(struct d1));
//     // d -> fptr = fptr1;
//     // d -> fp = fp1;
//     d -> t = 0;
//     struct d1* d2 = malloc(sizeof(struct d1));
//     // d2 -> fptr = fptr1;
//     // d2 -> fp = fp2;
//     d2 -> t = 1;
//     pthread_create(&tid[0], &attr, runner, d);
//     pthread_create(&tid[1], &attr, runner, d2);
//     pthread_join(tid[0], NULL);
//     pthread_join(tid[1], NULL);
//     // fclose(fptr1);
//     // fclose(fptr2);
//     // fclosse(fp1);
//     // fcloses(fp2);
//     return(0);
// }