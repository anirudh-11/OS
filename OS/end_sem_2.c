#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<ctype.h>
char *hash[100];

char words[100][100];

struct data
{
    char *word;
    int pos;
    int flag;
};

void *runner(void *param)
{
    struct data *is_unique = malloc(sizeof(struct data));
    is_unique = param;
    for(int i = (is_unique -> pos) - 1; i >= 0; i --)
    {
        if(strcmp(words[i], is_unique -> word) == 0)
        {    
            is_unique -> flag = 1;
            break;
        }
    }
    pthread_exit(is_unique);
}
int main()
{
    FILE *fptr;
    char buf[100];
    fptr = fopen("input.txt", "r");
    char temp[100];
    int count = 0;
    int word_size;
    int unique_words = 0;
    void *mem;
    struct data *ret_val = malloc(sizeof(struct data));
    while(fscanf(fptr, "%s", temp) != EOF )
    {
        word_size = 0;
        for(int i = 0; temp[i] != '\0'; i ++)
        {
            if(isdigit(temp[i]) || isalpha(temp[i]))
            {
                words[count][word_size] = temp[i];
                word_size ++;
            }
        }
        count ++;
    }
    for(int i = 0; i < count; i++)
        printf("word %d is %s\n", i + 1, words[i]);
    pthread_t tid[count];
    for(int i = 0; i < count; i ++)
    {
        struct data *d = malloc(sizeof(struct data));
        d -> word = words[i];
        d -> pos = i;
        d -> flag = 0;
        pthread_create(&tid[i], NULL, runner, d);
    }
    for(int i = 0; i < count; i ++)
    {
        pthread_join(tid[i], &mem);
        ret_val = mem;
        if(ret_val -> flag == 0)
        {
            hash[unique_words] = ret_val -> word;
            unique_words ++; 
            printf("#%d Unique word is = %s\n", i, ret_val -> word);
        }    
    } 
    fclose(fptr);

}