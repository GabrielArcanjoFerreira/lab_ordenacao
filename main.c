#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
#include <stdbool.h>

void swap2(uint64_t *i, uint64_t *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

void crescente(int *v, int n)
{
    for (uint64_t i = 0; i < n; i++)
    {
        v[i] = i;
    }
}

void crescente2(uint64_t *v, uint64_t n)
{
    for (uint64_t i = 0; i < n; i++)
    {
        v[i] = i;
    }
}

void decrescente(uint64_t *v, uint64_t n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = n - 1 - i;
    }
}

void aleatorio(uint64_t *v, uint64_t n)
{
    crescente2(v, n);
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        swap2(&v[i], &v[rand() % n]);
    }
}

int entradaPadrao(int *v)
{
    int n;
    scanf("%i", &n);
    v = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &v[i]);
    }
    return n;
}

void mostrar(int *v, int n)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("] \n");
}

bool isOrdenado(int *v, int n)
{
    bool resp = true;
    for (int i = 1; i < n; i++)
    {
        if (v[i - 1] > v[i])
        {
            i = n;
            resp = false;
        }
    }
    return resp;
}

int getMaior(uint64_t *array, int n)
{
    int maior = array[0];

    for (int i = 0; i < n; i++)
    {
        if (maior < array[i])
        {
            maior = array[i];
        }
    }
    return maior;
}

int getMaiorFilho(uint64_t *array, uint64_t i, uint64_t tamHeap)
{
    uint64_t filho;
    if (2 * i == tamHeap || array[2 * i] > array[2 * i + 1])
    {
        filho = 2 * i;
    }
    else
    {
        filho = 2 * i + 1;
    }
    return filho;
}

void constroi(uint64_t *array, uint64_t tamHeap)
{
    for (uint64_t i = tamHeap; i > 1 && array[i] > array[i / 2]; i /= 2)
    {
        swap2(array + i, array + i / 2);
    }
}

void reconstroi(uint64_t *array, uint64_t tamHeap)
{
    uint64_t i = 1;
    while (i <= (tamHeap / 2))
    {
        int filho = getMaiorFilho(array, i, tamHeap);
        if (array[i] < array[filho])
        {
            swap2(array + i, array + filho);
            i = filho;
        }
        else
        {
            i = tamHeap;
        }
    }
}

void bolha(uint64_t array[], int n)
{
    int i, j;
    for (i = (n - 1); i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap2(&array[j], &array[j + 1]);
            }
        }
    }
}

void countingsort(uint64_t *array, int n)
{
    //Array para contar o numero de ocorrencias de cada elemento
    int tamCount = getMaior(array, n) + 1;
    int count[tamCount];
    int ordenado[n];

    //Inicializar cada posicao do array de contagem
    for (int i = 0; i < tamCount; count[i] = 0, i++)
        ;

    //Agora, o count[i] contem o numero de elemento iguais a i
    for (int i = 0; i < n; count[array[i]]++, i++)
        ;

    //Agora, o count[i] contem o numero de elemento menores ou iguais a i
    for (int i = 1; i < tamCount; count[i] += count[i - 1], i++)
        ;

    //Ordenando
    for (int i = n - 1; i >= 0; ordenado[count[array[i]] - 1] = array[i], count[array[i]]--, i--)
        ;

    //Copiando para o array original
    for (int i = 0; i < n; array[i] = ordenado[i], i++)
        ;
}

void heapsort(uint64_t *array, uint64_t n)
{
    //Alterar o vetor ignorando a posicao zero

    uint64_t *arrayTmp = malloc((n + 1) * sizeof(uint64_t));

    for (uint64_t i = 0; i < n; i++)
    {
        arrayTmp[i + 1] = array[i];
    }

    //Contrucao do heap
    for (uint64_t tamHeap = 2; tamHeap <= n; tamHeap++)
    {
        constroi(arrayTmp, tamHeap);
    }

    //Ordenacao propriamente dita
    uint64_t tamHeap = n;
    while (tamHeap > 1)
    {
        swap2(arrayTmp + 1, arrayTmp + tamHeap--);
        reconstroi(arrayTmp, tamHeap);
    }

    //Alterar o vetor para voltar a posicao zero
    for (uint64_t i = 0; i < n; i++)
    {
        array[i] = arrayTmp[i + 1];
    }
    free(arrayTmp);
}

void insercao(uint64_t *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        int tmp = array[i];
        int j = i - 1;

        while ((j >= 0) && (array[j] > tmp))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = tmp;
    }
}

