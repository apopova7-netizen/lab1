Sorting Library Documentation
Role: Library Architect
Unified Interface (Interface.c) — universal function to run any sorting algorithm

Benchmarking System (Benchmark.c) — performance testing and analysis

Optimal Algorithm Selection (OptimalAlgorithm.c) — algorithm selection based on input data

1. Unified Interface (Interface.c)
Purpose
Provide a single entry point for running any sorting algorithm, hiding differences in their parameters.

Parameter Structure
c
typedef struct {
    // Which algorithm to use
    SortingMethod method;
    
    // Basic parameters (common to all)
    void *arr;                    // array
    int n;                         // size
    size_t elemSize;                // element size
    int (*cmp)(const void*, const void*); // comparison function
    
    // Special parameters for specific algorithms
    int minVal, maxVal;             // for CountingSort
    int (*getDigit)(const void*, int); // for RadixSort
    int maxDigits;                   // for RadixSort
    int left, right;                 // for StoogeSort
    PivotStrategy strategyPivot;     // for QuickSort
    PartitionType typePartition;      // for QuickSort
    
    // Operation counters
    long *comparisons;                // number of comparisons
    long *swaps;                       // number of swaps
} SortParams;
Main Function
c
void ExecuteSort(SortParams params);
How it works:

Takes a structure with all possible parameters

Determines the required algorithm by the method field

Passes only relevant parameters to the specific function

Usage Example:

c
SortParams params;
params.method = SORT_QUICKSORT;
params.arr = myArray;
params.n = 100;
params.elemSize = sizeof(int);
params.cmp = CompareInt;
params.strategyPivot = PIVOT_MEDIAN;
params.typePartition = PARTITION_HOARE;
params.comparisons = &compCount;
params.swaps = &swapCount;

ExecuteSort(params);
2. Benchmarking System (Benchmark.c)
Purpose
Automated testing of algorithms on various data types with high-precision performance measurement.

Main Testing Functions
2.1 Testing a Single Algorithm
c
void RunSingleTest(SortingMethod algo, 
                   PivotStrategy strategy, 
                   PartitionType partition);
What it tests:

Small arrays (12 elements) — int and double (if supported)

Array output BEFORE and AFTER sorting

Execution time

Time per element

Number of comparisons and swaps (if supported by the algorithm)

Large arrays (10000 elements) — 4 types:

Random

Sorted

Reverse

Almost Sorted (5% permutations)

For each type it outputs:

Execution time

Time per element

Number of comparisons and swaps

2.2 Testing All QuickSort Variations
c
void BenchmarkQuickSortAllVariations(void);
Tests all 10 combinations of QuickSort strategies:

5 pivot selection strategies: FIRST, LAST, MIDDLE, MEDIAN, RANDOM

2 partition types: LOMUTO, HOARE

Each combination is tested on 4 array types (random, sorted, reverse, almost sorted).

Output Example:

text
===== Random =====
  Configuration              | Time         | ns/el    | Compares | Swaps
  FIRST + LOMUTO             | 1.913700     | 191.4    | 160510   | 85666
  MEDIAN + HOARE             | 1.707600     | 170.8    | 150110   | 42035
2.3 Testing All Algorithms
c
void TestAllAlgorithms(void);
Runs RunSingleTest for all available algorithms.

3. Optimal Algorithm Selection (OptimalAlgorithm.c)
Purpose
Automatically determine the most efficient sorting algorithm based on input data analysis.

Decision Rules:

Condition	Selected Algorithm	Rationale
n ≤ 100	SORT_SHELL	For small arrays, ShellSort shows good results
n > 100 and array is sorted	SORT_TIMSORT	TimSort runs in O(n) on sorted data
n > 100 and type is NOT int	SORT_TIMSORT	TimSort is the best universal algorithm for complex types
n > 100, type is int, not sorted	SORT_COUNTING	CountingSort runs in O(n) for integers
For CountingSort, the function returns minimum and maximum values through outMinVal and outMaxVal — required for the algorithm to work.
