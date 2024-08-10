#include <stdio.h>
#include <stdlib.h>


int unico(int vet[], int N, int V) {
    for (int i = 0; i < N; i++) {
        if (vet[i] == V)
            return 0;
    }
    return 1;
}


int ComparaSequencia(int vet[], int N, int V) {
    int aux;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (vet[i] < vet[j]) {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (vet[i] == V) {
            return i + 1;
        }
    }

    return -1;
}

int main()
{

    int N;

    // numero de elementos do vetor
    // printf("Digite o valor de N:");
    scanf("%d", &N);

    // aloca memoria para o vetor
    int *elementos = (int *)malloc(N * sizeof(int));
    if (elementos == NULL)
    {
        perror("Falha ao alocar memoria");
        return 1;
    }

    // numeros
    // printf("Digite os elementos do vetor separados por espaco: ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &elementos[i]);
    }

    // aloca memoria para valores unicos
    int *valorUnico = (int *)malloc(N * sizeof(int));
    int *ident = (int *)malloc(N * sizeof(int));
    if (valorUnico == NULL || ident == NULL)
    {
        perror("Falha ao alocar memoria");
        free(ident);
        free(elementos);
        free(valorUnico);
        return 1;
    }

   int k = 0;
    for (int i = 0; i < N; i++) {
        if (unico(valorUnico, k, elementos[i])) {
            valorUnico[k] = elementos[i];
            k++;
        }
    }

    // aloca memoria para matriz resultado
    int **matrizSegmentos = (int **)malloc(2 * sizeof(int *));
    if (matrizSegmentos == NULL)
    {
        perror("Falha ao alocar memoria");
        free(valorUnico);
        free(ident);
        free(elementos);
        return 1;
    }

    matrizSegmentos[0] = (int *)malloc(N * sizeof(int)); // tipos dos segmentos
    matrizSegmentos[1] = (int *)malloc(N * sizeof(int)); // tamanhos dos segmentos
    if (matrizSegmentos[0] == NULL || matrizSegmentos[1] == NULL)
    {
        perror("Falha ao alocar memoria");
        free(elementos);
        free(valorUnico);
        free(ident);
        free(matrizSegmentos);
        return 1;
    }

    int count = 1;               // num seg encontrados
    int aux = 0;                 // contador de elementos no seg atual
    int segAtual = elementos[0]; // valor do seg atual

    for (int i = 1; i < N; i++)
    {
        if (elementos[i] == segAtual)
        {
            count++;
        }
        else
        {
            matrizSegmentos[0][aux] = ComparaSequencia(valorUnico, k, segAtual);
            matrizSegmentos[1][aux] = count;
            aux++;
            segAtual = elementos[i];
            count = 1;
        }
    }

    // Adiciona o último segmento
    matrizSegmentos[0][aux] = ComparaSequencia(valorUnico, k, segAtual);
    matrizSegmentos[1][aux] = count;
    aux++;

    // imprime a matriz
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < aux; j++)
        {
            if (j < aux - 1)
                printf("%d ", matrizSegmentos[i][j]);
            else
                printf("%d", matrizSegmentos[i][j]);
        }
        printf("\n"); // Nova linha após cada linha da matriz
    }

    // liberar memoria
    free(elementos);
    free(valorUnico);
    free(ident);
    free(matrizSegmentos[0]);
    free(matrizSegmentos[1]);
    free(matrizSegmentos);

    // printf("\n");
    return 0;
}