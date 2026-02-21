#include "Student2.h" 

// Копирование одного элемента
void CopyElement(void *dest, const void *src, size_t elemSize) {
    memcpy(dest, src, elemSize);
}

// Обмен двух элементов
void Swap(void *a, void *b, size_t elemSize, long *swaps) {
    unsigned char tmp[elemSize];
    memcpy(tmp, a, elemSize);
    memcpy(a, b, elemSize);
    memcpy(b, tmp, elemSize);
    if (swaps) (*swaps)++;
}

// Получение указателя на элемент массива
void* GetElement(void *arr, int index, size_t elemSize) {
    return (unsigned char*)arr + index * elemSize;
}

// Функция сравнения для целых чисел
int CompareInt(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}


