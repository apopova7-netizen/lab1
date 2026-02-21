#include "Student2.h"


// Оптимизированная версия просеивания с использованием "дырки"
void SiftDownOptimized(void *arr, int n, int i, size_t elemSize,
                       int (*cmp)(const void*, const void*),
                       long *comparisons, long *swaps) {
    void *tmp = malloc(elemSize);
    CopyElement(tmp, GetElement(arr, i, elemSize), elemSize); 
    int hole = i;
    
    while (2 * hole + 1 < n) {
        int left = 2 * hole + 1;
        int right = 2 * hole + 2;
        int larger = left;
        
        if (right < n) {
            if (comparisons) (*comparisons)++;
            if (cmp(GetElement(arr, right, elemSize), 
                    GetElement(arr, left, elemSize)) > 0) {
                larger = right;
            }
        }
        
        if (comparisons) (*comparisons)++;
        if (cmp(tmp, GetElement(arr, larger, elemSize)) >= 0) {
            break;
        }
        
        CopyElement(GetElement(arr, hole, elemSize), 
                   GetElement(arr, larger, elemSize), elemSize);
        if (swaps) (*swaps)++;
        hole = larger;
    }
    
    if (hole != i) {
        CopyElement(GetElement(arr, hole, elemSize), tmp, elemSize);
    }
    
    free(tmp);
}

// Функция построения максимальной кучи из массива
void BuildMaxHeap(void *arr, int n, size_t elemSize,
                  int (*cmp)(const void*, const void*),
                  long *comparisons, long *swaps) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        SiftDownOptimized(arr, n, i, elemSize, cmp, comparisons, swaps);
    }
}

// Основная функция пирамидальной сортировки (Heap Sort)
void HeapSort(void *arr, int n, size_t elemSize,
              int (*cmp)(const void*, const void*),
              long *comparisons, long *swaps) {
    if (n <= 1) return;
    BuildMaxHeap(arr, n, elemSize, cmp, comparisons, swaps);
    for (int i = n - 1; i > 0; i--) {
        Swap(GetElement(arr, 0, elemSize), 
             GetElement(arr, i, elemSize), 
             elemSize, swaps);
        SiftDownOptimized(arr, i, 0, elemSize, cmp, comparisons, swaps);
    }
}


































