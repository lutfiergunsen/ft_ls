#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

// Function prototypes
void list_directory(const char *path, int show_all, int long_format, int recursive, int reverse, int sort_time);

void print_long_format(const struct stat *file_stat, const char *file_name);
void print_permissions(mode_t mode, char *str);

int compare_time(const void *a, const void *b);
void swap(void *a, void *b, size_t size);
int partition(void *base, size_t size, int low, int high, int (*compar)(const void *, const void *));
void ft_qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *));

int my_scandir(const char *dir, struct dirent ***namelist);

#endif
