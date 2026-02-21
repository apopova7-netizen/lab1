//
// Created by Lenovo on 20.02.2026.
//
#include "Architect1.c.h"

// Функция сравнения для целых чисел
int compare_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// Функция сравнения для double
int compare_double(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

// Функция для печати целочисленного массива
void print_int_array(int* arr, int n) {
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// Функция для печати double массива
void print_double_array(double* arr, int n) {
    for(int i = 0; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n");
}

int main() {

    // Счетчики для операций
    long comparisons = 0;
    long swaps = 0;

    printf("\n=== ЕДИНЫЙ ИНТЕРФЕЙС ДЛЯ АЛГОРИТМОВ СТУДЕНТА 2 ===\n\n");

    // ===== ПРИМЕР 1: QuickSort на целых числах =====
    printf("Пример 1: QuickSort (int) с PIVOT_FIRST\n");
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Исходный: ");
    print_int_array(arr1, n1);

    SortParams params1;
    params1.method = SORT_QUICKSORT;
    params1.arr = arr1;
    params1.n = n1;
    params1.elem_size = sizeof(int);
    params1.cmp = compare_int;
    params1.strategyPivot = PIVOT_FIRST;
    params1.typePartition = PARTITION_LOMUTO;
    params1.comparisons = &comparisons;
    params1.swaps = &swaps;

    ExecuteSort(params1);

    printf("Результат: ");
    print_int_array(arr1, n1);
    printf("Сравнений: %ld, Обменов: %ld\n\n", comparisons, swaps);

    // ===== ПРИМЕР 2: QuickSort на double числах =====
    printf("Пример 2: QuickSort (double) с PIVOT_MEDIAN\n");
    double darr1[] = {64.5, 34.2, 25.7, 12.1, 22.8, 11.3, 90.0};
    int nd1 = sizeof(darr1) / sizeof(darr1[0]);

    printf("Исходный: ");
    print_double_array(darr1, nd1);

    comparisons = 0;
    swaps = 0;

    SortParams params2;
    params2.method = SORT_QUICKSORT;
    params2.arr = darr1;
    params2.n = nd1;
    params2.elem_size = sizeof(double);
    params2.cmp = compare_double;
    params2.strategyPivot = PIVOT_MEDIAN;  // медиана из трех
    params2.typePartition = PARTITION_HOARE;
    params2.comparisons = &comparisons;
    params2.swaps = &swaps;

    ExecuteSort(params2);

    printf("Результат: ");
    print_double_array(darr1, nd1);
    printf("Сравнений: %ld, Обменов: %ld\n\n", comparisons, swaps);

    // ===== ПРИМЕР 3: Сравнение ВСЕХ стратегий QuickSort =====
    printf("\n=== Сравнение ВСЕХ стратегий QuickSort (из Student2.h) ===\n");

    int test_arr[] = {64, 34, 25, 12, 22, 11, 90, 45, 33, 18, 77, 55};
    int n_test = sizeof(test_arr) / sizeof(test_arr[0]);

    printf("Исходный массив: ");
    print_int_array(test_arr, n_test);
    printf("\n");

    // Все 5 стратегий из Student2.h
    PivotStrategy strategies[] = {
        PIVOT_FIRST,
        PIVOT_LAST,
        PIVOT_MIDDLE,
        PIVOT_MEDIAN,
        PIVOT_RANDOM
    };

    char* strategy_names[] = {
        "PIVOT_FIRST",
        "PIVOT_LAST",
        "PIVOT_MIDDLE",
        "PIVOT_MEDIAN",
        "PIVOT_RANDOM"
    };

    printf("Тип разбиения: PARTITION_LOMUTO\n");
    for(int i = 0; i < 5; i++) {
        // Создаем копию массива
        int *arr_copy = malloc(n_test * sizeof(int));
        memcpy(arr_copy, test_arr, n_test * sizeof(int));

        comparisons = 0;
        swaps = 0;

        SortParams p;
        p.method = SORT_QUICKSORT;
        p.arr = arr_copy;
        p.n = n_test;
        p.elem_size = sizeof(int);
        p.cmp = compare_int;
        p.strategyPivot = strategies[i];
        p.typePartition = PARTITION_LOMUTO;
        p.comparisons = &comparisons;
        p.swaps = &swaps;

        clock_t start = clock();
        ExecuteSort(p);
        clock_t end = clock();

        double time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        printf("Стратегия: %-12s | Время: %8.3f ms | Сравнений: %4ld | Обменов: %4ld\n",
               strategy_names[i], time_ms, comparisons, swaps);

        free(arr_copy);
    }

    printf("\nТип разбиения: PARTITION_HOARE\n");
    for(int i = 0; i < 5; i++) {
        // Создаем копию массива
        int *arr_copy = malloc(n_test * sizeof(int));
        memcpy(arr_copy, test_arr, n_test * sizeof(int));

        comparisons = 0;
        swaps = 0;

        SortParams p;
        p.method = SORT_QUICKSORT;
        p.arr = arr_copy;
        p.n = n_test;
        p.elem_size = sizeof(int);
        p.cmp = compare_int;
        p.strategyPivot = strategies[i];
        p.typePartition = PARTITION_HOARE;
        p.comparisons = &comparisons;
        p.swaps = &swaps;

        clock_t start = clock();
        ExecuteSort(p);
        clock_t end = clock();

        double time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        printf("Стратегия: %-12s | Время: %8.3f ms | Сравнений: %4ld | Обменов: %4ld\n",
               strategy_names[i], time_ms, comparisons, swaps);

        free(arr_copy);
    }

    // ===== ПРИМЕР 4: MergeSort =====
    printf("\nПример 4: MergeSort\n");
    int arr3[] = {38, 27, 43, 3, 9, 82, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Исходный: ");
    print_int_array(arr3, n3);

    comparisons = 0;
    swaps = 0;

    SortParams params3;
    params3.method = SORT_MERGESORT;
    params3.arr = arr3;
    params3.n = n3;
    params3.elem_size = sizeof(int);
    params3.cmp = compare_int;
    params3.comparisons = &comparisons;
    params3.swaps = &swaps;

    ExecuteSort(params3);

    printf("Результат: ");
    print_int_array(arr3, n3);
    printf("Сравнений: %ld, Обменов: %ld\n\n", comparisons, swaps);

    // ===== ПРИМЕР 5: HeapSort =====
    printf("Пример 5: HeapSort\n");
    int arr4[] = {12, 11, 13, 5, 6, 7};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Исходный: ");
    print_int_array(arr4, n4);

    comparisons = 0;
    swaps = 0;

    SortParams params4;
    params4.method = SORT_HEAPSORT;
    params4.arr = arr4;
    params4.n = n4;
    params4.elem_size = sizeof(int);
    params4.cmp = compare_int;
    params4.comparisons = &comparisons;
    params4.swaps = &swaps;

    ExecuteSort(params4);

    printf("Результат: ");
    print_int_array(arr4, n4);
    printf("Сравнений: %ld, Обменов: %ld\n\n", comparisons, swaps);

    // ===== ПРИМЕР 6: TimSort =====
    printf("Пример 6: TimSort\n");
    int arr5[] = {5, 21, 7, 23, 19, 10, 3, 15, 12, 8};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("Исходный: ");
    print_int_array(arr5, n5);

    comparisons = 0;
    swaps = 0;

    SortParams params5;
    params5.method = SORT_TIMSORT;
    params5.arr = arr5;
    params5.n = n5;
    params5.elem_size = sizeof(int);
    params5.cmp = compare_int;
    params5.comparisons = &comparisons;
    params5.swaps = &swaps;

    ExecuteSort(params5);

    printf("Результат: ");
    print_int_array(arr5, n5);
    printf("Сравнений: %ld, Обменов: %ld\n\n", comparisons, swaps);

    // ===== ПРИМЕР 7: IntroSort =====
    printf("Пример 7: IntroSort\n");
    int arr6[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);

    printf("Исходный: ");
    print_int_array(arr6, n6);

    comparisons = 0;
    swaps = 0;

    SortParams params6;
    params6.method = SORT_INTROSORT;
    params6.arr = arr6;
    params6.n = n6;
    params6.elem_size = sizeof(int);
    params6.cmp = compare_int;
    params6.comparisons = &comparisons;
    params6.swaps = &swaps;

    ExecuteSort(params6);

    printf("Результат: ");
    print_int_array(arr6, n6);
    printf("Сравнений: %ld, Обменов: %ld\n\n", comparisons, swaps);

    return 0;
}