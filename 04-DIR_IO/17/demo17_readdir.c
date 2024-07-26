#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int ret;
    DIR *dp;
    struct dirent *dir;  
    if(argc != 2)
    {
        printf("Usage: %s <name file>\n", argv[0]);
        return -1;
    }
    dp = opendir(argv[1]);
    if(dp == NULL)
    {
        perror("opendir is eeror\n");
        return -2;
    }
    printf("opendir is ok\n");

    while(1)
    {
        dir = readdir(dp);
        if(dir != NULL)
        {
            printf("file name is %s\n", dir->d_name);
        }
        else
            break;
    }

    closedir(dp);
    return 0;
}