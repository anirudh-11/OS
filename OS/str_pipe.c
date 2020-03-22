#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("In parent\n");
        close(fd[0]);
        char s1[100],s2[100];
        printf("\nEnter two strings s1 and s2 : \n");
        scanf("%s %s", s1, s2);
        int n = strlen(s1), m = strlen(s2);
        printf("%d\t%d\n", n, m);
        write(fd[1], &n, sizeof(n));
        for(int i = 0; i < n; i ++)
            write(fd[1], s1 + i, sizeof(*(s1 + i)));
        write(fd[1], &m, sizeof(m));
        for(int i = 0; i < m; i ++)
            write(fd[1], s2 + i, sizeof(*(s2 + i)));
        close(fd[1]);
        printf("p- The two string are %s and %s.\n", s1, s2);
        wait(NULL);
    }
    else if(pid == 0)
    {
        sleep(4);
        printf("In Child\n");
        close(fd[1]);
        int n, m;
        read(fd[0], &n, sizeof(n));
        printf("%d\n", n);
        char s1[n + 1];
        for(int i = 0; i < n; i ++)
            read(fd[0], s1 + i, sizeof(*(s1 + i)));
        read(fd[0], &m, sizeof(m));
        printf("%d\n", m);
        char s2[m + 1];
        for(int i = 0; i < m; i ++)
            read(fd[0], s2 + i, sizeof(*(s2 + i)));
        s1[n] = '\0';
        s2[m] = '\0';
        char s3[n + 1], s4[m + 1];
        printf("The two string are %s and %s.\n", s1, s2);
        strcpy(s3, s1);
        strcpy(s4, s2);
        printf("s1 is copied into s3 and s2 is copied into s4\n");
        printf("The catenated string is %s \n", strcat(s3, s4));
        strcpy(s2, s4);
        if(strcmp(s1, s2) > 0)
        {
            printf("%s > %s", s1, s2);
        }
        else if(strcmp(s1, s2) < 0)
        {
            printf("%s < %s", s1, s2);
        }
        else
        {
            printf("%s = %s", s1, s2);
        }
        printf("\n");

        for(int i = 0; i < n; i ++)
        {
            if(s1[i] >= 'A' && s1[i] <='Z')
                s1[i] = s1[i] + 32;
        
            else if(s1[i] >= 'a' && s1[i] <='z')
                s1[i] = s1[i] - 32;
        }
        for(int i = 0; i < m; i ++)
        {
            if(s2[i] >= 'a' && s2[i] <='z')
                s2[i] = s2[i] - 32;

            else if(s2[i] >= 'A' && s2[i] <='Z')
                s2[i] = s2[i] + 32;
        }
        
        printf("The case converted strings are %s and %s\n", s1, s2);
        close(fd[0]);
        
    }
    return(0);
}