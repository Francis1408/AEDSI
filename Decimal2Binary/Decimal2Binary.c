//FRANCISCO ABREU GONCALVES-  AEDS I - PROFA. NATAILA BATISTA


#include <stdio.h>
#include <stdlib.h>

void dec2bin(int dec){
    int resultado; // resultado do binario
    resultado = dec%2; // reultado igual ao resto da divisao do decimal por 2

    if(dec > 1){ // caso o decimal nao foi completamente dividido
        dec2bin(dec/2); // chama a funcao novamente, porem com o decimal reduzido pela divisao anterior 
        printf("%d",resultado); // imprime os outros bits
    }
    else{
        printf("%d",resultado); // imprime o bit mais significativo
    }
      
} 


int main(){
    int dec; // variavel do decimal
    printf("Digite um numero inteiro: ");
    scanf("%d", &dec); // insere o decimal
    printf("Resultado: ");
    dec2bin(dec); // funcao que convertera para binario
}