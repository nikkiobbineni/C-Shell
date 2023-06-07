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
#include <sys/wait.h>
char *mwf[100000] = {NULL};
int abcd;
void bg()
{
    // printf("uDIHcbskjb");
    int hari;
    pid_t ID;
    ID = waitpid(-1, &hari, WNOHANG);
    if (ID > 0)
    {
        printf("%s with pID = %d ", mwf[ID], ID);
        if (hari == 0)
        {
            printf("abnormally");
        }
        else
        {
            printf("normally");
        }
        printf("\n");
    }
}
int fgbg(char kesav[], int last, int time_taken)
{
    last = 0;
    if (kesav[strlen(kesav) - 1] == '&')
    {
        last = 1;
    }
    char *wxyz;
    char *anu[2000];
    char *anu2;
    int siya = 1;
    anu[0] = strtok(kesav, "&");
    wxyz = anu[0];
    while (wxyz != NULL)
    {
        wxyz = strtok(NULL, "&");
        if (wxyz != NULL)
        {
            siya++;
            anu[siya] = wxyz;
        }
    }
    time_t time1, time2;
    pid_t kothi, abhi;
    int i = 0;
    time1 = time(0);
    while (anu[i] != NULL)
    {
        char *anu23[2000];
        int j = 0;
        anu23[0] = strtok(anu[i], " \t\n");
        anu2 = anu23[0];
        while (anu2 != NULL)
        {
            anu2 = strtok(NULL, " \t\n");
            if (anu2 != NULL)
            {
                j++;
                anu23[j] = anu2;
            }
        }
        signal(SIGCHLD, bg);
        kothi = fork();
        if (kothi != 0)
        {
            siya--;
            i++;
            if ((siya == -1 && last == 1) || (siya == 0 && last == 0))
            {
                abhi = kothi;
            }
            else
            {
                printf("[%d] %d\n", i, kothi);
                mwf[kothi] = anu23[0];
            }
        }
        else
        {
            execvp(anu23[0], anu23);
        }
    }
    if (last == 0)
    {
        waitpid(abhi, NULL, 0);
    }
    time2 = time(0);
    abcd = time2 - time1;
    return (time2 - time1 > 1 && last == 0);
}
int times()
{
    return abcd;
}
