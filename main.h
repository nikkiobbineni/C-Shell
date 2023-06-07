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
void cd(char *C[], char H[], char U[]);
void echo(char *C[], int w);
void pwd(char *C[]);
void ls(char *C[], char H[],int times);
void only_ls(char H[]);
void history(char in[2000], int *count, char H[], char his_array[20][2000], int call);
void pinfo(char *C[],int pid,char H[]);
void discover(char *paths[],int times,char H[]);
void printing(char *command, int xyz, char H[], int hans, int file, char *files);
int fgbg(char in[],int xyz,int pqr);
int times();
void bg();