#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemoryAllocated;

void merge(int arr[], int left, int middle, int right)
{
    int index1, index2, indexMerged;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int leftArr[n1], rightArr[n2];

    for (index1 = 0; index1 < n1; index1++)
        leftArr[index1] = arr[left + index1];
    for (index2 = 0; index2 < n2; index2++)
        rightArr[index2] = arr[middle + 1 + index2];

    index1 = 0;
    index2 = 0;
    indexMerged = left;

    while (index1 < n1 && index2 < n2)
    {
        if (leftArr[index1] <= rightArr[index2])
        {
            arr[indexMerged] = leftArr[index1];
            index1++;
        }
        else
        {
            arr[indexMerged] = rightArr[index2];
            index2++;
        }
        indexMerged++;
        extraMemoryAllocated += sizeof(int);
    }

    while (index1 < n1)
    {
        arr[indexMerged] = leftArr[index1];
        index1++;
        indexMerged++;
        extraMemoryAllocated += sizeof(int);
    }

    while (index2 < n2)
    {
        arr[indexMerged] = rightArr[index2];
        index2++;
        indexMerged++;
        extraMemoryAllocated += sizeof(int);
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void insertionSort(int *arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            extraMemoryAllocated += sizeof(int);
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int *arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                extraMemoryAllocated += sizeof(int);
            }
        }
    }
}

void selectionSort(int *arr, int n)
{
    int i, j, minIndex;
    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        extraMemoryAllocated += sizeof(int);
    }
}

int parseData(char *inputFileName, int **dataPtr)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSize = 0;
    *dataPtr = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSize);
        *dataPtr = (int *)malloc(sizeof(int) * dataSize);

        int i;
        for (i = 0; i < dataSize; i++)
        {
            fscanf(inFile, "%d", &(*dataPtr)[i]);
        }
    }

    return dataSize;
}

void printArray(int arr[], int dataSize)
{
    int i, lastStart = dataSize - 100;
    printf("\tData:\n\t");
    for (i = 0; i < 100; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\t");

    for (i = lastStart; i < dataSize; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

    for (i = 0; i < 3; ++i)
    {
        int *dataSrc, *dataCopy;
        int dataSize = parseData(fileNames[i], &dataSrc);

        if (dataSize <= 0)
            continue;

        dataCopy = (int *)malloc(sizeof(int) * dataSize);

        printf("---------------------------\n");
        printf("Dataset Size: %d\n", dataSize);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(dataCopy, dataSize);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("   runtime               : %.1lf\n", cpu_time_used);
        printf("   extraMemoryAllocated  : %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        printf("Insertion Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(dataCopy, dataSize);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("   runtime               : %.1lf\n", cpu_time_used);
        printf("   extraMemoryAllocated  : %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        printf("Bubble Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(dataCopy, dataSize);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("   runtime               : %.1lf\n", cpu_time_used);
        printf("   extraMemoryAllocated  : %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        printf("Merge Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(dataCopy, 0, dataSize - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("   runtime               : %.1lf\n", cpu_time_used);
        printf("   extraMemoryAllocated  : %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        free(dataCopy);
        free(dataSrc);
    }
}
