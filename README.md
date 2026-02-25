Документация библиотеки сортировки
Роль в проекте: Архитектор библиотеки
Я отвечаю за три ключевых компонента:

Единый интерфейс (ExecuteSort) — универсальная функция запуска любого алгоритма

Система бенчмаркинга (Benchmark.c) — тестирование производительности

Оптимальный выбор алгоритма (OptimalAlgorithm.c) — интеллектуальный подбор алгоритма под данные

1. Единый интерфейс (Interface.c)
Назначение
Предоставить единую точку входа для запуска любого алгоритма сортировки, скрывая различия в их параметрах.

Структура параметров
c
typedef struct {
    // Какой алгоритм используем
    SortingMethod method;
    
    // Основные параметры (есть у всех)
    void *arr;                    // массив
    int n;                         // размер
    size_t elemSize;                // размер элемента
    int (*cmp)(const void*, const void*); // функция сравнения
    
    // Специальные параметры для конкретных алгоритмов
    int minVal, maxVal;             // для CountingSort
    int (*getDigit)(const void*, int); // для RadixSort
    int maxDigits;                   // для RadixSort
    int left, right;                 // для StoogeSort
    PivotStrategy strategyPivot;     // для QuickSort
    PartitionType typePartition;      // для QuickSort
    
    // Счетчики операций
    long *comparisons;                // количество сравнений
    long *swaps;                       // количество обменов
} SortParams;
Основная функция
c
void ExecuteSort(SortParams params);
Как работает:

Принимает структуру со всеми возможными параметрами

По полю method определяет нужный алгоритм

Передает только релевантные параметры в конкретную функцию

Пример использования:

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
2. Система бенчмаркинга (Benchmark.c)
Назначение
Автоматическое тестирование алгоритмов на различных типах данных с высокоточным измерением производительности.

Ключевые возможности
Функция	Описание
GetPreciseTimeMS()	Таймер с микросекундной точностью (QueryPerformanceCounter)
GenerateRandomIntArray()	Генерация случайного int массива
GenerateRandomDoubleArray()	Генерация случайного double массива
GenerateSortedArray()	Отсортированный массив
GenerateReversedArray()	Массив в обратном порядке
GenerateAlmostSortedArray()	Почти отсортированный массив
Основные функции тестирования
1. Тестирование одного алгоритма
c
void RunSingleTest(SortingMethod algo, 
                   PivotStrategy strategy, 
                   PartitionType partition);
Что тестирует:

Маленькие массивы (12 элементов) — int и double (если поддерживается)

Вывод массива ДО и ПОСЛЕ сортировки

Время выполнения

Время на элемент

Количество сравнений и обменов (если алгоритм их поддерживает)

Большие массивы (10000 элементов) — 4 типа:

Random (случайный)

Sorted (отсортированный)

Reverse (обратный порядок)

Almost Sorted (почти отсортированный, 5% перестановок)

Для каждого типа выводится:

Время выполнения

Время на элемент

Количество сравнений и обменов

2. Тестирование всех вариаций QuickSort
c
void BenchmarkQuickSortAllVariations(void);
Тестирует все 10 комбинаций стратегий QuickSort:

5 стратегий выбора опорного элемента: FIRST, LAST, MIDDLE, MEDIAN, RANDOM

2 типа разбиения: LOMUTO, HOARE

Для каждой комбинации тестирование на 4 типах массивов (случайный, отсортированный, обратный, почти отсортированный).

Пример вывода:

text
===== Random =====
  Configuration              | Time         | ns/el    | Compares | Swaps
  FIRST + LOMUTO             | 1.913700     | 191.4    | 160510   | 85666
  MEDIAN + HOARE             | 1.707600     | 170.8    | 150110   | 42035
3. Тестирование всех алгоритмов
c
void TestAllAlgorithms(void);
Запускает RunSingleTest для всех доступных алгоритмов с конфигурацией PIVOT_MEDIAN + PARTITION_HOARE (для QuickSort).

3. Оптимальный выбор алгоритма (OptimalAlgorithm.c)
Назначение
Автоматически определить наиболее эффективный алгоритм сортировки на основе анализа входных данных.

Вспомогательные функции
c
int IsIntArray(size_t elemSize);
// Проверяет, является ли массив типа int (по размеру элемента)

int IsSorted(void *arr, int n, size_t elemSize, int (*cmp)(const void*, const void*));
// Проверяет, отсортирован ли массив по возрастанию

void FindMinMaxInt(int *arr, int n, int *minVal, int *maxVal);
// Находит минимальное и максимальное значение в int массиве
Логика выбора
c
SortingMethod SelectOptimalAlgorithm(void *arr, int n, size_t elemSize,
                                      int (*cmp)(const void*, const void*),
                                      int *outMinVal, int *outMaxVal);
Правила принятия решений:

Условие	Выбранный алгоритм	Обоснование
n ≤ 100	SORT_SHELL	На маленьких массивах важнее низкие накладные расходы, ShellSort показывает хорошие результаты
n > 100 и массив отсортирован	SORT_TIMSORT	TimSort работает за O(n) на отсортированных данных
n > 100 и тип НЕ int	SORT_TIMSORT	TimSort — лучший универсальный алгоритм для сложных типов
n > 100, тип int, не отсортирован	SORT_COUNTING	CountingSort работает за O(n) для целых чисел с ограниченным диапазоном
Важные замечания
Для CountingSort функция возвращает через outMinVal и outMaxVal минимальное и максимальное значение, необходимые для работы алгоритма.

Определение типа происходит по elemSize: sizeof(int) считается int массивом, все остальное — "не int".

Проверка на отсортированность выполняется за один проход по массиву (O(n)).
