#include "myls.h"

void do_open(char *path, int orders[])
{
    int count = 0;
    struct fileinfo infos[MAX_FILE];
    if (orders[a])
    {
        ls_a(path, infos, &count);
    }
    if (orders[a] == 0)
    {
        only_ls(path, infos, &count);
    }
    if (orders[t])
    {
        qsort(infos, count, sizeof(struct fileinfo), cmp_time);
    }
    if ((orders[s] == 1) && (orders[t] == 0))
    {
        qsort(infos, count, sizeof(struct fileinfo), cmp_size);
    }
    if ((orders[s] == 0) && orders[t] == 0)
    {
        qsort(infos, count, sizeof(struct fileinfo), cmp_name);
    }
    show_orders(infos, count, orders);
}

void do_open_R(char *path, int orders[])
{
    int count = 0;
    struct fileinfo *infos = (struct fileinfo *)malloc(sizeof(struct fileinfo) * MAX_RFILE);
    if (infos == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (orders[a])
    {
        ls_a(path, infos, &count);
    }
    if (orders[a] == 0)
    {
        only_ls(path, infos, &count);
    }
    if (orders[t])
    {
        qsort(infos, count, sizeof(struct fileinfo), cmp_time);
    }
    if ((orders[s] == 1) && (orders[t] == 0))
    {
        qsort(infos, count, sizeof(struct fileinfo), cmp_size);
    }
    if ((orders[s] == 0) && orders[t] == 0)
    {
        qsort(infos, count, sizeof(struct fileinfo), cmp_name);
    }
    show_orders(infos, count, orders);
    for (int i = 0; i < count; i++)
    {
        if (S_ISDIR(infos[i].mode) && strcmp(infos[i].name, ".") != 0 && strcmp(infos[i].name, "..") != 0)
        {
            char sub_path[MAX_PATH];
            snprintf(sub_path, sizeof(sub_path), "%s/%s", path, infos[i].name);
            struct stat flag;
            if (lstat(sub_path, &flag) == -1)
            {
                fprintf(stderr, "Permission denied or error reading: %s\n", sub_path);
                continue;
            }
            if(S_ISLNK(flag.st_mode))
            {
                continue;
            }
            do_open_R(sub_path,orders);
        }
    }
    free(infos);
}


void ls_a(char *path, struct fileinfo *infos, int *count)
{
    DIR *dir;
    struct dirent *dirp;
    if ((dir = opendir(path)) == NULL)
    {
        printf("%s\n", path);
        return ;
    }
    *count = 0;
    struct stat st;
    while ((dirp = readdir(dir)) != NULL)
    {
        char current_path[MAX_PATH];
        snprintf(current_path, sizeof(current_path), "%s/%s", path, dirp->d_name);
        
        if ((stat(current_path, &st)) != -1)
        {
            
            strncpy(infos[*count].name, dirp->d_name, sizeof(infos[*count].name) - 1);
            infos[*count].name[sizeof(infos[*count].name) - 1] = '\0';  // Null-terminate the string
            infos[*count].group = st.st_gid;
            infos[*count].owner = st.st_uid;
            infos[*count].mode = st.st_mode;
            infos[*count].c_ctime = st.st_ctime;
            infos[*count].size = st.st_size;
            infos[*count].m_ctime = st.st_mtime;
            infos[*count].i_node = st.st_ino;
            mode_to_letters(st.st_mode, infos[*count].permission);
            infos[*count].link_num = st.st_nlink;
            infos[*count].block=st.st_blocks;
        }
        else
        {
            perror("stat");
            continue;
        }
        (*count)++;
    }
    closedir(dir);//一定要记得关闭文件
}


void only_ls(char *path, struct fileinfo *infos, int *count)
{
    DIR *dir;
    struct dirent *dirp;
    if ((dir = opendir(path)) == NULL)
    {
        printf("%s\n", path);
        return ;
    }
    *count = 0;
    struct stat st;
    while ((dirp = readdir(dir)) != NULL)
    {
        if (dirp->d_name[0] != '.')
        {
            char current_path[MAX_PATH];
            snprintf(current_path, sizeof(current_path), "%s/%s", path, dirp->d_name);
            if ((stat(current_path, &st)) != -1)
            {
                snprintf(infos[*count].name, sizeof(infos[*count].name), "%s", dirp->d_name);
                infos[*count].group = st.st_gid;
                infos[*count].owner = st.st_uid;
                infos[*count].mode = st.st_mode;
                infos[*count].c_ctime = st.st_ctime;
                infos[*count].size = st.st_size;
                infos[*count].m_ctime = st.st_mtime;
                infos[*count].i_node = st.st_ino;
                mode_to_letters(st.st_mode, infos[*count].permission);
                infos[*count].link_num = st.st_nlink;
                infos[*count].block = st.st_blocks;
            }
            (*count)++;
        }
    }
    closedir(dir);//一定要记得及时释放
}

void mode_to_letters(mode_t mode, char modestr[]) {
    strcpy(modestr, "----------");
    if (S_ISDIR(mode)) modestr[0] = 'd';
    if (S_ISCHR(mode)) modestr[0] = 'c';
    if (S_ISBLK(mode)) modestr[0] = 'b';

    if (mode & S_IRUSR) modestr[1] = 'r';
    if (mode & S_IWUSR) modestr[2] = 'w';
    if (mode & S_IXUSR) modestr[3] = 'x';

    if (mode & S_IRGRP) modestr[4] = 'r';
    if (mode & S_IWGRP) modestr[5] = 'w';
    if (mode & S_IXGRP) modestr[6] = 'x';

    if (mode & S_IROTH) modestr[7] = 'r';
    if (mode & S_IWOTH) modestr[8] = 'w';
    if (mode & S_IXOTH) modestr[9] = 'x';
}

int cmp_name(const void *a, const void *b)
{
    const char *name_a = ((struct fileinfo *)a)->name;
    const char *name_b = ((struct fileinfo *)b)->name;
    setlocale(LC_COLLATE, "");
    return strcoll(name_a, name_b);
}

int cmp_size(const void *a, const void *b)
{
    off_t size_a = ((struct fileinfo *)a)->size;
    off_t size_b = ((struct fileinfo *)b)->size;
    return size_a > size_b ? (size_a < size_b ? -1 : 0) : 1;
}

int cmp_time(const void *a, const void *b)
{
    time_t time_a = ((struct fileinfo *)a)->m_ctime;
    time_t time_b = ((struct fileinfo *)b)->m_ctime;
    return time_a > time_b ? (time_a < time_b ? -1 : 0) : 1;
}

void show_orders(struct fileinfo *infos, int count, int orders[])
{
    long long total = 0;
    if(orders[l])
    {
        for(int i = 0; i < count; i++)
        {
            total+=infos[i].block/2;
        }
        printf("总计 : %-11ld\n", total);
    }
    if (orders[r])
    {
        for (int i = count - 1; i >= 0; i--)
        {
            if (orders[I])
            {
                printf("%-8d", infos[i].i_node);
            }
            if (orders[l])
            {
                printf("%s ", infos[i].permission);
                printf("%4d ", (int)infos[i].link_num);
                printf("%-8s ", uid_to_name(infos[i].owner));
                printf("%-8s ", gid_to_name(infos[i].group));
                printf("%8ld ", infos[i].size);
                printf("%.12s ", ctime(&infos[i].c_ctime) + 4);
            }
            print(infos[i]);
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (orders[I])
            {
                printf("%-8d", infos[i].i_node);
            }
            if(orders[s])
            {
                printf("%-8d", infos[i].block/2);
            }
            if (orders[l])
            {
                printf("%s ", infos[i].permission);
                printf("%4d ", (int)infos[i].link_num);
                printf("%-8s ", uid_to_name(infos[i].owner));
                printf("%-8s ", gid_to_name(infos[i].group));
                printf("%8ld ", infos[i].size);
                printf("%.12s ", ctime(&infos[i].c_ctime) + 4);
            }
            print(infos[i]);
        }
    }
}

char *uid_to_name(uid_t uid)
{
    struct passwd *pw_ptr;
    pw_ptr = getpwuid(uid);
    if (pw_ptr == NULL)
    {
        static char numstr[10];
        snprintf(numstr, sizeof(numstr), "%d", uid);
        return numstr;
    }
    else
    {
        return pw_ptr->pw_name;
    }
}

char *gid_to_name(gid_t gid)
{
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];
    if ((grp_ptr = getgrgid(gid)) == NULL)
    {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
    {
        return grp_ptr->gr_name;
    }
}

void print(struct fileinfo infos)
{
    if (S_ISREG(infos.mode))
    {
        // Regular file
        if (strstr(infos.name, ".c") != NULL)
        {
            // .c file, print in a different color
            printf("\033[40;32m %s\033[0m\n", infos.name);
        }
        else if (strstr(infos.name, ".out") != NULL)
        {
            // .out file, print in another color
            printf("\033[40;33m %s\033[0m\n", infos.name);
        }
        else
        {
            // Other regular file
            printf("%s\n", infos.name);
        }
    }
    else if (S_ISDIR(infos.mode))
    {
        // Directory
        printf("\033[40;34m %s\033[0m\n", infos.name);
    }
    else
    {
        // Other file types
        printf("%s\n", infos.name);
    }
}