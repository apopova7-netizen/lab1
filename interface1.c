//
// Created by Lenovo on 21.02.2026.
//
#include "Architect.h"

/*
Единый интерфейс для всех алгоритмов сортировки
Типы PivotStrategy и PartitionType берутся из student2.h
*/
void ExecuteSort(SortParams params) {

    // Выбор алгоритма по method
    switch (params.method) {

        // ========== СТУДЕНТ 1 ==========
/*
        case SORT_INSERTION:
            InsertionSort(params.arr, params.n, params.elem_size,
                         params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_SELECTION:
            SelectionSort(params.arr, params.n, params.elem_size,
                         params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_BUBBLE:
            BubbleSort(params.arr, params.n, params.elem_size,
                      params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_GNOME_RECURSIVE:
            GnomeSortRecursive(params.arr, params.n, params.elem_size,
                              params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_GNOME_ITERATIVE:
            GnomeSortIterative(params.arr, params.n, params.elem_size,
                              params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_STOOGE:
            StoogeSort(params.arr, params.left, params.right, params.elem_size,
                      params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_SHELL:
            ShellSort(params.arr, params.n, params.elem_size,
                     params.cmp, params.comparisons, params.swaps);
            break;*/

        // ========== СТУДЕНТ 2 ==========

        case SORT_QUICKSORT:
            // Используем параметры из student2.h
            QuickSort(params.arr, params.n, params.elem_size,
                     params.cmp,
                     params.strategyPivot,    // из student2.h
                     params.typePartition,    // из student2.h
                     params.comparisons, params.swaps);
            break;

        case SORT_MERGESORT:
            // Вызываем MergeSortTopDown из Student22.c
            MergeSortTopDown(params.arr, params.n, params.elem_size,
                           params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_HEAPSORT:
            // Вызываем HeapSort из Student23.c
            HeapSort(params.arr, params.n, params.elem_size,
                    params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_TIMSORT:
            // Вызываем TimSort из Student24.c
            TimSort(params.arr, params.n, params.elem_size,
                   params.cmp, params.comparisons, params.swaps);
            break;

        case SORT_INTROSORT:
            // Вызываем IntroSort из Student25.c
            IntroSort(params.arr, params.n, params.elem_size,
                     params.cmp, params.comparisons, params.swaps);
            break;

        // ========== СТУДЕНТ 3 ==========
/*
        case SORT_COUNTING:
            CountingSort((int*)params.arr, params.n,
                        params.minVal, params.maxVal,
                        params.comparisons, params.swaps);
            break;

        case SORT_RADIX_LSD:
            RadixSortLsd((int*)params.arr, params.n,
                        params.comparisons, params.swaps);
            break;

        case SORT_RADIX_MSD:
            RadixSortMsd(params.arr, params.n, params.elem_size,
                        params.getDigit, params.max_digits,
                        params.comparisons, params.swaps);
            break;

        case SORT_BUCKET:
            BucketSort((double*)params.arr, params.n,
                      params.comparisons, params.swaps);
            break;

        case SORT_DUTCH_FLAG:
            DutchFlagSort((int*)params.arr, params.n,
                         params.comparisons, params.swaps);
            break;

        case SORT_K_WAY_MERGE:
            KWwayMerge(params.arrays, params.sizes, params.k, params.elem_size,
                      params.cmp, params.output,
                      params.comparisons, params.swaps);
            break;

        case SORT_PANCAKE:
            PancakeSort((int*)params.arr, params.n,
                       params.comparisons, params.swaps);
            break;*/

        default:
            // Просто ничего не делаем, если метод неизвестен
            break;
    }
}