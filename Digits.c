//FRANCISCO ABREU GONCALVES-  AEDS I - PROFA. NATAILA BATISTA

#include <stdio.h> 

int Digitos(int num){ // Funcao que calcula a quantidade de digitos do numero
    int cont; //Varivel que armazena o contador 
    if(num < 10){ // Se o numero possuir apenas um digito
        cont = 1; // Conta 1
    }else{ // Se possuir mais que um digito
        cont = 1; // Conta 1
        cont = cont + Digitos(num/10); // Chama a funcao novamente, mas o numero possui menos 1 digito
    }
    return cont;
}

int main(){
    int num; // Variavel que armazena o valor do numero
    printf("Digite um numero inteiro: ");
    scanf("%d",&num);

    printf("Resultado: %d", Digitos(num));

}