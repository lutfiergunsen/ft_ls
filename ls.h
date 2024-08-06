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

#endif
