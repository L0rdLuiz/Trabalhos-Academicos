#include <iostream>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

void preencherVetor(int* vetor, int TAM, int caso) {
    switch (caso) {
        case 1: // Melhor caso - Ordenado crescente
            for (int i = 0; i < TAM; i++) {
                vetor[i] = i + 1;
            }
            break;

        case 2: // Pior caso - Ordenado decrescente
            for (int i = 0; i < TAM; i++) {
                vetor[i] = TAM - i;
            }
            break;

        case 3: // Aleatório
            for (int i = 0; i < TAM; i++) {
                vetor[i] = rand() % 100 + 1;
            }
            break;

        default:
            cout << "Opção inválida para ordenação." << endl;
            break;
    }
}

void insertionSort(int* vetor, int TAM) {
    for (int i = 1; i < TAM; i++) {
        int chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

void shellSort(int* vetor, int TAM) {
    for (int gap = TAM / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < TAM; i++) {
            int temp = vetor[i];
            int j;

            for (j = i; j >= gap && vetor[j - gap] > temp; j -= gap) {
                vetor[j] = vetor[j - gap];
            }

            vetor[j] = temp;
        }
    }
}

void bubbleSort(int* vetor, int TAM) {
    for (int i = 0; i < TAM - 1; i++) {
        for (int j = 0; j < TAM - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                swap(vetor[j], vetor[j + 1]);
            }
        }
    }
}

int partition(int* vetor, int low, int high) {
    int pivot = vetor[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (vetor[j] < pivot) {
            i++;
            swap(vetor[i], vetor[j]);
        }
    }
    swap(vetor[i + 1], vetor[high]);
    return i + 1;
}

void quickSort(int* vetor, int low, int high) {
    if (low < high) {
        int pi = partition(vetor, low, high);
        quickSort(vetor, low, pi - 1);
        quickSort(vetor, pi + 1, high);
    }
}

void selectionSort(int* vetor, int TAM) {
    for (int i = 0; i < TAM - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < TAM; j++) {
            if (vetor[j] < vetor[minIndex]) {
                minIndex = j;
            }
        }
        swap(vetor[i], vetor[minIndex]);
    }
}

void heapify(int* vetor, int TAM, int i) {
    int largest = i;       // Inicializa como raiz
    int left = 2 * i + 1;  // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Verifica se o filho esquerdo é maior que a raiz
    if (left < TAM && vetor[left] > vetor[largest]) {
        largest = left;
    }

    // Verifica se o filho direito é maior que o maior até agora
    if (right < TAM && vetor[right] > vetor[largest]) {
        largest = right;
    }

    // Troca e continua para o subárvore afetado
    if (largest != i) {
        swap(vetor[i], vetor[largest]);
        heapify(vetor, TAM, largest);
    }
}

void heapSort(int* vetor, int TAM) {
    // Constrói o heap máximo
    for (int i = TAM / 2 - 1; i >= 0; i--) {
        heapify(vetor, TAM, i);
    }

    // Extrai os elementos do heap
    for (int i = TAM - 1; i >= 0; i--) {
        swap(vetor[0], vetor[i]);
        heapify(vetor, i, 0);
    }
}

void merge(int* vetor, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; i++) {
        L[i] = vetor[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = vetor[mid + 1 + j];
    }

    // Une os arrays temporários
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* vetor, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vetor, left, mid);
        mergeSort(vetor, mid + 1, right);

        merge(vetor, left, mid, right);
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    int ordenacao = 0;
    int repeticoes = 0;
    bool menu = true;

    do {
        system("cls");
        cout << "Algoritmos de Ordenação de Vetores" << endl << endl;
        cout << "Selecione um método:" << endl << endl;
        cout << "1. Insertion Sort" << endl;
        cout << "2. Shellsort" << endl;
        cout << "3. Bubble Sort" << endl;
        cout << "4. Quick Sort" << endl;
        cout << "5. Selection Sort" << endl;
        cout << "6. Heapsort" << endl;
        cout << "7. Mergesort" << endl;
        cout << "8. Sair" << endl;
        cin >> ordenacao;

        switch (ordenacao) {
            case 1: {
                // Insertion Sort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    insertionSort(vetor, TAM);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // Em milissegundos
                    tempoTotal += duracao;

                    delete[] vetor; // Liberar memória alocada
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do Insertion Sort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }

            case 2: {
                // Shellsort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    shellSort(vetor, TAM);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // Em milissegundos
                    tempoTotal += duracao;

                    delete[] vetor; // Liberar memória alocada
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do ShellSort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }
            case 3: {
                // Bubble sort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    bubbleSort(vetor, TAM);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
                    tempoTotal += duracao;

                    delete[] vetor;
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do bubbleSort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }
            case 4:{
                // QuickSort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    quickSort(vetor, 0, TAM - 1);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // Em milissegundos
                    tempoTotal += duracao;

                    delete[] vetor; // Liberar memória alocada
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do QuickSort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }
            case 5:{
                // Selection Sort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    selectionSort(vetor, TAM);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // Em milissegundos
                    tempoTotal += duracao;

                    delete[] vetor; // Liberar memória alocada
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do SelectionSort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }
            case 6:{
                // HeapSort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    heapSort(vetor, TAM);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // Em milissegundos
                    tempoTotal += duracao;

                    delete[] vetor; // Liberar memória alocada
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do HeapSort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }
            case 7:{
                // MergeSort
                int TAM;
                cout << "Qual tamanho do vetor você quer?" << endl;
                cin >> TAM;

                if (TAM <= 0) {
                    cout << "Tamanho inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                cout << "Qual ordenação você quer?" << endl;
                cout << "1. Melhor caso (Ordenado)" << endl;
                cout << "2. Pior caso (Decrescente)" << endl;
                cout << "3. Aleatório" << endl;
                int caso;
                cin >> caso;

                cout << "Quantas vezes você quer repetir o processo para calcular a média?" << endl;
                cin >> repeticoes;

                if (repeticoes <= 0) {
                    cout << "Número de repetições inválido. Tente novamente." << endl;
                    system("pause");
                    break;
                }

                double tempoTotal = 0.0;

                for (int r = 0; r < repeticoes; r++) {
                    int* vetor = new int[TAM];
                    preencherVetor(vetor, TAM, caso);

                    auto inicio = high_resolution_clock::now();
                    mergeSort(vetor, 0, TAM-1);
                    auto fim = high_resolution_clock::now();

                    double duracao = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // Em milissegundos
                    tempoTotal += duracao;

                    delete[] vetor; // Liberar memória alocada
                }

                double tempoMedio = tempoTotal / repeticoes;

                cout << "Tempo médio de execução do mergeSort: " << tempoMedio << " ms" << endl;
                system("pause");
                break;
            }

            case 8:
                // Sair
                menu = false;
                break;

            default:
                cout << "Opção inválida. Tente novamente." << endl;
                system("pause");
                break;
        }
    } while (menu);

    cout << "Encerrando o programa. Até mais!" << endl;
    return 0;
}
