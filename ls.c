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
void bubbleSort(char *names[10000], int nonames)
{
    int swap_count = 0;
    char tempstr[10000];

    if (nonames == 1)
        return;

    for (int i = 0; i < nonames - 1; i = i + 1)
    {

        if (strcasecmp(&names[i][0], &names[i + 1][0]) < 0)
        {
            continue;
        }
        else
        {
            swap_count++;
            strcpy(&tempstr[0], &names[i][0]);
            strcpy(&names[i][0], &names[i + 1][0]);
            strcpy(&names[i + 1][0], &tempstr[0]);
        }
    }

    if (swap_count > 0)
        bubbleSort(names, nonames - 1);
}
void only_ls(char H[])
{
    char *store[10000];
    int i = 0;
    int k = 0;
    DIR *dir;
    struct dirent *D;
    dir = opendir(H);
    if (dir == NULL)
    {
        perror("Cant open directory");
    }
    else
    {
        D = readdir(dir);
        while (D != NULL)
        {
            if (D->d_name[0] != '.')
            {
                // printf("%s\n", D->d_name);
                store[i] = D->d_name;
                i++;
            }
            D = readdir(dir);
        }
        bubbleSort(store, i);
        while (k < i)
        {
            char Str[500];
            // getcwd(Str, sizeof(Str));
            strcpy(Str, H);
            strcat(Str, "/");
            strcat(Str, store[k]);
            // printf("%s\n", Str);
            struct stat y = {0};
            if (stat(Str, &y) == 0)
            {
                if (S_ISDIR(y.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", store[k]);
                    printf("\033[0m");
                }
                else if (y.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m");
                    printf("%s\n", store[k]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", store[k]);
                }
                k++;
            }
        }
    }
}
void ls_l(char H[])
{
    DIR *dir;
    struct dirent *D;
    char curr_dir[2000], buf[2000];
    char *store[10000];
    // getcwd(curr_dir, 2000);
    int all = 0;
    int i = 0;
    int k = 0;
    dir = opendir(H);
    if (dir == NULL)
    {
        perror("Cant open directory");
    }
    else
    {
        D = readdir(dir);
        while (D != NULL)
        {
            if (D->d_name[0] != '.')
            {
                // printf("%s\n", D->d_name);
                store[i] = D->d_name;
                i++;
            }
            D = readdir(dir);
        }
        bubbleSort(store, i);
    }
    struct stat ved = {0};
    int j = 0;
    while (j < i)
    {
        char Str[500];
        // getcwd(Str, sizeof(Str));
        strcpy(Str, H);
        strcat(Str, "/");
        strcat(Str, store[j]);
        // printf("%o\n", ved.st_mode);
        if (stat(Str, &ved) == 0)
        {
            all = all + ved.st_blocks;
        }
        j++;
    }
    printf("total ");
    printf("%d\n", all / 2);
    k = 0;
    while (k < i)
    {
        char Str[500];
        // getcwd(Str, sizeof(Str));
        strcpy(Str, H);
        strcat(Str, "/");
        strcat(Str, store[k]);
        // printf("%s\n", Str);
        struct stat y = {0};
        if (stat(Str, &y) == 0)
        {
            struct passwd *U = getpwuid(y.st_uid);
            struct group *G = getgrgid(y.st_gid);
            struct tm tyme;
            time_t t = y.st_mtime;
            char tym[2000];
            if (y.st_mode & S_IFDIR)
            {
                printf("d");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IRUSR)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IWUSR)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IXUSR)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IRGRP)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IWGRP)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IXGRP)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IROTH)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IWOTH)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IXOTH)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            printf(" %ld ", y.st_nlink);
            printf("%s %s %6ld", U->pw_name, G->gr_name, y.st_size);
            localtime_r(&t, &tyme);
            strftime(tym, sizeof(tym), "%b %d %Y %H:%M", &tyme);
            printf("  %s  ", tym);
            if (S_ISDIR(y.st_mode))
            {
                printf("\033[1;34m");
                printf("%s", store[k]);
                printf("\033[0m");
            }
            else if (y.st_mode & S_IXUSR)
            {
                printf("\033[1;32m");
                printf("%s", store[k]);
                printf("\033[0m");
            }
            else
            {
                printf("%s", store[k]);
            }
            printf("\n");
        }
        k++;
    }
}
void ls_a(char H[])
{
    DIR *dir;
    struct dirent *D;
    char curr_dir[2000], buf[2000];
    char *store[10000];
    getcwd(curr_dir, 2000);
    int i = 0;
    int k = 0;
    dir = opendir(H);
    if (dir == NULL)
    {
        perror("Cant open directory");
    }
    else
    {
        D = readdir(dir);
        while (D != NULL)
        {
            // printf("%s\n", D->d_name);
            store[i] = D->d_name;
            i++;
            D = readdir(dir);
        }
        bubbleSort(store, i);
        while (k < i)
        {
            char Str[500];
            // getcwd(Str, sizeof(Str));
            strcpy(Str, H);
            strcat(Str, "/");
            strcat(Str, store[k]);
            // printf("%s\n", Str);
            struct stat y = {0};
            if (stat(Str, &y) == 0)
            {
                if (S_ISDIR(y.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", store[k]);
                    printf("\033[0m");
                }
                else if (y.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m");
                    printf("%s\n", store[k]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", store[k]);
                }
                k++;
            }
        }
    }
}
void ls_la(char H[])
{
    DIR *dir;
    struct dirent *D;
    char curr_dir[2000], buf[2000];
    char *store[10000];
    // getcwd(curr_dir, 2000);
    int all = 0;
    int i = 0;
    int k = 0;
    dir = opendir(H);
    if (dir == NULL)
    {
        perror("Cant open directory");
    }
    else
    {
        D = readdir(dir);
        while (D != NULL)
        {
            // printf("%s\n", D->d_name);
            store[i] = D->d_name;
            i++;
            D = readdir(dir);
        }
        bubbleSort(store, i);
    }
    struct stat ved = {0};
    int j = 0;
    while (j < i)
    {
        char Str[500];
        // getcwd(Str, sizeof(Str));
        strcpy(Str, H);
        strcat(Str, "/");
        strcat(Str, store[j]);
        // printf("%o\n", ved.st_mode);
        if (stat(Str, &ved) == 0)
        {
            all = all + ved.st_blocks;
        }
        j++;
    }
    printf("total ");
    printf("%d\n", all / 2);
    k = 0;
    while (k < i)
    {
        char Str[500];
        // getcwd(Str, sizeof(Str));
        strcpy(Str, H);
        strcat(Str, "/");
        strcat(Str, store[k]);
        // printf("%s\n", Str);
        struct stat y = {0};
        if (stat(Str, &y) == 0)
        {
            struct passwd *U = getpwuid(y.st_uid);
            struct group *G = getgrgid(y.st_gid);
            struct tm tyme;
            time_t t = y.st_mtime;
            char tym[2000];
            if (y.st_mode & S_IFDIR)
            {
                printf("d");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IRUSR)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IWUSR)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IXUSR)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IRGRP)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IWGRP)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IXGRP)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IROTH)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IWOTH)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (y.st_mode & S_IXOTH)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            printf(" %ld ", y.st_nlink);
            printf("%s %s %6ld", U->pw_name, G->gr_name, y.st_size);
            localtime_r(&t, &tyme);
            strftime(tym, sizeof(tym), "%b %d %Y %H:%M", &tyme);
            printf("  %s  ", tym);
            if (S_ISDIR(y.st_mode))
            {
                printf("\033[1;34m");
                printf("%s", store[k]);
                printf("\033[0m");
            }
            else if (y.st_mode & S_IXUSR)
            {
                printf("\033[1;32m");
                printf("%s", store[k]);
                printf("\033[0m");
            }
            else
            {
                printf("%s", store[k]);
            }
            printf("\n");
        }
        k++;
    }
}
void ls(char *C[], char H[], int times)
{
    // printf("jkdCGCSH");
    DIR *dir;
    struct dirent *D;
    char curr_dir[2000], buf[2000];
    getcwd(curr_dir, 2000);
    char c1[] = "-a";
    char c2[] = "-l";
    char c3[] = ".";
    char c4[] = "..";
    char c5[] = "~";
    char c6[] = "-a -l";
    char c7[] = "-la";
    char c8[] = "-al";
    char *store[10000];
    int i = 0;
    int k = 0;
    int xp = 0;
    int wx = 0;
    int ch1 = 0, ch2 = 0, ch3 = 0, ch4 = 0, ch5 = 0, ch6 = 0;
    int wxi = 0;
    int geethu = 0;
    while (xp < times)
    {
        if (strcmp("-l", C[xp]) == 0)
        {
            ch2 = 1;
            wxi = 1;
        }
        else if (strcmp("-a", C[xp]) == 0)
        {
            ch3 = 1;
            wxi = 1;
        }
        else if (strcmp("-la", C[xp]) == 0 || strcmp("-al", C[xp]) == 0)
        {
            ch1 = 10;
            wxi = 1;
        }
        xp++;
    }
    if (ch2 == 1 && ch3 == 1)
    {
        ch1 = 10;
    }
    xp = 0;
    while (xp < times)
    {
        k = 0;
        i = 0;
        if (strcmp(".", C[xp]) == 0)
        {
            if (ch2 == 1 && ch3 != 1)
            {
                ls_l(".");
            }
            if (ch2 != 1 && ch3 == 1)
            {
                ls_a(".");
            }
            if (ch2 != 1 && ch3 != 1 && ch1 != 10)
            {
                dir = opendir(".");
                if (dir == NULL)
                {
                    perror("Cant open directory");
                }
                else
                {
                    D = readdir(dir);
                    while (D != NULL)
                    {
                        if (D->d_name[0] != '.')
                        {
                            // printf("%s\n", D->d_name);
                            store[i] = D->d_name;
                            i++;
                        }
                        D = readdir(dir);
                    }
                    bubbleSort(store, i);
                    while (k < i)
                    {
                        char Str[500];
                        // getcwd(Str, sizeof(Str));
                        strcpy(Str, H);
                        strcat(Str, "/");
                        strcat(Str, store[k]);
                        // printf("%s\n", Str);
                        struct stat y = {0};
                        if (stat(Str, &y) == 0)
                        {
                            if (S_ISDIR(y.st_mode))
                            {
                                printf("\033[1;34m");
                                printf("%s\n", store[k]);
                                printf("\033[0m");
                            }
                            else if (y.st_mode & S_IXUSR)
                            {
                                printf("\033[1;32m");
                                printf("%s\n", store[k]);
                                printf("\033[0m");
                            }
                            else
                            {
                                printf("%s\n", store[k]);
                            }
                            k++;
                        }
                    }
                }
            }
            if (ch1 == 10)
            {
                ls_la(".");
            }
            wx = 1;
            // printf("\n");
        }
        else if (strcmp("..", C[xp]) == 0)
        {
            if (ch2 == 1 && ch3 != 1)
            {
                ls_l("./..");
            }
            if (ch2 != 1 && ch3 == 1)
            {
                ls_a("..");
            }
            if (ch2 != 1 && ch3 != 1 && ch1 != 10)
            {
                dir = opendir("./..");
                if (dir == NULL)
                {
                    perror("Cant open directory");
                }
                else
                {
                    D = readdir(dir);
                    while (D != NULL)
                    {
                        if (D->d_name[0] != '.')
                        {
                            // printf("%s\n", D->d_name);
                            store[i] = D->d_name;
                            i++;
                        }
                        D = readdir(dir);
                    }
                    bubbleSort(store, i);
                    while (k < i)
                    {
                        char Str[500];
                        // getcwd(Str, sizeof(Str));
                        strcpy(Str, H);
                        strcat(Str, "/");
                        strcat(Str, store[k]);
                        // printf("%s\n", Str);
                        struct stat y = {0};
                        if (stat(Str, &y) == 0)
                        {
                            if (S_ISDIR(y.st_mode))
                            {
                                printf("\033[1;34m");
                                printf("%s\n", store[k]);
                                printf("\033[0m");
                            }
                            else if (y.st_mode & S_IXUSR)
                            {
                                printf("\033[1;32m");
                                printf("%s\n", store[k]);
                                printf("\033[0m");
                            }
                            else
                            {
                                printf("%s\n", store[k]);
                            }
                            k++;
                        }
                        k++;
                    }
                }
            }
            if (ch1 == 10)
            {
                ls_la("./..");
            }
            wx = 1;
        }
        else if (strcmp("~", C[xp]) == 0)
        {
            if (ch2 == 1 && ch3 != 1)
            {
                ls_l(H);
            }
            if (ch2 != 1 && ch3 == 1)
            {
                ls_a(H);
            }
            if (ch2 != 1 && ch3 != 1 && ch1 != 10)
            {
                dir = opendir(H);
                if (dir == NULL)
                {
                    perror("Cant open directory");
                }
                else
                {
                    D = readdir(dir);
                    while (D != NULL)
                    {
                        if (D->d_name[0] != '.')
                        {
                            // printf("%s\n", D->d_name);
                            store[i] = D->d_name;
                            i++;
                        }
                        D = readdir(dir);
                    }
                    bubbleSort(store, i);
                    while (k < i)
                    {
                        char Str[500];
                        // getcwd(Str, sizeof(Str));
                        strcpy(Str, H);
                        strcat(Str, "/");
                        strcat(Str, store[k]);
                        // printf("%s\n", Str);
                        struct stat y = {0};
                        if (stat(Str, &y) == 0)
                        {
                            if (S_ISDIR(y.st_mode))
                            {
                                printf("\033[1;34m");
                                printf("%s\n", store[k]);
                                printf("\033[0m");
                            }
                            else if (y.st_mode & S_IXUSR)
                            {
                                printf("\033[1;32m");
                                printf("%s\n", store[k]);
                                printf("\033[0m");
                            }
                            else
                            {
                                printf("%s\n", store[k]);
                            }
                            k++;
                        }
                        k++;
                    }
                }
            }
            if (ch1 == 10)
            {
                ls_la(H);
            }
            wx = 1;
        }
        else
        {
            if (strcmp("-l", C[xp]) != 0 && strcmp("-a", C[xp]) != 0 && strcmp("-la", C[xp]) != 0 && strcmp("-al", C[xp]) != 0)
            {
                char Str[500];
                // getcwd(Str, sizeof(Str));
                strcpy(Str, H);
                strcat(Str, "/");
                strcat(Str, C[xp]);
                // printf("%s\n", Str);
                struct stat y = {0};
                if (stat(Str, &y) == 0)
                {
                    if (y.st_mode & S_IFDIR)
                    {
                        if (ch1 == 10)
                        {
                            ls_la(C[xp]);
                            geethu = 1;
                        }
                        if (ch2 == 1 && ch3 != 1)
                        {
                            ls_l(C[xp]);
                            geethu = 1;
                        }
                        if (ch2 != 1 && ch3 == 1)
                        {
                            ls_a(C[xp]);
                            geethu = 1;
                        }
                        if (ch2 != 1 && ch3 != 1 && ch1 != 10)
                        {
                            only_ls(C[xp]);
                            geethu = 1;
                        }
                    }
                    else
                    {
                        if (ch1 == 10 || ch2 == 1 && ch3 != 1)
                        {
                            struct stat y = {0};
                            if (stat(C[xp], &y) == 0)
                            {
                                struct passwd *U = getpwuid(y.st_uid);
                                struct group *G = getgrgid(y.st_gid);
                                struct tm tyme;
                                time_t t = y.st_mtime;
                                char tym[2000];
                                if (y.st_mode & S_IFDIR)
                                {
                                    printf("d");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IRUSR)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IWUSR)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IXUSR)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IRGRP)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IWGRP)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IXGRP)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IROTH)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IWOTH)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }
                                if (y.st_mode & S_IXOTH)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }
                                printf(" %ld ", y.st_nlink);
                                printf("%s %s %6ld", U->pw_name, G->gr_name, y.st_size);
                                localtime_r(&t, &tyme);
                                strftime(tym, sizeof(tym), "%b %d %Y %H:%M", &tyme);
                                printf("  %s  ", tym);
                                printf("%s", C[xp]);
                                printf("\n");
                            }
                            geethu = 1;
                        }
                        if (ch2 != 1 && ch3 == 1)
                        {
                            printf("%s\n", C[xp]);
                            geethu = 1;
                        }
                        if (ch2 != 1 && ch3 != 1 && ch1 != 10)
                        {
                            printf("%s\n", C[xp]);
                            geethu = 1;
                        }
                    }
                }
            }
        }
        xp++;
    }
    if (wx != 1 && geethu != 1)
    {
        if (ch1 == 10)
        {
            ls_la(".");
        }
        if (ch2 == 1 && ch3 != 1)
        {
            ls_l(".");
        }
        if (ch2 != 1 && ch3 == 1)
        {
            ls_a(".");
        }
    }
}
