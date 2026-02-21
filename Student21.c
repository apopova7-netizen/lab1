#include "Student2.h"


// Сортировка вставками для малых массивов
void InsertionSort2(void *arr, int left, int right, size_t elemSize,
                   int (*cmp)(const void*, const void*),
                   long *comparisons, long *swaps) {
    for (int i = left + 1; i <= right; i++) {
        unsigned char key[elemSize];
        void *elemI = (char*)arr + i * elemSize;
        memcpy(key, elemI, elemSize);
        
        int j = i - 1;
        while (j >= left) {
            void *elemJ = (char*)arr + j * elemSize;
            if (comparisons) (*comparisons)++;
            if (cmp(elemJ, key) <= 0) break;
            
            void *NextJ = (char*)arr + (j + 1) * elemSize;
            memcpy(NextJ, elemJ, elemSize);
            if (swaps) (*swaps)++;  
            j--;
        }
        if (j + 1 != i) {
            void *NextJ = (char*)arr + (j + 1) * elemSize;
            memcpy(NextJ, key, elemSize);
            if (swaps) (*swaps)++;  
        }
    }
}


// Выбор опорного элемента по стратегии
int SelectPivot(void *arr, int left, int right, size_t elemSize,
                int (*cmp)(const void*, const void*),
                PivotStrategy strategy, long *comparisons) {
    switch (strategy) {
        case PIVOT_FIRST:
            return left;
        
        case PIVOT_LAST:
            return right;
        
        case PIVOT_MIDDLE:
            return left + (right - left) / 2;
        
        case PIVOT_RANDOM:
            return left + rand() % (right - left + 1);
        
        case PIVOT_MEDIAN: {
            int mid = left + (right - left) / 2;
            void *elemLeft  = GetElement(arr, left, elemSize);
            void *elemMid   = GetElement(arr, mid,  elemSize);
            void *elemRight = GetElement(arr, right, elemSize);
            
            if (comparisons) (*comparisons)++;
            if (cmp(elemLeft, elemMid) > 0) {
                if (comparisons) (*comparisons)++;
                if (cmp(elemMid, elemRight) > 0)
                    return mid;
                if (comparisons) (*comparisons)++;
                return (cmp(elemLeft, elemRight) > 0) ? right : left;
            } else {
                if (comparisons) (*comparisons)++;
                if (cmp(elemLeft, elemRight) > 0)
                    return left;
                if (comparisons) (*comparisons)++;
                return (cmp(elemMid, elemRight) > 0) ? right : mid;
            }
        }
        
        default:
            return left;
    }
}

// Разбиение Ломуто
int PartitionLomuto(void *arr, int left, int right, size_t elemSize,
                    int (*cmp)(const void*, const void*),
                    long *comparisons, long *swaps) {
    void *pivot = GetElement(arr, right, elemSize);
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        void *elemJ = GetElement(arr, j, elemSize);
        if (comparisons) (*comparisons)++;
        
        if (cmp(elemJ, pivot) <= 0) {
            i++;
            void *elemI = GetElement(arr, i, elemSize);
            if (i != j) {
                Swap(elemI, elemJ, elemSize, swaps);
            }
        }
    }
    
    void *elemINext = GetElement(arr, i + 1, elemSize);
    void *elemRight = GetElement(arr, right, elemSize);
    if (i + 1 != right) {
        Swap(elemINext, elemRight, elemSize, swaps);
    }
    
    return i + 1;
}

// Разбиение Хоара
int PartitionHoare(void *arr, int left, int right, size_t elemSize,
                   int (*cmp)(const void*, const void*),
                   PivotStrategy strategyPivot,
                   long *comparisons, long *swaps) {
    int pivotPos = SelectPivot(arr, left, right, elemSize, cmp,
                               strategyPivot, comparisons);
    int mid = left + (right - left) / 2;
    if (pivotPos != mid) {
        Swap(GetElement(arr, pivotPos, elemSize),
             GetElement(arr, mid, elemSize), elemSize, swaps);
    }
    unsigned char *pivotVal = malloc(elemSize);
    if (!pivotVal) return left; 
    memcpy(pivotVal, GetElement(arr, mid, elemSize), elemSize);

    int i = left - 1;
    int j = right + 1;

    while (1) {
        do {
            i++;
            if (comparisons) (*comparisons)++;
        } while (i <= right && cmp(GetElement(arr, i, elemSize), pivotVal) < 0);

        do {
            j--;
            if (comparisons) (*comparisons)++;
        } while (j >= left && cmp(GetElement(arr, j, elemSize), pivotVal) > 0);

        if (i >= j) {
            free(pivotVal);
            return j;
        }

        Swap(GetElement(arr, i, elemSize),
             GetElement(arr, j, elemSize), elemSize, swaps);
    }
}

