#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int n, choice;
    printf("\nEnter the number of terms in the series : \n");
    scanf("%d", &n);
    printf("\nEnter '0' for even and '1' for odd series generation : \n");
    scanf("%d", &choice);
    pid_t pid;
    pid = fork();
    if(pid > 0 && !choice)
    {
        for(int i = 0; i < n; i++)
        {
            printf("%d\t", i * 2);
        }
        printf("\nThe parent pid of this process is %d and the pid of this process is %d \n", getppid(), getpid());
        wait();
    }

    else if(pid == 0 && choice)
    {
        for(int i = 0; i < n; i++)
        {
            printf("%d\t", (i * 2) + 1);
        }
        printf("\nThe parent pid of this process is %d and the pid of this process is %d \n", getppid(), getpid());
    }
    return 0;
}