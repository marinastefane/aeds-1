#include <stdio.h>

// remove os elementos duplicados
int duplicados(int v[], int j)
{
    if (j == 0) // se for 0, retorna 0
        return 0;

    int prox = 0;

    for (int i = 1; i < j; i++)
    {
        if (v[i] != v[prox])
        {
            prox++;
            v[prox] = v[i];
        }
    }

    return prox + 1;
}

int main()
{
    int j;
    printf("digite o numero N de elementos: ");
    scanf("%d", &j);

    int v[j];
    printf("digite N elementos: \n");
    for (int i = 0; i < j; i++)
    {

        scanf("%d", &v[i]);
    }

    int unico = duplicados(v, j);

    printf("quantidade de elementos unicos: %d\n", unico);

    // imprime os elementos unicos
    printf("sequencia de elementos unicos: ");
    for (int i = 0; i < unico; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
