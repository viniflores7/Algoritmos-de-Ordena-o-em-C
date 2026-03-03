#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// FUNÇÕES AUXILIARES
// ==========================================

// Imprime o array (Requisito 1)
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Copia o array original para garantir testes justos nos mesmos dados
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Troca dois elementos de posição
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// ==========================================
// ALGORITMOS DE ORDENAÇÃO
// ==========================================

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 4. Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 5. Merge Sort (e função auxiliar merge)
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
    
    free(L); free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, r);
    }
}

// 6. Quick Sort (e função auxiliar partition)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// ==========================================
// FUNÇÃO DE TESTE E MEDIÇÃO
// ==========================================
void testAlgorithm(int op, int originalArr[], int n, int isVisual) {
    int* arr = (int*)malloc(n * sizeof(int));
    copyArray(originalArr, arr, n); // Usa o mesmo conjunto de dados (Requisito 2)

    if (isVisual) {
        printf("Array ANTES: ");
        printArray(arr, n);
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    switch (op) {
        case 1: bubbleSort(arr, n); break;
        case 2: selectionSort(arr, n); break;
        case 3: insertionSort(arr, n); break;
        case 4: shellSort(arr, n); break;
        case 5: mergeSort(arr, 0, n - 1); break;
        case 6: quickSort(arr, 0, n - 1); break;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if (isVisual) {
        printf("Array DEPOIS: ");
        printArray(arr, n);
    }
    
    printf("-> Tempo de execucao: %f segundos\n\n", cpu_time_used);
    free(arr);
}

// ==========================================
// MAIN E MENU INTERATIVO
// ==========================================
int main() {
    int choice = 0;
    int sizeVisual = 10;
    int sizePerf = 20000; // Array grande para evidenciar diferença de tempo
    
    int visualArr[10] = {64, 34, 25, 12, 22, 11, 90, 88, 5, 42};
    int* perfArr = (int*)malloc(sizePerf * sizeof(int));
    
    // Alimenta array de performance com dados aleatórios
    srand(time(NULL));
    for (int i = 0; i < sizePerf; i++) {
        perfArr[i] = rand() % 50000;
    }

    while (choice != 8) {
        printf("=========================================\n");
        printf("       MENU DE ORDENACAO (C/C++)         \n");
        printf("=========================================\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Shell Sort\n");
        printf("5. Merge Sort\n");
        printf("6. Quick Sort\n");
        printf("7. Testar TODOS no Modo Performance\n");
        printf("8. Sair\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6) {
            printf("\n--- MODO VISUAL (10 Elementos) ---\n");
            testAlgorithm(choice, visualArr, sizeVisual, 1);
            
            printf("--- MODO PERFORMANCE (%d Elementos) ---\n", sizePerf);
            testAlgorithm(choice, perfArr, sizePerf, 0);
        } 
        else if (choice == 7) {
            printf("\nComparando todos com o mesmo array de %d elementos...\n", sizePerf);
            const char* names[] = {"", "Bubble", "Selection", "Insertion", "Shell", "Merge", "Quick"};
            for(int i = 1; i <= 6; i++) {
                printf("%s Sort ", names[i]);
                testAlgorithm(i, perfArr, sizePerf, 0);
            }
        }
        else if (choice != 8) {
            printf("\nOpcao invalida. Tente novamente.\n\n");
        }
    }
    
    free(perfArr);
    return 0;
}
