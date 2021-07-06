#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_PATH_LEN (10001)

static void trave_dir(char* path)
{
    DIR *d = NULL;
    struct dirent *dp = NULL; /* readdir函数的返回值就存放在这个结构体中 */
    struct stat st;    
    char p[MAX_PATH_LEN] = {0};
    
    if(stat(path, &st) < 0 || !S_ISDIR(st.st_mode))
    {
        printf("invalid path: %s\n", path);
        return;
    }

    if(!(d = opendir(path)))
    {
        printf("opendir[%s] error: %m\n", path);
        return;
    }

    while((dp = readdir(d)) != NULL)
    {
        /* 把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录 */
        if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
            continue;
        snprintf(p, sizeof(p) - 1, "%s/%s", path, dp->d_name);
        stat(p, &st);
        if(!S_ISDIR(st.st_mode))
        {
            FILE *fp = NULL;    //输入 
            FILE *fq = NULL;    //输出 
            //char filename_body[10];
            char filename[10001];
            strcpy(filename, path);
            strcat(filename, "/");
            char filename_tail[10001];
            strcpy(filename_tail, dp->d_name);
            strcat(filename, filename_tail);
            if ((fp = fopen(filename, "r")) == NULL)
            {
                printf ("open filename fail...\n");
            }
            char str[1000001];
            int pin = 0;
            char ch;
            while (fscanf(fp, "%c", &ch) != EOF)
            {
                memset (str, 0, sizeof (str));
                pin = 0;
                while(ch != '\n')
                {
                    str[pin++] = ch;
                    if (fscanf(fp, "%c", &ch) == EOF) break;
                }
                puts(str);
            }
            /*while (fscanf(fp, "%s", str) != EOF)
            {
                printf ("%s\n", str);
            }*/
    
            fclose(fp);
        }
        else
        {
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
 
    if (argc != 2)
    {
        printf("Usage: %s [dir]\n", argv[0]);
        printf("use DEFAULT option: %s .\n", argv[0]);
        printf("-------------------------------------------\n");
        char dir[10001];
        printf ("Enter a directory: ");
        gets(dir, stdin);
        path = dir;
    }
    else
    {
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
