#include <stdio.h>

int mult(int base, int exp)
{

    int r = 0;
    if (exp == 0)
    {
        return 1;
    }
    else

        r = base * mult(base, exp - 1);

    return r;
}

int main()
{

    int resultado, base, exp;
    scanf("%i %i", &base, &exp);

    resultado = mult(base, exp);
    printf("Digite a base e o expoente inteiros: Resultado: %i", resultado);

    printf("\n");
    return 0;
}