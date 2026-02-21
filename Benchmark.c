// ========== ЗАДАЧА 2: БЕНЧМАРКИНГ ==========
#include "Architect.h"
// Название алгоритма
const char* get_algorithm_name(SortingMethod algo) {
    switch(algo) {
        case SORT_INSERTION: return "InsertionSort";
        case SORT_SELECTION: return "SelectionSort";
        case SORT_BUBBLE: return "BubbleSort";
        case SORT_GNOME_RECURSIVE: return "GnomeRecursive";
        case SORT_GNOME_ITERATIVE: return "GnomeIterative";
        case SORT_STOOGE: return "StoogeSort";
        case SORT_SHELL: return "ShellSort";
        case SORT_QUICKSORT: return "QuickSort";
        case SORT_MERGESORT: return "MergeSort";
        case SORT_HEAPSORT: return "HeapSort";
        case SORT_TIMSORT: return "TimSort";
        case SORT_INTROSORT: return "IntroSort";
        case SORT_COUNTING: return "CountingSort (только int)";
        case SORT_RADIX_LSD: return "RadixSortLSD (только int)";
        case SORT_RADIX_MSD: return "RadixSortMSD";
        case SORT_BUCKET: return "BucketSort (только double)";
        case SORT_DUTCH_FLAG: return "DutchFlagSort (только int)";
        case SORT_K_WAY_MERGE: return "KWayMerge";
        case SORT_PANCAKE: return "PancakeSort (только int)";
        default: return "Unknown";
    }
}

// Проверка, работает ли алгоритм с int
int works_with_int(SortingMethod algo) {
    if (algo == SORT_BUCKET) return 0;  // BucketSort только double
    return 1;  // все остальные работают с int
}

// Проверка, работает ли алгоритм с double
int works_with_double(SortingMethod algo) {
    // Эти алгоритмы работают только с int
    if (algo == SORT_COUNTING || algo == SORT_RADIX_LSD ||
        algo == SORT_DUTCH_FLAG || algo == SORT_PANCAKE) {
        return 0;
    }
    // BucketSort специально для double
    if (algo == SORT_BUCKET) return 1;
    // Остальные работают с void*, значит могут и с double
    return 1;
}

// Копирование массива int
void copy_int_array(int *dest, int *src, int n) {
    for(int i = 0; i < n; i++) dest[i] = src[i];
}

// Копирование массива double
void copy_double_array(double *dest, double *src, int n) {
    for(int i = 0; i < n; i++) dest[i] = src[i];
}

