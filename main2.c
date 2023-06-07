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
char prev[2000];
void cd(char *C[], char H[], char U[])
{
    char curr_dir[2000], buf[2000], dir[2000];
    getcwd(curr_dir, 2000);
    char c1[1] = ".";
    char c2[2] = "..";
    // char c3[1] = "~";
    // char c4[1] = "-";
    // char c5[1] = " ";
    if (strcmp(C[1], c1) == 0)
    {
    }
    if (strcmp(C[1], c2) == 0)
    {
        getcwd(prev, 2000);
        if (strrchr(curr_dir, '/'))
        {
            strcpy(dir, prev);
            strncpy(dir, curr_dir, strrchr(curr_dir, '/') - curr_dir);
            chdir(dir);
        }
    }
    if (strcmp(C[1], "~") == 0)
    {
        chdir(H);
    }
    if (strcmp(C[1], "-") == 0)
    {
        chdir(prev);
        printf("%s\n", prev);
        strcpy(prev, curr_dir);
    }
    if (strrchr(C[1], '~') != NULL && strstr(C[1], "/") != NULL)
    {
        strcpy(buf, H);
        strcat(buf, strstr(C[1], "/"));
        strcpy(prev, curr_dir);
        chdir(buf);
    }
    else
    {
        strcpy(prev, curr_dir);
        chdir(C[1]);
    }
}
void echo(char *C[], int w)
{
    int e;
    e = w - 1;
    while (e > 0)
    {
        if (w - e == w - 1)
        {
            printf("%s", C[w - e]);
            // printf("abcdgf");
        }
        else
        {
            printf("%s ", C[w - e]);
            // printf("ujhbfdhsjc");
        }
        e--;
    }
    printf("\n");
}
void pwd(char *C[])
{
    char curr_dir[2000];
    getcwd(curr_dir, 2000);
    printf("%s", curr_dir);
    strcpy(prev, curr_dir);
    printf("\n");
}
int main()
{
    char user[2000], host[2000], prevdir[2000], X[2000], H[2000], in[2000];
    char *Com[2000];
    char buf[2000];
    char te[2000];
    int xps;
    char His[20][2000];
    // Com[1] = 0x0;
    char *Inputs[2000];
    char infg[1000];
    strcpy(infg, in);
    int s = 0, t = 0, x = 0, y;
    int his_count = 0;
    int i = 0, callhis = 0;
    int last = -1;
    int tts = 0;
    gethostname(host, 2000);
    getlogin_r(user, 2000);
    getcwd(H, 2000);
    int count = 0;
    strcpy(buf, H);
    strcat(buf, "/store.txt");
    FILE *fp = fopen(buf, "r");
    if (fp == NULL)
    {
        FILE *fp2;
        fp2 = fopen(buf, "w");
        fclose(fp2);
        fp = fopen(buf, "r");
    }
    while ((fscanf(fp, "%[^\n]%*c", te) != EOF))
    {
        strcpy(His[count], te);
        count++;
    }
    fclose(fp);
    his_count = count;
    while (1)
    {
        s = 0;
        getcwd(prevdir, 2000);
        if (prevdir == NULL)
        {
            perror("Can't read");
        }
        else
        {
            printf("\033[1;34m");
            if (!xps)
            {
                if (strstr(prevdir, H))
                {
                    printf("<%s@%s~%s>", user, host, strlen(H) + strstr(prevdir, H));
                }
                else
                {
                    printf("<%s@%s~%s>", user, host, prevdir);
                }
            }
            else
            {
                if (strstr(prevdir, H))
                {
                    printf("<%s@%s~%s took %ds>", user, host, strlen(H) + strstr(prevdir, H), tts);
                }
                else
                {
                    printf("<%s@%s~%s took %ds>", user, host, prevdir, tts);
                }
                xps = 0;
            }
            printf("\033[0m");
        }
        // fgets(in, 2000, stdin);
        scanf("%[^\n]%*c", in);
        int xp = 0;
        int and = 0;
        callhis++;
        history(in, &his_count, H, His, callhis);
        char kesav[1000];
        strcpy(kesav, in);
        Inputs[s] = strtok(in, ";");
        while (1)
        {
            if (Inputs[s] == NULL)
            {
                break;
            }
            else
            {
                s++;
                Inputs[s] = strtok(NULL, ";");
            }
        }
        x = 0;
        s=s+1;
        while (Inputs[x]!=NULL)
        {
            //printf("%s ",Inputs[x]);
            strcpy(kesav,Inputs[x]);
            t = 0;
            Com[t] = strtok(Inputs[x], "' ','\t','\n'");
            x++;
            while (1)
            {
                if (Com[t] == NULL)
                {
                    break;
                }
                else
                {
                    t++;
                    Com[t] = strtok(NULL, "' ','\t','\n'");
                }
            }
            if (and == 0)
            {
                // printf("hi t is %d\n",t);
                if (strcmp(Com[0], "cd") == 0)
                {
                    if (t == 1)
                    {
                        chdir(H);
                    }
                    else if (t > 2)
                    {
                        perror("Many arguments");
                    }
                    else
                    {
                        cd(Com, H, user);
                    }
                }
                else if (strcmp(Com[0], "echo") == 0)
                {
                    echo(Com, t);
                }
                else if (strcmp(Com[0], "pwd") == 0)
                {
                    pwd(Com);
                }

                else if (strcmp(Com[0], "ls") == 0)
                {
                    if (t == 1)
                    {
                        only_ls(".");
                    }
                    if (t == 2)
                    {
                        ls(Com, H, t);
                    }
                    if (t >= 3)
                    {
                        ls(Com, H, t);
                    }
                }
                else if (strcmp(Com[0], "history") == 0)
                {
                    if (t == 1)
                    {
                        if (his_count >= 10 && his_count < 20)
                        {
                            y = his_count - 10;
                            while (y < his_count)
                            {
                                printf("%s\n", His[y]);
                                y++;
                            }
                        }
                        if (his_count > 20)
                        {
                            y = 10;
                            while (y < 20)
                            {
                                printf("%s\n", His[y]);
                                y++;
                            }
                        }
                        if (his_count < 10)
                        {
                            y = 0;
                            while (y < his_count)
                            {
                                printf("%s\n", His[y]);
                                y++;
                            }
                        }
                    }
                }
                else if (strcmp(Com[0], "exit") == 0)
                {
                    exit(0);
                }
                else if (strcmp(Com[0], "pinfo") == 0)
                {
                    int pid = 0;
                    if (t == 1)
                    {
                        pid = getpid();
                    }
                    pinfo(Com, pid, H);
                }
                else if (strcmp(Com[0], "discover") == 0)
                {
                    discover(Com, t, H);
                }
                else
                {
                    xps = fgbg(kesav, last, tts);
                    tts = times();
                }
            }
        }
    }
}