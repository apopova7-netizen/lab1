//
// Created by Lenovo on 21.02.2026.
//
#ifndef ARCHITECT_H
#define ARCHITECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//#include "Student1.h"
#include "Student2.h"  // здесь уже определены PivotStrategy и PartitionType
//#include "Student3.h"

// Перечисление всех алгоритмов сортировки
typedef enum {
    // Студент 1
    SORT_INSERTION = 1,
    SORT_SELECTION,
    SORT_BUBBLE,
    SORT_GNOME_RECURSIVE,
    SORT_GNOME_ITERATIVE,
    SORT_STOOGE,
    SORT_SHELL,

    // Студент 2
    SORT_QUICKSORT,
    SORT_MERGESORT,
    SORT_HEAPSORT,
    SORT_TIMSORT,
    SORT_INTROSORT,

    // Студент 3
    SORT_COUNTING,
    SORT_RADIX_LSD,
    SORT_RADIX_MSD,
    SORT_BUCKET,
    SORT_DUTCH_FLAG,
    SORT_K_WAY_MERGE,
    SORT_PANCAKE
} SortingMethod;

// Структура для ВСЕХ параметров
typedef struct {
    // Какой алгоритм используем
    SortingMethod method;

    // Основные параметры
    void *arr;
    int n;
    size_t elem_size;
    int (*cmp)(const void*, const void*);

    // Для CountingSort
    int minVal;
    int maxVal;

    // Для RadixSort MSD
    int (*getDigit)(const void*, int);
    int max_digits;

    // Для StoogeSort
    int left;
    int right;

    // Для K-Way Merge
    void **arrays;
    int *sizes;
    int k;
    void *output;

    // Параметры для QuickSort (из student2.h)
    PivotStrategy strategyPivot;    // стратегия выбора опорного элемента
    PartitionType typePartition;     // тип разбиения (Ломуто/Хоара)

    // Счетчики
    long *comparisons;
    long *swaps;

} SortParams;

// Главная функция - единый интерфейс
void ExecuteSort(SortParams params);

#endif