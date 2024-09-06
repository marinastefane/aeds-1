/****************

LAED1 - Projeto (Parte III) - Detecção de impedimentos na pista

Alunos(as): Letícia Vaz Pires e Marina Stefane Candido Delfino

Data: 04/09/2024
****************/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
        printf("Chave: %d, NumElementos: %d, PontoMedio: %d\n", Aux->Item.Chave, Aux->Item.NumElementos, Aux->Item.PontoMedio);
        Aux = Aux->Prox;
    }
}

int mapearCor(int valor)
{
    if (valor == 0)
        return 1; // preto
    else if (valor == 128)
        return 2; // branco
    else if (valor == 255)
        return 3; // vermelho
    return -1;    // desconhecido
}

int unico(int vet[], int N, int V)
{
    // Verifica se o valor já está no vetor
    if (N == 0)
        return 1; // Sempre retorna 1 para o primeiro elemento

    // Verifica se o último valor do vetor é igual ao valor atual
    return vet[N - 1] != V;
}

int verificaPadrao(int *elementos, int N)
{
    // Padrão esperado da pista
    int padrao[] = {1, 3, 2, 3, 1};
    int tamanhoPadrao = sizeof(padrao) / sizeof(padrao[0]);
    bool impedimento = false;

    // Percorre o vetor procurando o padrão
    for (int i = 0; i <= N - tamanhoPadrao; i++)
    {
        bool padraoCorreto = true;
        for (int j = 0; j < tamanhoPadrao; j++)
        {
            if (elementos[i + j] != padrao[j])
            {
                if (padrao[j] == 2 && elementos[i + j] != 2)
                {
                    impedimento = true;
                }
                else
                {
                    padraoCorreto = false;
                    break;
                }
            }
        }
        if (padraoCorreto)
            return 0; // Padrão encontrado
    }

    if (N <= 4)
    {
        return 2;
    }

    return 1; // Impedimento
}

int main()
{

    int N, L;
    int contagemImpedimentos = 0;
    int pistaCorreta = 0;
    int pistaIncorreta = 0;

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
            int v;
            scanf("%d", &v);
            elementos[j] = mapearCor(v);
        }

        int *valorUnico = (int *)malloc(N * sizeof(int));
        int k = 0;
        for (int j = 0; j < N; j++)
        {
            if (unico(valorUnico, k, elementos[j]))
            {
                valorUnico[k] = elementos[j];
                k++;
            }
        }

        // TESTES-------------------------------------------
        printf("Elementos do perfil %d: ", i + 1);
        for (int j = 0; j < N; j++)
        {
            printf("%d ", elementos[j]);
        }
        printf("\n");

        printf("Elementos unicos %d: ", i + 1);
        for (int j = 0; j < k; j++)
        {
            printf("%d ", valorUnico[j]);
        }
        printf("\n");

        //---------------------------------------------------

        // Verifica se houve impedimento na pista
        int resultado = verificaPadrao(valorUnico, k);
        if (resultado == 0)
        {
            pistaCorreta++; // Incrementa o contador de pistas corretas
            printf("Resultado: Pista sem impedimento.\n");
        }
        else if (resultado == 1)
        {
            contagemImpedimentos++; // Incrementa o contador de impedimentos
            printf("Resultado: Pista com impedimento.\n");
        }
        else if (resultado == 2)
        {
            pistaIncorreta++; // Incrementa o contador de pista incorreta
            printf("Resultado: Pista Incorreta.\n");
        }

        printf("Contagem de pistas incorretas: %d \n", pistaIncorreta);

        free(elementos);
        free(valorUnico);
    }

    // verifica 70% do padrao
    float proporcao = (float)pistaIncorreta / L;
    printf("Proporcao: %f \n", proporcao);

    if (proporcao > 0.3)
    {
        printf("Resultado final: Formato da pista nao estimado..\n");
    }
    else
    {
        if (contagemImpedimentos > 0)
        {
            printf("Resultado final: Pista com impedimento.\n");
        }
        else if (pistaCorreta >= 0.7 * L)
        {
            printf("Resultado final: Pista sem impedimento.\n");
        }
        else
        {
            printf("Resultado final: Formato da pista nao estimado..\n");
        }
    }

    return 0;
}