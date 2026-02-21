#ifndef STUDENT2_H
#define STUDENT2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_RECURSION_DEPTH 64
#define INSERTION_SORT_THRESHOLD 10
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define K_INSERTION_SORT_THRESHOLD 16

typedef enum {
    PIVOT_FIRST,
    PIVOT_LAST,
    PIVOT_MIDDLE,
    PIVOT_MEDIAN,
    PIVOT_RANDOM     
} PivotStrategy;

typedef enum {
    PARTITION_LOMUTO,  
    PARTITION_HOARE    
} PartitionType;

typedef struct {
    int start; 
    int len;                 
} Run;

void CopyElement(void *dest, const void *src, size_t elemSize);
void Swap(void *a, void *b, size_t elemSize, long *swaps);
void* GetElement(void *arr, int index, size_t elemSize);
int CompareInt(const void *a, const void *b);

void InsertionSort2(void *arr, int left, int right, size_t elemSize,
                        int (*cmp)(const void*, const void*),
                        long *comparisons, long *swaps);
int SelectPivot(void *arr, int left, int right, size_t elemSize,
                int (*cmp)(const void*, const void*),
                PivotStrategy strategy, long *comparisons);
int PartitionLomuto(void *arr, int left, int right, size_t elemSize,
                    int (*cmp)(const void*, const void*),
                    long *comparisons, long *swaps);
int PartitionHoare(void *arr, int left, int right, size_t elemSize,
                   int (*cmp)(const void*, const void*),
                   PivotStrategy strategyPivot,
                   long *comparisons, long *swaps);
void QuickSortRecursive(void *arr, int left, int right, size_t elemSize,
                        int (*cmp)(const void*, const void*),
                        PivotStrategy strategyPivot,
                        PartitionType typePartition,
                        long *comparisons, long *swaps,
                        int depth);
void QuickSort(void *arr, int n, size_t elemSize,
               int (*cmp)(const void*, const void*),
               PivotStrategy strategyPivot,
               PartitionType typePartition,
               long *comparisons, long *swaps);
void QuickSortIterative(void *arr, int n, size_t elem_size,
                        int (*cmp)(const void*, const void*),
                        PivotStrategy strategyPivot,
                        PartitionType typePartition,
                        long *comparisons, long *swaps);


void Merge(void *arr, int left, int mid, int right, size_t elemSize,
           int (*cmp)(const void*, const void*),
           long *comparisons, long *swaps, void *tmp);
void MergeOptimized(void *arr, int left, int mid, int right, size_t esz,
                    int (*cmp)(const void *, const void *),
                    long *comparisons, long *swaps,
                    void *tmp);       
void MergeSortTopDownHelper(void *arr, int left, int right, size_t elemSize,
                                   int (*cmp)(const void*, const void*),
                                   long *comparisons, long *swaps, void *tmp);
void MergeSortTopDown(void *arr, int n, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons, long *swaps);
void MergeSortBottomUp(void *arr, int n, size_t elemSize,
                       int (*cmp)(const void*, const void*),
                       long *comparisons, long *swaps);                  
void MergeInPlace(void *arr, int left, int mid, int right, size_t elemSize,
                  int (*cmp)(const void*, const void*),
                  long *comparisons, long *swaps);                    
void MergeSortInPlace(void *arr, int left, int right, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons, long *swaps);
int FindRunEnd(void *arr, int start, int n, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons);
void MergeSortNatural(void *arr, int n, size_t elemSize,
                      int (*cmp)(const void*, const void*),
                      long *comparisons, long *swaps);               
void MergeSort(void *arr, int n, size_t elem_size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps);

void SiftDownOptimized(void *arr, int n, int i, size_t elemSize,
                       int (*cmp)(const void*, const void*),
                       long *comparisons, long *swaps);
void BuildMaxHeap(void *arr, int n, size_t elemSize,
                  int (*cmp)(const void*, const void*),
                  long *comparisons, long *swaps);
void HeapSort(void *arr, int n, size_t elemSize,
              int (*cmp)(const void*, const void*),
              long *comparisons, long *swaps);
              
              
int FindRun(void *arr, int start, int n, size_t elemSize,
            int (*cmp)(const void *, const void *),
            long *comparisons, long *swaps);
void MergeRuns(void *arr, int left, int mid, int right, size_t elemSize,
               int (*cmp)(const void *, const void *),
               long *comparisons, long *swaps);
int MinRun(int n);
int MergeIfNeeded(void *arr, Run *stack, int *stackSize,
                  size_t elemSize,
                  int (*cmp)(const void *, const void *),
                  long *comparisons, long *swaps);                                  
void MergeAll(void *arr, Run *stack, int *stackSize,
              size_t elemSize,
              int (*cmp)(const void *, const void *),
              long *comparisons, long *swaps);
void TimSort(void *arr, int n, size_t elemSize,
             int (*cmp)(const void *, const void *),
             long *comparisons, long *swaps);



int MedianOfThree(void *arr, int left, int right, size_t elemSize,
                  int (*cmp)(const void*, const void*),
                  long *comparisons, long *swaps);
int Partition(void *arr, int left, int right, size_t elemSize,
              int (*cmp)(const void*, const void*),
              long *comparisons, long *swaps);
void IntrosortRecursive(void *arr, int left, int right,
                               int depthLimit, size_t elemSize,
                               int (*cmp)(const void*, const void*),
                               long *comparisons, long *swaps);
void IntroSort(void *arr, int n, size_t elemSize,
               int (*cmp)(const void*, const void*),
               long *comparisons, long *swaps);                                             






#endif  /* STUDENT2_H */ 