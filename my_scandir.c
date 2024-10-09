#include "ls.h"

int my_scandir(const char *dir, struct dirent ***namelist) {
    DIR *d;
    struct dirent *entry;
    int count = 0;
    int capacity = 10; // Başlangıç kapasitesi

    // Bellekte yer ayır
    *namelist = malloc(capacity * sizeof(struct dirent *));
    if (*namelist == NULL) {
        perror("malloc");
        return -1; // Hata durumunda -1 döndür
    }

    d = opendir(dir); // Dizin açma
    if (!d) {
        perror("opendir");
        free(*namelist); // Belleği serbest bırak
        return -1; // Hata durumunda -1 döndür
    }

    // Dizin içeriğini oku
    while ((entry = readdir(d)) != NULL) {
        // Kapasite kontrolü
        if (count >= capacity) {
            capacity *= 2; // Kapasiteyi iki katına çıkar
            *namelist = realloc(*namelist, capacity * sizeof(struct dirent *)); // Belleği genişlet
            if (*namelist == NULL) {
                perror("realloc");
                closedir(d);
                return -1; // Hata durumunda -1 döndür
            }
        }

        // Yeni bir dirent için bellek ayır
        (*namelist)[count] = malloc(sizeof(struct dirent)); 
        if ((*namelist)[count] == NULL) {
            perror("malloc");
            closedir(d);
            return -1; // Hata durumunda -1 döndür
        }
        
        memcpy((*namelist)[count], entry, sizeof(struct dirent)); // Giriş yapısını kopyala
        count++; // Giriş sayısını artır
    }

    closedir(d); // Dizin kapat
    return count; // Toplam giriş sayısını döndür
}