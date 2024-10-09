#include "ls.h"

// Function to compare two file stats based on modification time
int compare_time(const struct stat *a, const struct stat *b) {
    return b->st_mtime - a->st_mtime;
}

// İki elemanı yer değiştirmek için kullanılan yardımcı fonksiyon
void swap(void *a, void *b, size_t size) {
    unsigned char temp[size]; // Geçici bir alan oluştur
    for (size_t i = 0; i < size; i++) {
        temp[i] = ((unsigned char *)a)[i]; // 'a' elemanını geçici alana kopyala
        ((unsigned char *)a)[i] = ((unsigned char *)b)[i]; // 'b' elemanını 'a' elemanına kopyala
        ((unsigned char *)b)[i] = temp[i]; // Geçici alandaki değeri 'b' elemanına kopyala
    }
}

// Diziyi bölmek için kullanılan fonksiyon
int partition(void *base, size_t size, int low, int high, int (*compar)(const void *, const void *)) {
    void *pivot = (char *)base + high * size; // Pivot elemanını son eleman olarak belirle
    int i = low - 1; // Küçük eleman indeksini tutmak için başlat

    // Dizinin elemanlarını pivot ile karşılaştır
    for (int j = low; j < high; j++) {
        if (compar((char *)base + j * size, pivot) < 0) { // Eğer eleman pivot'tan küçükse
            i++; // Küçük eleman indeksini artır
            swap((char *)base + i * size, (char *)base + j * size, size); // Elemanları yer değiştir
        }
    }
    swap((char *)base + (i + 1) * size, (char *)base + high * size, size); // Pivot ile son küçük elemanı yer değiştir
    return i + 1; // Pivot'un yeni indeksini döndür
}

// Hızlı sıralama algoritmasının ana mantığını içeren fonksiyon
void ft_qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    if (num < 2) return; // Sıralanacak eleman yoksa çık

    int low = 0; // Dizi başlangıcı
    int high = num - 1; // Dizi sonu
    int pivot_index; // Pivot indeksini tutmak için

    // Kendi başına sıralama fonksiyonu
    while (low < high) {
        pivot_index = partition(base, size, low, high, compar); // Diziyi böl
        // Recursive olarak sol ve sağ parçaları sıralıyoruz
        ft_qsort(base, pivot_index, size, compar); // Sol parçayı sırala
        low = pivot_index + 1; // Sağ parçayı sırala
    }
}