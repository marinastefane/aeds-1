/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as): Letícia Vaz Pires e Marina Stefane Candido Delfino

Data: 15/08/2024

****************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TipoChave;

typedef struct
{
  int Chave; // tipo do segmento
  // int Tipo;
  int NumElementos; // num elementos no segmento
  int PontoMedio;   // ponto medio do segmento
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

void FLVazia(TipoLista *Lista)
{
  Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

// void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
// { /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
//   TipoApontador q;
//   if (Vazia(*Lista) || p == NULL || p -> Prox == NULL)
//   { printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
//     return;
//   }
//   q = p -> Prox;
//   *Item = q -> Item;
//   p -> Prox = q -> Prox;
//   if (p -> Prox == NULL) Lista -> Ultimo = p;
//   free(q);
// }

void Imprime(TipoLista Lista)
{
  TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL)
  {
    printf("\nChave: %d, NumElementos: %d, PontoMedio: %d\n",
           Aux->Item.Chave, Aux->Item.NumElementos, Aux->Item.PontoMedio);
    Aux = Aux->Prox;
  }
}

// funcao para verificar o padrao na lista
int verificarPadrao(TipoLista *Lista)
{
  int padrao[] = {1, 3, 2, 3, 1};
  int i = 0;
  TipoApontador Aux = Lista->Primeiro->Prox;

  while (Aux != NULL)
  {
    if (Aux->Item.Chave == padrao[i])
    {
      i++;
      if (i == 5) // Se encontrar os 5 elementos na ordem correta
      {
        return 1;
      }
      Aux = Aux->Prox;
    }
    else
    {
      // Reinicia a busca do padrão a partir do primeiro elemento
      if (i == 0)
      {
        // Verifica se o elemento atual pode ser o início do padrão
        Aux = Aux->Prox;
      }
      else
      {
        i = 0;
      }
    }
  }
  return 0;
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

  TipoLista lista;
  FLVazia(&lista);

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
      TipoItem item;
      item.NumElementos = count;
      item.Chave = segAtual;
      item.PontoMedio = (aux + (aux + count - 1)) / 2;
      Insere(item, &lista);

      segAtual = elementos[i];
      count = 1;
      aux = i;
    }
  }
  // adicionar o ult seg
  TipoItem item;
  item.NumElementos = count;
  item.Chave = segAtual;
  item.PontoMedio = (aux + (aux + count - 1)) / 2;
  Insere(item, &lista);

  // imprimir se achou ou nao
  // verificar se existe o padrao

  if (verificarPadrao(&lista))
  {
    printf("Resultado: Padrao encontrado");
  }
  else
  {
    printf("Resultado: Padrao nao encontrado");
  }

  Imprime(lista);

  // liberar memoria
  free(elementos);

  // printf("\n");
  return 0;
}