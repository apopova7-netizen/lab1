#include "Student2.h"


//слияние двух отсортированных подмассивов
void Merge(void *arr, int left, int mid, int right, size_t elemSize,
           int (*cmp)(const void*, const void*),
           long *comparisons, long *swaps, void *tmp) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (comparisons) (*comparisons)++;
        if (cmp(GetElement(arr, i, elemSize), GetElement(arr, j, elemSize)) <= 0) {
            CopyElement(GetElement(tmp, k, elemSize), GetElement(arr, i, elemSize), elemSize);
            i++;
        } else {
            CopyElement(GetElement(tmp, k, elemSize), GetElement(arr, j, elemSize), elemSize);
            j++;
        }
        k++;
    }
    while (i <= mid) {
        CopyElement(GetElement(tmp, k, elemSize), GetElement(arr, i, elemSize), elemSize);
        i++;
        k++;
    }
    while (j <= right) {
        CopyElement(GetElement(tmp, k, elemSize), GetElement(arr, j, elemSize), elemSize);
        j++;
        k++;
    }
    for (i = left; i <= right; i++) {
        CopyElement(GetElement(arr, i, elemSize), GetElement(tmp, i, elemSize), elemSize);
        if (swaps) (*swaps)++;
    }
}

//Оптимизированная версия слияния с использованием memcpy для копирования блоков.
void MergeOptimized(void *arr, int left, int mid, int right, size_t elemSize,
                    int (*cmp)(const void *, const void *),
                    long *comparisons, long *swaps,
                    void *tmp){
    int lenL = mid - left + 1;
    int lenR = right - mid;
    memcpy(GetElement(tmp, 0, elemSize), GetElement(arr, left, elemSize), lenL * elemSize);
    memcpy(GetElement(tmp, lenL, elemSize), GetElement(arr, mid + 1, elemSize), lenR * elemSize);
    int i = 0;       
    int j = lenL;   
    int k = left;    
    int leftDone  = 0;
    int rightDone = 0;

    while (!(leftDone && rightDone)) {
        int takeLeft;
        if (leftDone) {
            takeLeft = 0;
        } else if (rightDone) {
            takeLeft = 1;
        } else {
            if (comparisons) (*comparisons)++;
            takeLeft = cmp(GetElement(tmp, i, elemSize),
                           GetElement(tmp, j, elemSize)) <= 0;
        }
        if (takeLeft) {
            memcpy(GetElement(arr, k, elemSize), GetElement(tmp, i, elemSize), elemSize);
            if (swaps) (*swaps)++;
            i++;
            if (i == lenL) leftDone = 1;
        } else {
            memcpy(GetElement(arr, k, elemSize), GetElement(tmp, j, elemSize), elemSize);
            if (swaps) (*swaps)++;
            j++;
            if (j == lenL + lenR) rightDone = 1;
        }
        k++;
    }
}


// Рекурсивный шаг нисходящей сортировки с оптимизированным слиянием
void MergeSortTopDownHelper(void *arr, int left, int right, size_t elemSize,
                            int (*cmp)(const void*, const void*),
                            long *comparisons, long *swaps, void *tmp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSortTopDownHelper(arr, left, mid, elemSize, cmp, comparisons, swaps, tmp);
        MergeSortTopDownHelper(arr, mid + 1, right, elemSize, cmp, comparisons, swaps, tmp);
        MergeOptimized(arr, left, mid, right, elemSize, cmp, comparisons, swaps, tmp);
    }
}

//Реализация нисходящей (рекурсивной) сортировки слиянием.
void MergeSortTopDown(void *arr, int n, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons, long *swaps) {
    if (n <= 1) return;
    void *tmp = malloc(n * elemSize);
    if (!tmp) return;
    MergeSortTopDownHelper(arr, 0, n - 1, elemSize, cmp, comparisons, swaps, tmp);
    free(tmp);
}

//Реализация восходящей (итеративной) сортировки слиянием.
void MergeSortBottomUp(void *arr, int n, size_t elemSize,
                       int (*cmp)(const void*, const void*),
                       long *comparisons, long *swaps) {
    void *tmp = malloc(n * elemSize);
    if (!tmp) return;

    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid   = left + size - 1;
            int right = left + 2 * size - 1;
            if (right >= n) right = n - 1;
            Merge(arr, left, mid, right, elemSize, cmp, comparisons, swaps, tmp);
        }
    }
    free(tmp);
}

//Выполняет слияние двух отсортированных подмассивов без использования дополнительной памяти (in-place). 
void MergeInPlace(void *arr, int left, int mid, int right, size_t elemSize,
                  int (*cmp)(const void*, const void*),
                  long *comparisons, long *swaps) {
    int start2 = mid + 1;
    if (comparisons) (*comparisons)++;
    if (cmp(GetElement(arr, mid, elemSize),
            GetElement(arr, start2, elemSize)) <= 0) {
        return;
    }
    void *value = malloc(elemSize);
    if (!value) return;

    while (left <= mid && start2 <= right) {
        if (comparisons) (*comparisons)++;
        if (cmp(GetElement(arr, left, elemSize),
                GetElement(arr, start2, elemSize)) <= 0) {
            left++;
        } else {
            CopyElement(value, GetElement(arr, start2, elemSize), elemSize);

            int index = start2;
            while (index != left) {
                CopyElement(GetElement(arr, index, elemSize),
                            GetElement(arr, index - 1, elemSize), elemSize);
                index--;
                if (swaps) (*swaps)++;
            }

            CopyElement(GetElement(arr, left, elemSize), value, elemSize);

            left++;
            mid++;
            start2++;
        }
    }

    free(value);
}

//Рекурсивная сортировка слиянием без использования дополнительной памяти.
void MergeSortInPlace(void *arr, int left, int right, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons, long *swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSortInPlace(arr, left, mid, elemSize, cmp, comparisons, swaps);
        MergeSortInPlace(arr, mid + 1, right, elemSize, cmp, comparisons, swaps);
        MergeInPlace(arr, left, mid, right, elemSize, cmp, comparisons, swaps);
    }
}


// Находит конец текущего отсортированного рана
int FindRunEnd(void *arr, int start, int n, size_t elemSize,
               int (*cmp)(const void*, const void*),
               long *comparisons) {
    int end = start + 1;
    while (end < n) {
        if (comparisons) (*comparisons)++;
        if (cmp(GetElement(arr, end - 1, elemSize),
                GetElement(arr, end, elemSize)) > 0) {
            return end - 1;
        }
        end++;
    }
    return n - 1;
}

//Реализация естественной сортировки слиянием (natural merge sort).
void MergeSortNatural(void *arr, int n, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons, long *swaps) {
    void *tmp = malloc(n * elemSize);
    if (!tmp) return;
    while (1) {
        int merged = 0;
        int i = 0;
        while (i < n) {
            int run1Start = i;
            int run1End   = FindRunEnd(arr, run1Start, n, elemSize, cmp, comparisons);

            if (run1End >= n - 1) break;

            int run2Start = run1End + 1;
            int run2End   = FindRunEnd(arr, run2Start, n, elemSize, cmp, comparisons);

            Merge(arr, run1Start, run1End, run2End, elemSize,
                  cmp, comparisons, swaps, tmp);

            i = run2End + 1;
            merged = 1;
        }

        if (!merged) break;
    }

    free(tmp);
}

//Основная функция сортировки слиянием (обертка над MergeSortTopDown).
void MergeSort(void *arr, int n, size_t elem_size,
               int (*cmp)(const void*, const void*),
               long *comparisons, long *swaps) {
    MergeSortTopDown(arr, n, elem_size, cmp, comparisons, swaps);
}
