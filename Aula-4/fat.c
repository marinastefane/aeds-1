#include <stdio.h>
#include <stdlib.h>

#define TAM 36000

int main()
{
    int num, num1, v_resultado[TAM] = {0};
    int i, resultado = 0, operacao;
    int tamanho = 1;

    scanf("%d", &num);

    printf("Resultado: ");
    if (num < 2)
    {
        printf("1");
    }
    else
    {
        v_resultado[0] = 1; // inicializa a primeira posição em 1

        for (num1 = 2; num1 <= num; num1++)
        {

            for (i = 0; i <= tamanho; i++)
            {
                operacao = v_resultado[i] * num1 + resultado;
                resultado = operacao / 10;
                v_resultado[i] = operacao % 10;
            }
            while (resultado != 0)
            {
                tamanho++;
                v_resultado[tamanho] = resultado % 10;
                resultado /= 10;
            }
        }

        for (int j = tamanho; j >= 0; j--)
        {
            printf("%d", v_resultado[j]);
        }
    }

    printf("\n");
    return 0;
}