// Функция сравнения для double
int compare_double(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

// ===== ФИКСИРОВАННЫЕ ТЕСТОВЫЕ МАССИВЫ =====

// INT массивы
int int_small_4[] = {8, 2, 5, 1};
int int_medium_7[] = {7, 2, 9, 1, 5, 3, 8};
int int_nearly_sorted_5[] = {1, 2, 4, 3, 5};
int int_reversed_5[] = {5, 4, 3, 2, 1};

// DOUBLE массивы (те же числа)
double double_small_4[] = {8.0, 2.0, 5.0, 1.0};
double double_medium_7[] = {7.0, 2.0, 9.0, 1.0, 5.0, 3.0, 8.0};
double double_nearly_sorted_5[] = {1.0, 2.0, 4.0, 3.0, 5.0};
double double_reversed_5[] = {5.0, 4.0, 3.0, 2.0, 1.0};

// ===== ФУНКЦИЯ БЕНЧМАРКИНГА =====

void benchmark_algorithm(SortingMethod algo) {

    printf("\n========== %s ==========\n", get_algorithm_name(algo));

    // Определяем, с какими типами тестируем
    int test_int = works_with_int(algo);
    int test_double = works_with_double(algo);

    // Названия тестов
    char *test_names[] = {
        "Маленький случ. (4)",
        "Средний случ. (7)",
        "Почти отсорт. (5)",
        "Обратный (5)"
    };

    // Размеры тестов
    int sizes[] = {4, 7, 5, 5};

    // Если алгоритм работает с int
    if (test_int) {
        printf("\n--- ТЕСТИРОВАНИЕ НА INT МАССИВАХ ---\n");
        printf("%-25s %-12s %-15s %-12s %-10s\n",
               "Тестовый массив", "Время(ms)", "нс/элемент", "Сравнения", "Обмены");
        printf("----------------------------------------------------------------\n");

        for(int test = 0; test < 4; test++) {

            // Выбираем исходные данные
            int *src = NULL;
            switch(test) {
                case 0: src = int_small_4; break;
                case 1: src = int_medium_7; break;
                case 2: src = int_nearly_sorted_5; break;
                case 3: src = int_reversed_5; break;
            }

            // Создаем копию
            int *data_copy = malloc(sizes[test] * sizeof(int));
            copy_int_array(data_copy, src, sizes[test]);

            // Счетчики
            long comparisons = 0;
            long swaps = 0;

            // Замер времени
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            // Заполняем параметры
            SortParams params;
            params.method = algo;
            params.arr = data_copy;
            params.n = sizes[test];
            params.elem_size = sizeof(int);
            params.cmp = NULL;  // для int сортировок
            params.comparisons = &comparisons;
            params.swaps = &swaps;

            // Для CountingSort
            params.minVal = 1;
            params.maxVal = 9;

            // Для RadixSort MSD
            params.getDigit = NULL;
            params.max_digits = 3;

            // Для StoogeSort
            params.left = 0;
            params.right = sizes[test] - 1;

            // Остальное не используется
            params.arrays = NULL;
            params.sizes = NULL;
            params.k = 0;
            params.output = NULL;

            // Вызываем сортировку
            ExecuteSort(params);

            // Конец замера времени
            clock_gettime(CLOCK_MONOTONIC, &end);

            // Считаем время
            double time_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                             (end.tv_nsec - start.tv_nsec) / 1000000.0;

            // Выводим результаты
            printf("%-25s %-12.3f %-15.1f %-12ld %-10ld\n",
                   test_names[test],
                   time_ms,
                   (time_ms * 1000000.0) / sizes[test],
                   comparisons,
                   swaps);

            free(data_copy);
        }
    }

    // Если алгоритм работает с double
    if (test_double) {
        printf("\n--- ТЕСТИРОВАНИЕ НА DOUBLE МАССИВАХ ---\n");
        printf("%-25s %-12s %-15s %-12s %-10s\n",
               "Тестовый массив", "Время(ms)", "нс/элемент", "Сравнения", "Обмены");
        printf("----------------------------------------------------------------\n");

        for(int test = 0; test < 4; test++) {

            // Выбираем исходные данные
            double *src = NULL;
            switch(test) {
                case 0: src = double_small_4; break;
                case 1: src = double_medium_7; break;
                case 2: src = double_nearly_sorted_5; break;
                case 3: src = double_reversed_5; break;
            }

            // Создаем копию
            double *data_copy = malloc(sizes[test] * sizeof(double));
            copy_double_array(data_copy, src, sizes[test]);

            // Счетчики
            long comparisons = 0;
            long swaps = 0;

            // Замер времени
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            // Заполняем параметры
            SortParams params;
            params.method = algo;
            params.arr = data_copy;
            params.n = sizes[test];
            params.elem_size = sizeof(double);
            params.cmp = compare_double;  // для double нужна функция сравнения
            params.comparisons = &comparisons;
            params.swaps = &swaps;

            // Для CountingSort (не используется)
            params.minVal = 0;
            params.maxVal = 0;

            // Для RadixSort MSD
            params.getDigit = NULL;
            params.max_digits = 0;

            // Для StoogeSort
            params.left = 0;
            params.right = sizes[test] - 1;

            // Остальное не используется
            params.arrays = NULL;
            params.sizes = NULL;
            params.k = 0;
            params.output = NULL;

            // Вызываем сортировку
            ExecuteSort(params);

            // Конец замера времени
            clock_gettime(CLOCK_MONOTONIC, &end);

            // Считаем время
            double time_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                             (end.tv_nsec - start.tv_nsec) / 1000000.0;

            // Выводим результаты
            printf("%-25s %-12.3f %-15.1f %-12ld %-10ld\n",
                   test_names[test],
                   time_ms,
                   (time_ms * 1000000.0) / sizes[test],
                   comparisons,
                   swaps);

            free(data_copy);
        }
    }
}

#include "Student4.h"

// Функция для получения цифры (для RadixSort MSD)
int get_digit_int(const void* num, int pos) {
    int value = *(int*)num;
    for(int i = 0; i < pos; i++) value /= 10;
    return value % 10;
}

int main() {

    printf("========== БЕНЧМАРКИНГ АЛГОРИТМОВ СОРТИРОВКИ ==========\n");
    printf("Каждый алгоритм тестируется на типах, с которыми может работать\n\n");

    // Алгоритмы, которые работают с int (почти все)
    printf("\n=========================================================");
    printf("\nТЕСТИРОВАНИЕ АЛГОРИТМОВ, РАБОТАЮЩИХ С int");
    printf("\n=========================================================");

    benchmark_algorithm(SORT_INSERTION);
    benchmark_algorithm(SORT_SELECTION);
    benchmark_algorithm(SORT_BUBBLE);
    benchmark_algorithm(SORT_QUICKSORT);
    benchmark_algorithm(SORT_MERGESORT);
    benchmark_algorithm(SORT_HEAPSORT);

    // Алгоритмы, которые работают только с int
    printf("\n=========================================================");
    printf("\nАЛГОРИТМЫ, РАБОТАЮЩИЕ ТОЛЬКО С int");
    printf("\n=========================================================");

    benchmark_algorithm(SORT_COUNTING);
    benchmark_algorithm(SORT_RADIX_LSD);
    benchmark_algorithm(SORT_DUTCH_FLAG);
    benchmark_algorithm(SORT_PANCAKE);

    // Алгоритмы, которые работают с double
    printf("\n=========================================================");
    printf("\nТЕСТИРОВАНИЕ АЛГОРИТМОВ НА double МАССИВАХ");
    printf("\n=========================================================");

    benchmark_algorithm(SORT_BUBBLE);      // можно и на double
    benchmark_algorithm(SORT_QUICKSORT);    // можно и на double
    benchmark_algorithm(SORT_MERGESORT);    // можно и на double
    benchmark_algorithm(SORT_BUCKET);       // специально для double

    return 0;
}