#include "Student2.h"

/* Выбираем pivot как медиану из первого, среднего и последнего */
int MedianOfThree(void *arr, int left, int right, size_t elemSize,
                  int (*cmp)(const void*, const void*),
                  long *comparisons, long *swaps) {
    int mid = left + (right - left) / 2;
    if (cmp(GetElement(arr, left, elemSize), 
            GetElement(arr, mid, elemSize)) > 0) {
        Swap(GetElement(arr, left, elemSize), 
             GetElement(arr, mid, elemSize), elemSize, swaps);
    }
    if (comparisons) (*comparisons)++;
    
    if (cmp(GetElement(arr, left, elemSize),
            GetElement(arr, right, elemSize)) > 0) {
        Swap(GetElement(arr, left, elemSize),
                    GetElement(arr, right, elemSize), elemSize, swaps);
    }
    if (comparisons) (*comparisons)++;
    
    if (cmp(GetElement(arr, mid, elemSize),
            GetElement(arr, right, elemSize)) > 0) {
        Swap(GetElement(arr, mid, elemSize),
                    GetElement(arr, right, elemSize), elemSize, swaps);
    }
    if (comparisons) (*comparisons)++;
    
    return mid;
}

/* Функция разделения массива относительно опорного элемента */
int Partition(void *arr, int left, int right, size_t elemSize,
              int (*cmp)(const void*, const void*),
              long *comparisons, long *swaps) {
    int pivotIndex = MedianOfThree(arr, left, right, elemSize, cmp, comparisons, swaps);
    Swap(GetElement(arr, pivotIndex, elemSize),
         GetElement(arr, right, elemSize), elemSize, swaps);

    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (comparisons) (*comparisons)++;
        if (cmp(GetElement(arr, i, elemSize),
                GetElement(arr, right, elemSize)) <= 0) {
            Swap(GetElement(arr, i, elemSize),
                 GetElement(arr, storeIndex, elemSize),
                 elemSize, swaps);
            storeIndex++;
        }
    }
    Swap(GetElement(arr, storeIndex, elemSize),
         GetElement(arr, right, elemSize),
         elemSize, swaps);
    
    return storeIndex;
}


/* Рекурсивная функция интроспективной сортировки с контролем глубины */
void IntrosortRecursive(void *arr, int left, int right,
                        int depthLimit, size_t elemSize,
                        int (*cmp)(const void*, const void*),
                        long *comparisons, long *swaps) {
    int curSize = right - left + 1;
    if (curSize <= K_INSERTION_SORT_THRESHOLD) {
        InsertionSort2(GetElement(arr, left, elemSize), 0, curSize - 1,
                      elemSize, cmp, comparisons, swaps);
        return;
    }
    if (depthLimit == 0) {
        HeapSort(GetElement(arr, left, elemSize), curSize,
                 elemSize, cmp, comparisons, swaps);
        return;
    }
    int pivotPos = Partition(arr, left, right, elemSize, 
                                   cmp, comparisons, swaps);
    IntrosortRecursive(arr, left, pivotPos - 1, depthLimit - 1,
                       elemSize, cmp, comparisons, swaps);
    IntrosortRecursive(arr, pivotPos + 1, right, depthLimit - 1,
                       elemSize, cmp, comparisons, swaps);
}

/* Интроспективная сортировка (Introsort) - адаптивный гибрид */
void IntroSort(void *arr, int n, size_t elemSize,
               int (*cmp)(const void*, const void*),
               long *comparisons, long *swaps) {
    if (arr == NULL || n <= 0 || elemSize == 0 || cmp == NULL) return;
    if (n <= 1) return;
    int depthLimit = 2 * (int)log2((double)n);
    IntrosortRecursive(arr, 0, n - 1, depthLimit,
                       elemSize, cmp, comparisons, swaps);
}