void intercalar(uint64_t *array, int esq, int meio, int dir)
{
    int n1, n2, i, j, k;

    //Definir tamanho dos dois subarrays
    n1 = meio - esq + 1;
    n2 = dir - meio;

    int *a1 = (int *)malloc((n1 + 1) * sizeof(int));
    int *a2 = (int *)malloc((n2 + 1) * sizeof(int));

    //Inicializar primeiro subarray
    for (i = 0; i < n1; i++)
    {
        a1[i] = array[esq + i];
    }

    //Inicializar segundo subarray
    for (j = 0; j < n2; j++)
    {
        a2[j] = array[meio + j + 1];
    }

    //Sentinela no final dos dois arrays
    a1[i] = a2[j] = 0x7FFFFFFF;

    //Intercalacao propriamente dita
    for (i = j = 0, k = esq; k <= dir; k++)
    {
        array[k] = (a1[i] <= a2[j]) ? a1[i++] : a2[j++];
    }

    free(a1);
    free(a2);
}

void mergesortRec(uint64_t *array, int esq, int dir)
{
    if (esq < dir)
    {
        int meio = (esq + dir) / 2;
        mergesortRec(array, esq, meio);
        mergesortRec(array, meio + 1, dir);
        intercalar(array, esq, meio, dir);
    }
}

void mergesort(uint64_t *array, int n)
{
    mergesortRec(array, 0, n - 1);
}

void quicksortRec(uint64_t *array, int esq, int dir)
{
    int i = esq, j = dir;
    int pivo = array[(dir + esq) / 2];
    while (i <= j)
    {
        while (array[i] < pivo)
            i++;
        while (array[j] > pivo)
            j--;
        if (i <= j)
        {
            swap2(array + i, array + j);
            i++;
            j--;
        }
    }
    if (esq < j)
        quicksortRec(array, esq, j);
    if (i < dir)
        quicksortRec(array, i, dir);
}

void quicksort(uint64_t *array, int n)
{
    quicksortRec(array, 0, n - 1);
}

void selecao(uint64_t *array, int n)
{
    for (int i = 0; i < (n - 1); i++)
    {
        int menor = i;
        for (int j = (i + 1); j < n; j++)
        {
            if (array[menor] > array[j])
            {
                menor = j;
            }
        }
        swap2(&array[menor], &array[i]);
    }
}

void adaptado(uint64_t *array, int n)
{
    for (int i = 0; i < (n - 1); i++)
    {
        int menor = i;
        for (int j = (i + 1); j < n; j++)
        {
            if (array[menor] > array[j])
            {
                menor = j;
            }
        }
        for (; i != menor;)
        {
            swap2(&array[menor], &array[i]);
            break;
        }
        //if (i != menor)
        //    swap2(&array[menor], &array[i]);
    }
}

void insercaoPorCor(uint64_t *array, int n, int cor, int h)
{
    for (int i = (h + cor); i < n; i += h)
    {
        int tmp = array[i];
        int j = i - h;
        while ((j >= 0) && (array[j] > tmp))
        {
            array[j + h] = array[j];
            j -= h;
        }
        array[j + h] = tmp;
    }
}

void shellsort(uint64_t *array, int n)
{
    int h = 1;

    do
    {
        h = (h * 3) + 1;
    } while (h < n);

    do
    {
        h /= 3;
        for (int cor = 0; cor < h; cor++)
        {
            insercaoPorCor(array, n, cor, h);
        }
    } while (h != 1);
}

double get_memory_used_MB()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    return (double)info.PeakWorkingSetSize / (1024 * 1024);
}

void teste(uint64_t n, char ordem)
{

    clock_t start_time, end_time;
    double cpu_time_used, memory_used;
    size_t peakSize;

    uint64_t *array = (uint64_t *)malloc(n * sizeof(uint64_t));

    if (array == NULL)
    {
        printf("NAO TEM MEMORIA");
        exit(0);
    }
    else
    {
        //printf("TEM MEMORIA");
    }

    //Geracao do conjunto a ser ordenado

    switch (ordem)
    {
    case 'C':
        crescente2(array, n);
        break;
    case 'D':
        decrescente(array, n);
        break;
    case 'A':
        aleatorio(array, n);
        break;
    default:
        break;
    }
    crescente2(array, n);
    //decrescente(array, n);
    //aleatorio(array, n);

    start_time = clock();

    //Execucao do algoritmo de ordenacao

    //bolha(array, n);
    //countingsort(array, n);
    //heapsort(array, n);
    //insercao(array, n);
    //mergesort(array, n);
    //quicksort(array, n);
    //selecao(array, n);
    //shellsort(array, n);
    adaptado(array, n);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    memory_used = get_memory_used_MB();

    printf("%0.2fs - %0.2fMB\n", cpu_time_used, memory_used);

    free(array);
}

int main()
{
    char ordem;

    for (int i = 1; i <= 3; i++)
    {
        if (i == 1)
        {
            ordem = 'C';
        }
        else if (i == 2)
        {
            ordem = 'D';
        }
        else
        {
            ordem = 'A';
        }

        printf("\nADAPTADO -  %c \n", ordem);

        for (uint64_t n = 2000; n <= 128000; n *= 2)
        {
            printf("%d - ", n);
            teste(n, ordem);
        }
    }

    return 0;
}