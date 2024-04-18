#include <stdio.h>

int mdc(int a, int b){

    if (b != 0)
    {
        return (b, a % b);
    }
    else
        return a;
}

int main(){

    int a, b, resultado;
    scanf("%i %i", &a, &b);

    resultado = mdc(a, b);
    printf("Digite dois numeros inteiros: Resultado: %d", resultado);

    printf("\n");
    return 0;
}