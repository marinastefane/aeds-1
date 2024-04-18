#include <stdio.h>

void dec2bin(int dec){

    int r = 0;

    if (dec > 1)

    dec2bin(dec / 2);
    r = dec % 2;

    printf("%d", r);
}

int main(){

    int dec;
    scanf("%i", &dec);

    printf("Digite um numero inteiro: Resultado: ");
    dec2bin(dec);

    printf("\n");
    return 0;
}