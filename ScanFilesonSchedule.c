#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_PATH_LEN (256)

static void trave_dir(char* path) {
    DIR *d = NULL;
    struct dirent *dp = NULL; /* readdir函数的返回值就存放在这个结构体中 */
    struct stat st;    
    char p[MAX_PATH_LEN] = {0};
    
    if(stat(path, &st) < 0 || !S_ISDIR(st.st_mode)) {
        printf("invalid path: %s\n", path);
        return;
    }

    if(!(d = opendir(path))) {
        printf("opendir[%s] error: %m\n", path);
        return;
    }

    while((dp = readdir(d)) != NULL) {
        /* 把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录 */
        if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
            continue;

        snprintf(p, sizeof(p) - 1, "%s/%s", path, dp->d_name);
        stat(p, &st);
        if(!S_ISDIR(st.st_mode)) {
            printf("%s\n", dp->d_name);
        } else {
            printf("%s/\n", dp->d_name);
            trave_dir(p);
        }
    }
    closedir(d);

    return;
}

int main(int argc, char **argv)
{   
    char *path = NULL;
 
    if (argc != 2) {
        printf("Usage: %s [dir]\n", argv[0]);
        printf("use DEFAULT option: %s .\n", argv[0]);
        printf("-------------------------------------------\n");
        char dir[200];
        printf ("Enter a directory: ");
        gets(dir, stdin);
        path = dir;
    } else {
        path = argv[1];
    }
    int cnt = 0;
    int duration = 5;
    if(duration<=0) exit(1);
    //设置启动时间
    time_t start, current;
    printf("开始时间:%s \n",ctime(&start));
    while (++cnt)
        {
            printf("第%d次扫描\n", cnt);
            trave_dir(path);
            time(&start);
            do
            {
                //设置当前时间
                time(&current);
            } while ((current - start) != duration);
            printf("\n\n");
        }

    return 0;
}
