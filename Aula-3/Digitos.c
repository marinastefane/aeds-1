#include <stdio.h>

int digitos(int N){
    
    static int count = 0;
    count++;
    if (N < 10)
    {
        return count;
    }
    else
        return digitos(N / 10);
}

int main(){

    int resultado, N;
    scanf("%i", &N);

    resultado = digitos(N);
    printf("Digite um numero inteiro: Resultado: %i", resultado);

    printf("\n");
    return 0;
}