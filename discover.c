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
#include <pwd.h>
#include <limits.h>
#include <signal.h>
#include "main.h"
void printing(char *command, int xyz, char H[], int hans, int file, char *files)
{
    DIR *dir;
    struct dirent *D;
    char store[1000];
    char buf[2000];
    int i = 0;
    dir = opendir(command);
    if (dir == NULL)
    {
        // perror("Cant open directory");
    }
    else
    {
        D = readdir(dir);
        while (D != NULL)
        {
            if (D->d_name[0] != '.')
            {
                strcpy(buf, command);
                strcat(buf, "/");
                strcat(buf, D->d_name);
                if (opendir(buf) == NULL)
                {
                    i = 1;
                }
                if (file != 1)
                {
                    if (xyz == 0 || (xyz == 2 && i == 1) || (xyz == 1 && i == 0))
                    {

                        if (hans != 0)
                        {
                            printf("~");
                        }
                        printf("%s\n", &buf[hans]);
                    }
                }
                else
                {
                    if (strcmp(D->d_name, files) == 0)
                    {
                        printf("%s\n", &buf[hans]);
                    }
                }
                printing(buf, xyz, H, hans, file, files);
                i = 0;
            }
            D = readdir(dir);
        }
    }
}
void discover(char *C[], int times, char H[])
{
    int d = 0, f = 0, hps = 0, xp = 1, fps = 0, dps = 0;
    char buf[1000];
    while (xp < times)
    {
        if (strcmp("-d", C[xp]) == 0)
        {
            d = 1;
        }
        else if (strcmp("-f", C[xp]) == 0)
        {
            f = 1;
        }
        else if (strcmp(".", C[xp]) == 0 || strcmp("..", C[xp]) == 0 || strcmp("~", C[xp]) == 0)
        {
        }
        else
        {
            if (C[xp][0] == '.')
            {
                dps = 1;
            }
            else
            {
                fps = 1;
                strcpy(buf, C[xp]);
            }
        }
        xp++;
    }
    if (d == 1 && f == 0)
    {
        hps = 1;
    }
    if (d == 0 && f == 1)
    {
        hps = 2;
    }
    if (d == 0 && f == 0)
    {
        hps = 0;
    }
    if (d == 1 && f == 1)
    {
        hps = 0;
    }
    if (times != 1)
    {
        if (fps != 1 && (strcmp(C[1], "~") == 0))
        {
            printf("~\n");
            printing(H, hps, H, strlen(H), fps, buf);
        }
        else if (fps != 1 && (strcmp(C[1], "..") == 0 || strcmp(C[1], ".") == 0))
        {
            printf("%s\n", C[1]);
            printing(C[1], hps, H, 0, fps, buf);
        }
        else if (fps != 1 && (strcmp(C[1], "-d") == 0 || strcmp(C[1], "-f") == 0))
        {
            printf(".\n");
            printing(".", hps, H, 0, fps, buf);
        }
        else
        {
            if (dps == 1 && fps != 1)
            {
                printing(C[1], hps, H, 0, fps, buf);
            }
            if (fps == 1 && dps != 1)
            {
                char abc[strlen(buf) - 1];
                for (int i = 0; i < strlen(buf) - 2; i++)
                {
                    abc[i] = buf[i + 1];
                }
                if (strcmp(".", C[1]) == 0 || strcmp("..", C[1]) == 0)
                {
                    printing(C[1], hps, H, 0, fps, abc);
                }
                if (strcmp("~", C[1]) == 0)
                {
                    printing(H, hps, H, 0, fps, abc);
                }
            }
            if (fps == 1 && dps == 1)
            {
                char abc[strlen(buf) - 1];
                for (int i = 0; i < strlen(buf) - 2; i++)
                {
                    abc[i] = buf[i + 1];
                }
                printing(C[1], hps, H, 0, fps, abc);
            }
        }
    }
    else
    {
        printf(".\n");
        printing(".", hps, H, 0, fps, buf);
    }
}
