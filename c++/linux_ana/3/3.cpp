#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATASIZE 10

typedef struct stringdata
{
    char *string;
    int iscontinuing;
    struct stringdata *next;
} mydata;

mydata *append(mydata *start, char *input);
void displaydata(mydata *start);
void freedata(mydata *start);

int main(void)
{
    char input[DATASIZE];
    mydata *start = NULL;

    printf("输入一些数据，完成后按Ctrl+D。 \n");

    while (fgets(input, sizeof(input), stdin))
    {
        start = append(start, input);
    }

    displaydata(start);
    freedata(start);
    return 0;
}

mydata *append(mydata *start, char *input)
{
    mydata *cur = start, *prev = NULL, *pnew;

    while (cur)
    {
        prev = cur;
        cur = cur->next;
    }
    cur = prev;

    pnew = (mydata *)malloc(sizeof(mydata));
    if (!pnew)
    {
        printf("无法分配内存！\n");
        exit(255);
    }

    if (cur)
        cur->next = pnew;
    else
        start = pnew;

    cur = pnew;

    if (!(cur->string = (char *)malloc(sizeof(input) + 1)))
    {
        printf("无法分配内存！\n");
        exit(255);
    }
    strcpy(cur->string, input);
    cur->iscontinuing = !(input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\r');
    cur->next = NULL;

    return start;
}

void displaydata(mydata *start)
{
    mydata *cur;
    int linecounter = 0, structcounter = 0;
    int newline = 1;

    cur = start;
    while (cur)
    {
        if (newline)
            printf("行 %d:", ++linecounter);
        structcounter++;
        printf("%s", cur->string);
        newline = !cur->iscontinuing;
        cur = cur->next;
    }
    printf("此数据包含%d行，并存储在%d个结构中。\n",
           linecounter, structcounter);
}

void freedata(mydata *start)
{
    mydata *cur, *next = NULL;

    cur = start;
    while (cur)
    {
        next = cur->next;
        free(cur->string);
        free(cur);
        cur = next;
    }
}
