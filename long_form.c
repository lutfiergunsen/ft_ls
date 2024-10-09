#include "ls.h"

void print_permissions(mode_t mode, char *str) {
    str[0] = (mode & S_IRUSR) ? 'r' : '-';
    str[1] = (mode & S_IWUSR) ? 'w' : '-';
    str[2] = (mode & S_IXUSR) ? 'x' : '-';
    
    str[3] = (mode & S_IRGRP) ? 'r' : '-';
    str[4] = (mode & S_IWGRP) ? 'w' : '-';
    str[5] = (mode & S_IXGRP) ? 'x' : '-';
    // Others permissions
    str[6] = (mode & S_IROTH) ? 'r' : '-';
    str[7] = (mode & S_IWOTH) ? 'w' : '-';
    str[8] = (mode & S_IXOTH) ? 'x' : '-';
    str[9] = '\0';
}

void print_long_format(const struct stat *file_stat, const char *file_name) { // uzun formatta dosya bilgilerini yazdır ls -l
    char time_str[20];
    char perm_str[11];

    struct passwd *pw = getpwuid(file_stat->st_uid);    // kullanıcı bilgilerini al
    struct group *gr = getgrgid(file_stat->st_gid);    // grup bilgilerini al
    
    if (S_ISDIR(file_stat->st_mode)) {  // dosya türüne göre dosya adını yazdır
        perm_str[0] = 'd';
    }
    else if (S_ISLNK(file_stat->st_mode)) {     // sembolik link
        perm_str[0] = 'l';
    }
    else {
        perm_str[0] = '-';
    }
    print_permissions(file_stat->st_mode, perm_str + 1); // izinleri yazdır
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat->st_mtime));  // zamanı yazdır
    printf("%s %4hu %s %s %8lld %s %s\n",
           perm_str,    // izinler
           file_stat->st_nlink, // link sayısı
           pw->pw_name, // kullanıcı adı
           gr->gr_name, // grup adı
           (long long)file_stat->st_size, // dosya boyutu
           time_str,    // değiştirilme zamanı
           file_name);  // dosya adı
}