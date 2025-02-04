#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <locale.h>

#define COLOR_RESET "\x1B[0m"
#define COLOR_DIR "\x1B[34m"
#define COLOR_LINK "\x1B[36m"
#define COLOR_EXE "\x1B[32m"

typedef struct {
    int a, l, R, t, r, i, s;
    int dir_count;  // 需要显示目录名的目录数量
} Options;

typedef struct {
    char *path;
    struct stat st;
} Entry;

// 新增比较函数：按文件名排序
int compare_name(const void *a, const void *b) {
    const Entry *ea = a;
    const Entry *eb = b;
    const char *name_a = strrchr(ea->path, '/') ? strrchr(ea->path, '/') + 1 : ea->path;
    const char *name_b = strrchr(eb->path, '/') ? strrchr(eb->path, '/') + 1 : eb->path;
    return strcoll(name_a, name_b);
}

const char* get_color(const char *path) {
    struct stat st;
    if (lstat(path, &st) == -1) return COLOR_RESET;

    if (S_ISLNK(st.st_mode)) return COLOR_LINK;
    if (S_ISDIR(st.st_mode)) return COLOR_DIR;
    if (st.st_mode & S_IXUSR) return COLOR_EXE;
    return COLOR_RESET;
}

char* mode_to_str(mode_t mode, char *str) {
    strcpy(str, "----------");
    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISLNK(mode)) str[0] = 'l';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';
    if (S_ISFIFO(mode)) str[0] = 'p';
    if (S_ISSOCK(mode)) str[0] = 's';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
    return str;
}

int compare_entries(const void *a, const void *b) {
    const Entry *ea = a, *eb = b;
    if (ea->st.st_mtime == eb->st.st_mtime)
        return strcoll(ea->path, eb->path);
    return (ea->st.st_mtime > eb->st.st_mtime) ? -1 : 1;
}

void print_entry(const char *path, const char *name, Options opts) {
    struct stat st;
    if (lstat(path, &st) == -1) return;

    if (opts.i) printf("%8lu ", st.st_ino);
    if (opts.s) printf("%4ld ", st.st_blocks/2);

    if (opts.l) {
        char modestr[11];
        mode_to_str(st.st_mode, modestr);
        printf("%s %2ld %-8s %-8s %8ld ",
               modestr,
               st.st_nlink,
               getpwuid(st.st_uid)->pw_name,
               getgrgid(st.st_gid)->gr_name,
               st.st_size);

        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));
        printf("%s ", timebuf);
    }

    const char *color = get_color(path);
    printf("%s%s%s", color, name, COLOR_RESET);

    if (opts.l && S_ISLNK(st.st_mode)) {
        char linkbuf[PATH_MAX];
        ssize_t len = readlink(path, linkbuf, sizeof(linkbuf)-1);
        if (len != -1) {
            linkbuf[len] = '\0';
            printf(" -> %s", linkbuf);
        }
    }
    putchar('\n');
}

void process_path(const char *path, Options opts, int is_explicit_dir);

void process_dir(const char *dirpath, Options opts, int is_explicit_dir) {
    if (opts.dir_count++ > 0) putchar('\n');
    if (is_explicit_dir) printf("%s:\n", dirpath);

    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror(dirpath);
        return;
    }

    Entry *entries = NULL;
    int count = 0;
    struct dirent *ent;

    while ((ent = readdir(dir)) != NULL) {
        if (!opts.a && ent->d_name[0] == '.') continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, ent->d_name);

        entries = realloc(entries, (count+1)*sizeof(Entry));
        entries[count].path = strdup(fullpath);
        lstat(fullpath, &entries[count].st);
        count++;
    }
    closedir(dir);

    if (opts.t) {
        qsort(entries, count, sizeof(Entry), compare_entries);
    } 
    else {
        qsort(entries, count, sizeof(Entry), compare_name);
    }
    if (opts.r) {
        for (int i = 0; i < count/2; i++) {
            Entry tmp = entries[i];
            entries[i] = entries[count-1-i];
            entries[count-1-i] = tmp;
        }
    }

    for (int i = 0; i < count; i++) {
        char *name = strrchr(entries[i].path, '/') + 1;
        print_entry(entries[i].path, name, opts);
    }

    if (opts.R) {
        for (int i = 0; i < count; i++) {
            if (S_ISDIR(entries[i].st.st_mode) && 
                strcmp(entries[i].path + strlen(dirpath)+1, ".") != 0 &&
                strcmp(entries[i].path + strlen(dirpath)+1, "..") != 0) {
                process_path(entries[i].path, opts, 1);
            }
        }
    }

    for (int i = 0; i < count; i++) free(entries[i].path);
    free(entries);
}

void process_file(const char *path, Options opts) {
    print_entry(path, path, opts);
}

void process_path(const char *path, Options opts, int is_explicit_dir) {
    struct stat st;
    if (lstat(path, &st) == -1) {
        perror(path);
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        process_dir(path, opts, is_explicit_dir);
    } else {
        process_file(path, opts);
    }
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    Options opts = {0};
    char **paths = NULL;
    int path_count = 0;

    // 参数解析
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char *p = argv[i] + 1;
            while (*p) {
                switch (*p) {
                    case 'a': opts.a = 1; break;
                    case 'l': opts.l = 1; break;
                    case 'R': opts.R = 1; break;
                    case 't': opts.t = 1; break;
                    case 'r': opts.r = 1; break;
                    case 'i': opts.i = 1; break;
                    case 's': opts.s = 1; break;
                    default: 
                        fprintf(stderr, "无效选项: -%c\n", *p);
                        exit(EXIT_FAILURE);
                }
                p++;
            }
        } 
        else {
            paths = realloc(paths, (path_count+1)*sizeof(char*));
            paths[path_count++] = argv[i];
        }
    }

    // 默认处理当前目录
    if (path_count == 0) {
        paths = realloc(paths, sizeof(char*));
        paths[path_count++] = ".";
    }

    // 处理多个路径
    opts.dir_count = 0;
    for (int i = 0; i < path_count; i++) {
        process_path(paths[i], opts, path_count > 1);
    }

    free(paths);
    return 0;
}