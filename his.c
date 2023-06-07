#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include "main.h"
void history(char in[2000], int *count, char H[], char his_array[20][2000], int call)
{
    int x = *count;
    int l, y;
    char buf[2000];
    strcpy(buf, H);
    strcat(buf, "/store.txt");
    if (x == 0)
    {
        strcpy(his_array[0], in);
        *count = *count + 1;
    }
    if (x > 0 && x < 20)
    {
        l = strcmp(his_array[x - 1], in);
        if (l != 0)
        {
            strcpy(his_array[x], in);
            *count = *count + 1;
        }
    }
    if (x >= 20)
    {
        l = strcmp(his_array[19], in);
        if (l != 0)
        {
            for (int i = 1; i < 20; i++)
            {
                strcpy(his_array[i - 1], his_array[i]);
            }
            strcpy(his_array[19], in);
            *count = *count + 1;
        }
    }
    FILE *f = fopen(buf, "w");
    y = 0;
    if (*count >= 20)
    {
        while (y < 20)
        {
            fprintf(f, "%s\n", his_array[y]);
            //printf("%s",his_array[y]);
            y++;
        }
    }
    else
    {
        while (y < *count)
        {
            fprintf(f, "%s\n", his_array[y]);
            y++;
        }
    }
    fclose(f);
}