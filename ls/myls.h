#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <getopt.h>
#include <error.h>

#define MAX_PATH 1024
#define MAX_FILE 512
#define MAX_RFILE 60000

enum order {
    a, s, t, r, I, l, R
};

struct fileinfo
{
    unsigned int i_node;
    char permission[16];
    short owner;
    short group;
    off_t size;
    time_t c_ctime;
    time_t m_ctime;
    nlink_t link_num;
    char name[MAX_PATH];
    mode_t mode;
    blkcnt_t block;
};

void do_open(char *path, int orders[]);
void ls_a(char *path, struct fileinfo *infos, int *count);
void only_ls(char *path, struct fileinfo *infos, int *count);
void mode_to_letters(mode_t mode, char modestr[]);
int cmp_name(const void *a, const void *b);
int cmp_time(const void *a, const void *b);
int cmp_size(const void *a, const void *b);
void show_orders(struct fileinfo *infos, int count, int orders[]);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void do_open_R(char *path, int orders[]);
void print(struct fileinfo infos);