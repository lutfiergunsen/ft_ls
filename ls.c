#include "ls.h"

// Function to list a directory
void list_directory(const char *path, int show_all, int long_format, int recursive, int reverse, int sort_time) {   // dizin listeleme fonksiyonu
    struct dirent **namelist;   // dizin içeriğini tutan struct
    int n = my_scandir(path, &namelist);  // dizin içeriğini al
    if (n < 0) {    // hata kontrolü
        perror("scandir");
        return;
    }

    // Array to hold file stats
    struct stat *file_stats = malloc(n * sizeof(struct stat));  // dosya istatistiklerini tutan struct
    for (int i = 0; i < n; i++) {   
        char full_path[1024];   
        snprintf(full_path, sizeof(full_path), "%s/%s", path, namelist[i]->d_name); // dosya yolunu oluştur
        stat(full_path, &file_stats[i]);    // dosya istatistiklerini al
    }

    // Sort by time if requested
    if (sort_time) {    // zaman sıralaması
        ft_qsort(file_stats, n, sizeof(struct stat), (int (*)(const void *, const void *))compare_time);
        printf("-t çalıştı gibi\n");
    }

    for (int i = 0; i < n; i++) {   // dosya adlarını yazdır
        struct dirent *entry = namelist[i]; 
        if (!show_all && entry->d_name[0] == '.') continue;     // gizli dosyaları gösterme
        if (long_format) {  // uzun formatta yazdırma
            print_long_format(&file_stats[i], entry->d_name);
        } else { 
            printf("%s\n", entry->d_name);
        }
        if (recursive && entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {      // recursive olarak dizinleri yazdırma 
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name); // yeni yol oluştur
            printf("\n%s:\n", new_path);        // yeni dizin adını yazdır
            list_directory(new_path, show_all, long_format, recursive, reverse, sort_time); // yeni dizini yazdır
        }
    }

    free(file_stats);
    for (int i = 0; i < n; i++) {
        free(namelist[i]);
    }
    free(namelist);
}

// Function to parse options
void parse_options(int argc, char **argv, int *show_all, int *long_format, int *recursive, int *reverse, int *sort_time) {
    int opt;
    while ((opt = getopt(argc, argv, "alRrt")) != -1) {
        switch (opt) {
            case 'a':
                *show_all = 1;
                break;
            case 'l':
                *long_format = 1;
                break;
            case 'R':
                *recursive = 1;
                break;
            case 'r':
                *reverse = 1;
                break;
            case 't':
                *sort_time = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-alRrt] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char **argv) {
    int show_all = 0, long_format = 0, recursive = 0, reverse = 0, sort_time = 0;
    parse_options(argc, argv, &show_all, &long_format, &recursive, &reverse, &sort_time);
    
    if (optind >= argc) {   
        list_directory(".", show_all, long_format, recursive, reverse, sort_time);
    } else {
        for (int i = optind; i < argc; i++) {   // dosya adlarını yazdır
            printf("%s:\n", argv[i]);   
            list_directory(argv[i], show_all, long_format, recursive, reverse, sort_time);  
        }
    }
    return 0;
}
