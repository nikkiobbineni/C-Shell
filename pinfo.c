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
void pinfo(char *C[], int pid, char H[])
{
    char buf[2000];
    char buf2[2000];
    char buf3[2000];
    char buf4[2000];
    char buf5[2000];
    int useless;
    char useless2[2000];
    char A;
    char p[50];
    strcpy(buf, "/proc/");
    printf("pid : ");
    if (pid != 0)
    {
        printf("%d", pid);
        sprintf(p, "%d", pid);
        strcat(buf, p);
    }
    else
    {
        printf("%s", C[1]);
        strcat(buf, C[1]);
    }
    printf("\n");
    strcpy(buf2, buf);
    strcpy(buf3, buf);
    strcpy(buf4, buf);
    strcat(buf2, "/stat");
    strcat(buf3, "/statm");
    strcat(buf4, "/exe");
    // printf("%s",buf2);
    FILE *f1 = fopen(buf2, "r");
    FILE *f2 = fopen(buf3, "r");
    if (f1 == NULL || f2 == NULL)
    {
        perror("Cant open");
    }
    if (f1 != NULL && f2 != NULL)
    {
        fscanf(f1, "%d", &useless);
        fscanf(f1, "%s", useless2);
        fscanf(f1, " %c", &A);
        fscanf(f2, "%d", &useless);
        printf("process status : ");
        printf("%c", A);
        int plus;
        int minus;
        fscanf(f1, "%*d %d %*d %*d %d", &plus, &minus);
        if (plus == minus)
        {
            printf("+");
        }
        printf("\n");
        printf("memory : ");
        printf("%d\n", useless);
        readlink(buf4, buf5, 1000);
        if (strstr(buf5, H) == NULL)
        {
            printf("executable path : %s\n", buf5);
        }
        else
        {
            char temp[1000] = "~";
            strcat(temp, strstr(buf5, H) + strlen(H));
            printf("executable path : %s\n", temp);
        }
    }
}