// Рекурсивная версия быстрой сортировки
void QuickSortRecursive(void *arr, int left, int right, size_t elemSize,
                        int (*cmp)(const void*, const void*),
                        PivotStrategy strategyPivot,
                        PartitionType typePartition,
                        long *comparisons, long *swaps,
                        int depth) {
    if (left >= right) return;
    if (depth > MAX_RECURSION_DEPTH) {
        InsertionSort2(arr, left, right, elemSize, cmp, comparisons, swaps);
        return;
    }
    if (right - left + 1 < INSERTION_SORT_THRESHOLD) {
        InsertionSort2(arr, left, right, elemSize, cmp, comparisons, swaps);
        return;
    }
    int pivotIndex;
    if (typePartition == PARTITION_LOMUTO) {
        int selected = SelectPivot(arr, left, right, elemSize, cmp,
                                   strategyPivot, comparisons);
        if (selected != right) {
            Swap(GetElement(arr, selected, elemSize),
                 GetElement(arr, right, elemSize), elemSize, swaps);
        }
        pivotIndex = PartitionLomuto(arr, left, right, elemSize, cmp,
                                     comparisons, swaps);
        QuickSortRecursive(arr, left, pivotIndex - 1, elemSize, cmp,
                           strategyPivot, typePartition,
                           comparisons, swaps, depth + 1);
        QuickSortRecursive(arr, pivotIndex + 1, right, elemSize, cmp,
                           strategyPivot, typePartition,
                           comparisons, swaps, depth + 1);
    } else {
        pivotIndex = PartitionHoare(arr, left, right, elemSize, cmp,
                                    strategyPivot, comparisons, swaps);
        QuickSortRecursive(arr, left, pivotIndex, elemSize, cmp,
                           strategyPivot, typePartition,
                           comparisons, swaps, depth + 1);
        QuickSortRecursive(arr, pivotIndex + 1, right, elemSize, cmp,
                           strategyPivot, typePartition,
                           comparisons, swaps, depth + 1);
    }
}

// Версия с выбором стратегии
void QuickSort(void *arr, int n, size_t elemSize,
               int (*cmp)(const void*, const void*),
               PivotStrategy strategyPivot,
               PartitionType typePartition,
               long *comparisons, long *swaps) {
    if (n <= 1) return;
    QuickSortRecursive(arr, 0, n - 1, elemSize, cmp,
                       strategyPivot, typePartition,
                       comparisons, swaps, 0);
}


// Итеративная версия быстрой сортировки
void QuickSortIterative(void *arr, int n, size_t elem_size,
                        int (*cmp)(const void*, const void*),
                        PivotStrategy strategyPivot,
                        PartitionType typePartition,
                        long *comparisons, long *swaps) {
    
    if (n <= 1) return;
    int *stack = malloc(2 * n * sizeof(int));
    if (!stack) return;
    int top = -1;
    stack[++top] = 0;
    stack[++top] = n - 1;
    
    while (top >= 0) {
        int right = stack[top--];
        int left = stack[top--];
        if (right - left + 1 < INSERTION_SORT_THRESHOLD) {
            InsertionSort2(arr, left, right, elem_size, cmp, comparisons, swaps);
            continue;
        }
        int pivotIndex;
        if (typePartition == PARTITION_LOMUTO) {
            int selected = SelectPivot(arr, left, right, elem_size, 
                                      cmp, strategyPivot, comparisons);
            if (selected != right) {
                Swap(GetElement(arr, selected, elem_size),
                     GetElement(arr, right, elem_size), elem_size, swaps);
            }
            
            pivotIndex = PartitionLomuto(arr, left, right, elem_size, 
                                       cmp, comparisons, swaps);
            int leftSize = pivotIndex - 1 - left;
            int rightSize = right - (pivotIndex + 1);
            if (leftSize > rightSize) {
                if (left < pivotIndex - 1) {
                    stack[++top] = left;
                    stack[++top] = pivotIndex - 1;
                }
                if (pivotIndex + 1 < right) {
                    stack[++top] = pivotIndex + 1;
                    stack[++top] = right;
                }
            } else {
                if (pivotIndex + 1 < right) {
                    stack[++top] = pivotIndex + 1;
                    stack[++top] = right;
                }
                if (left < pivotIndex - 1) {
                    stack[++top] = left;
                    stack[++top] = pivotIndex - 1;
                }
            }
        } else { 
            pivotIndex = PartitionHoare(arr, left, right, elem_size, cmp,
                                      strategyPivot, comparisons, swaps);
            int leftSize = pivotIndex - left;
            int rightSize = right - (pivotIndex + 1);
            if (leftSize > rightSize) {
                if (left < pivotIndex) {
                    stack[++top] = left;
                    stack[++top] = pivotIndex;
                }
                if (pivotIndex + 1 < right) {
                    stack[++top] = pivotIndex + 1;
                    stack[++top] = right;
                }
            } else {
                if (pivotIndex + 1 < right) {
                    stack[++top] = pivotIndex + 1;
                    stack[++top] = right;
                }
                if (left < pivotIndex) {
                    stack[++top] = left;
                    stack[++top] = pivotIndex;
                }
            }
        }
    }
    free(stack);
}