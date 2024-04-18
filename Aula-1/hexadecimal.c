#include <stdio.h>

// Aula 1 - decimal para hexadecimal

int main()
{
    int numero;
    int i = 0;
    char caracteres[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char resto[100];

    printf("Digite o numero em decimal: ");
    scanf(" %i", &numero);

    while (numero > 0)
    {
        resto[i] = caracteres[numero % 16];
        numero /= 16;
        i++;
    }

    printf("O numero hexadecimal: ");
    for (i = i - 1; i >= 0; i--)
    {
        printf("%c", resto[i]);
    }

    return 0;
}
