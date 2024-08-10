#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}


int mochila(int w1, int peso[], int preco[], int n)
{
    int valor_maximo[n + 1][w1 + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= w1; w++)
        {
            if (i == 0 || w == 0)
            {
                valor_maximo[i][w] = 0;
            }
            else if (peso[i - 1] <= w)
            {
                valor_maximo[i][w] = max(preco[i-1] + valor_maximo[i-1][w - peso[i-1]], valor_maximo[i-1][w]);
                
            }
            else
            {
                valor_maximo[i][w] = valor_maximo[i - 1][w];
            }
        }
    }

    return valor_maximo[n][w1];
}

int main()
{
    int w1, n, peso, preco;
    // tamanho da mochila
    scanf("%d", &w1);

    // numero de itens
    scanf("%d", &n);

    int vpeso[n], vpreco[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &peso, &preco);
        vpeso[i] = peso;
        vpreco[i] = preco;
    }
    int x, rpeso = 0, rpreco = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &x);
                if(x == 1){
                    rpeso += vpeso[i];
                    rpreco += vpreco[i];
                }
        }
        

    int valormax = mochila(w1, vpeso, vpreco, n);

    if(w1 < rpeso){
        printf("Solucao inviavel.");
    }
    else {
        if (rpreco == valormax){
            printf("Solucao otima.");
        }
        else{
            printf("Solucao viavel mas nao otima.");
        }
    }
    printf("\n");
    return 0;
}