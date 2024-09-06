/****************

LAED1 - Projeto (Parte II) - Busca por padrão em sequência

Alunos(as): Letícia Vaz Pires e Marina Stefane Candido Delfino

Data: 30/08/2024

****************/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

typedef int TipoChave;

typedef struct
{
    int Chave;        // Tipo do segmento
    int NumElementos; // Número de elementos no segmento
    int PontoMedio;   // Ponto médio do segmento
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;
} TipoLista;

/* Função para inicializar uma lista vazia */
void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

/* Verifica se a lista está vazia */
int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

/* Insere um item na lista */
void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

/* Função para imprimir a lista */
void Imprime(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        Aux = Aux->Prox;
    }
}
int mapearCor(int valor)
{
    if (valor == 0)
        return 1;
    else if (valor == 128)
        return 2;
    else if (valor == 255)
        return 3;
    return -1;
}

int verifica70padrao(int x, int total_linhas)
{
    return ((float)x / total_linhas) >= 0.7;
}

int calcularPontosMedios(int *elementos, int N, TipoLista *lista)
{
    int i = 0, chave = 1;
    while (i < N)
    {
        int tipo = mapearCor(elementos[i]);
        if (tipo == 0)
        {
            i++;
            continue;
        }

        int inicio = i;
        while (i < N && mapearCor(elementos[i]) == tipo)
        {
            i++;
        }
        int fim = i - 1;

        if (tipo == 2)
        {
            TipoItem item;
            item.Chave = chave++;
            item.NumElementos = fim - inicio + 1;
            item.PontoMedio = (inicio + fim) / 2;
            Insere(item, lista);
        }
    }
    return (Vazia(*lista) ? 0 : 1); // Retorna 1 se a lista não estiver vazia
}

int estimarFormato(TipoLista listaPontosMedios, int L, int N)
{
    if (Vazia(listaPontosMedios))
    {
        return 0; // Lista vazia
    }

    int esquerda = 0, direita = 0, reta = 0;
    TipoApontador atual = listaPontosMedios.Primeiro->Prox;

    while (atual->Prox != NULL)
    {
        TipoApontador proximo = atual->Prox;

        // printf("Comparando: Atual PontoMedio = %d, Proximo PontoMedio = %d\n",
        //        atual->Item.PontoMedio, proximo->Item.PontoMedio);

        int a = 2 * N / 950;

        if (proximo->Item.PontoMedio < (atual->Item.PontoMedio - a))
        {
            direita++;
        }
        else if (proximo->Item.PontoMedio > (atual->Item.PontoMedio + a))
        {
            esquerda++;
        }
        else
        {
            reta++;
        }
        atual = proximo;
    }

    int totalComparacoes = esquerda + direita + reta;

    // Verificar se há comparações suficientes
    if (totalComparacoes < 2) // Número de comparações insuficiente para estimar
    {
        return 0; // Formato da pista não estimado
    }

    // printf("Esquerda: %d, Direita: %d, Reta: %d\n", esquerda, direita, reta);

    if (esquerda > direita && esquerda >= reta)
    {
        return 1;
    }
    else if (direita > esquerda && direita >= reta)
    {
        return 2;
    }
    else if (reta >= esquerda && reta >= direita)
    {
        return 3;
    }
    return 0;
}

int main()
{

    int N, L, aux = 0;

    TipoLista lista;
    FLVazia(&lista);

    // Leitura do número de elementos do vetor
    scanf("%d", &L);

    for (int i = 0; i < L; i++)
    {
        scanf("%d", &N);

        // Aloca memória para o vetor de elementos
        int *elementos = (int *)malloc(N * sizeof(int));
        if (elementos == NULL)
        {
            perror("Falha ao alocar memoria");
            return 1;
        }

        // Leitura dos elementos do vetor
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &elementos[j]);
        }
        aux += calcularPontosMedios(elementos, N, &lista);
        free(elementos);
    }

    //   Imprime(lista);

    int resultado = estimarFormato(lista, L, N);
    // int r = verifica70padrao (x, total_linhas);

    if (resultado == 0)
    {
        printf("Resultado: Formato da pista nao estimado.\n");
    }
    else if (resultado == 1)
    {
        printf("Resultado: Curva a esquerda.\n");
    }
    else if (resultado == 2)
    {
        printf("Resultado: Curva a direita.\n");
    }
    else if (resultado == 3)
    {
        printf("Resultado: Pista em linha reta.\n");
    }
    else
    {
        printf("Resultado: Formato da pista nao estimado.\n");
    }

    // Libera memória

    return 0;
}