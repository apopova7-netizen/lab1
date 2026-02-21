#include "Student2.h"

//Находит естественно упорядоченный участок (run) в массиве и при необходимости разворачивает убывающие последовательности
int FindRun(void *arr, int start, int n, size_t elemSize,
            int (*cmp)(const void *, const void *),
            long *comparisons, long *swaps) {
    if (start + 1 >= n) return start;

    if (comparisons) (*comparisons)++;
    int end = start + 1;

    if (cmp(GetElement(arr, start, elemSize),
            GetElement(arr, end, elemSize)) > 0) {
        while (end + 1 < n) {
            if (comparisons) (*comparisons)++;
            if (cmp(GetElement(arr, end, elemSize),
                    GetElement(arr, end + 1, elemSize)) > 0)
                end++;
            else
                break;
        }
        int i = start, j = end;
        while (i < j) {
            Swap(GetElement(arr, i, elemSize),
                 GetElement(arr, j, elemSize),
                 elemSize, swaps);
            i++; j--;
        }
    } else {
        while (end + 1 < n) {
            if (comparisons) (*comparisons)++;
            if (cmp(GetElement(arr, end, elemSize),
                    GetElement(arr, end + 1, elemSize)) <= 0)
                end++;
            else
                break;
        }
    }

    return end;
}


//Слияние двух отсортированных участков (run'ов) массива
void MergeRuns(void *arr, int left, int mid, int right, size_t elemSize,
               int (*cmp)(const void *, const void *),
               long *comparisons, long *swaps) {
    int leftLen  = mid - left + 1;
    int rightLen = right - mid;

    void *leftBuf  = malloc(leftLen  * elemSize);
    void *rightBuf = malloc(rightLen * elemSize);
    if (!leftBuf || !rightBuf) {
        free(leftBuf);
        free(rightBuf);
        return;
    }

    memcpy(leftBuf,  GetElement(arr, left, elemSize), leftLen  * elemSize);
    memcpy(rightBuf, GetElement(arr, mid + 1, elemSize), rightLen * elemSize);

    int i = 0, j = 0, k = left;

    while (i < leftLen && j < rightLen) {
        if (comparisons) (*comparisons)++;
        if (cmp(GetElement(leftBuf,  i, elemSize),
                GetElement(rightBuf, j, elemSize)) <= 0) {
            memcpy(GetElement(arr, k, elemSize),
                   GetElement(leftBuf, i, elemSize), elemSize);
            if (swaps) (*swaps)++;
            i++;
        } else {
            memcpy(GetElement(arr, k, elemSize),
                   GetElement(rightBuf, j, elemSize), elemSize);
            if (swaps) (*swaps)++;
            j++;  
        }
        k++;
    }

    while (i < leftLen) {
        memcpy(GetElement(arr, k++, elemSize),
               GetElement(leftBuf, i++, elemSize), elemSize);
        if (swaps) (*swaps)++;
    }
    while (j < rightLen) {
        memcpy(GetElement(arr, k++, elemSize),
               GetElement(rightBuf, j++, elemSize), elemSize);
        if (swaps) (*swaps)++;
    }

    free(leftBuf);
    free(rightBuf);
}

//Вычисляет оптимальный минимальный размер run'а для заданной длины массива
int MinRun(int n) {
    int i = 0;
    while (n >= 64) {
        if (n % 2 == 1) {
            i = 1; 
        }
        n = n / 2;  
    }
    return n + i;
}

//Проверяет и выполняет слияние run'ов согласно инвариантам стека TimSort
int MergeIfNeeded(void *arr, Run *stack, int *stackSize,
                  size_t elemSize,
                  int (*cmp)(const void *, const void *),
                  long *comparisons, long *swaps) {
    if (*stackSize < 2) return 0;

    Run *A = &stack[*stackSize - 1];
    Run *B = &stack[*stackSize - 2];

    if (*stackSize >= 3) {
        Run *C = &stack[*stackSize - 3];
        if (C->len <= B->len + A->len || B->len <= A->len) {
            if (C->len < A->len) {
                int cRight = C->start + C->len + B->len - 1;
                MergeRuns(arr, C->start, C->start + C->len - 1,
                          cRight, elemSize, cmp, comparisons, swaps);
                C->len += B->len;
                stack[*stackSize - 2] = stack[*stackSize - 1];
            } else {
                int bRight = B->start + B->len + A->len - 1;
                MergeRuns(arr, B->start, B->start + B->len - 1,
                          bRight, elemSize, cmp, comparisons, swaps);
                B->len += A->len;
            }
            (*stackSize)--;
            return 1;
        }
        return 0;
    }
    if (B->len <= A->len) {
        int bRight = B->start + B->len + A->len - 1;
        MergeRuns(arr, B->start, B->start + B->len - 1,
                  bRight, elemSize, cmp, comparisons, swaps);
        B->len += A->len;
        (*stackSize)--;
        return 1;
    }
    return 0;
}

//Выполняет окончательное слияние всех оставшихся run'ов в стеке
void MergeAll(void *arr, Run *stack, int *stackSize,
              size_t elemSize,
              int (*cmp)(const void *, const void *),
              long *comparisons, long *swaps) {
    while (*stackSize > 1) {
        Run *A = &stack[*stackSize - 1];
        Run *B = &stack[*stackSize - 2];
        int bRight = B->start + B->len + A->len - 1;
        MergeRuns(arr, B->start, B->start + B->len - 1,
                  bRight, elemSize, cmp, comparisons, swaps);
        B->len += A->len;
        (*stackSize)--;
    }
}

//Основная функция гибридной сортировки TimSort
void TimSort(void *arr, int n, size_t elemSize,
             int (*cmp)(const void *, const void *),
             long *comparisons, long *swaps) {
    if (n < 2) return;
    int minrun = MinRun(n);
    int maxStack = 128;
    Run stack[128];
    int stackSize = 0;
    int pos = 0;

    while (pos < n) {
        if (stackSize >= maxStack) {
            MergeAll(arr, stack, &stackSize, elemSize, cmp, comparisons, swaps);
        }
        int runEnd = FindRun(arr, pos, n, elemSize, cmp, comparisons, swaps);
        int forcedEnd = pos + minrun - 1;
        if (forcedEnd > n - 1) forcedEnd = n - 1;
        if (forcedEnd > runEnd) {
            InsertionSort2(arr, pos, forcedEnd, elemSize, cmp, comparisons, swaps);
            runEnd = forcedEnd;
        }
        stack[stackSize].start = pos;
        stack[stackSize].len = runEnd - pos + 1;
        stackSize++;
        pos = runEnd + 1;
        while (MergeIfNeeded(arr, stack, &stackSize,
                             elemSize, cmp, comparisons, swaps));
    }
    MergeAll(arr, stack, &stackSize, elemSize, cmp, comparisons, swaps);
}