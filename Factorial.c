/* FRANCISCO ABREU GONÇALVES AEDSI */
// PROGRAMA QUE CALCULA FATORIAL DE NUMEROS GRANDES

#include <stdio.h>

#define PADRAO 40000

int CalculaTamanho(int *resultado){
	int contador = 0;
	while(resultado[PADRAO-contador]==0){ //conta quantos zeros a esquerda do resultado existem
		contador++;	
	}
	return PADRAO - contador; // retorna o tamanho do resultado
}

void ZeraExpoente(int *expoente){
	for(int i=0;i<PADRAO;i++){
		expoente[i] = 0;
	}
}

void AcrescentaValor(int valor,int numero,int *resultado, int *expoente,int j){	
	if(valor>9){ //caso a multiplicacao seja maior que 9, o segundo algarismo deve passar como expoente da proxima posicao
		resultado[j] = valor%10; //primeiro algarismo fica como valor da posicao atual
		expoente[j+1] = valor/10; 
	}
	else{
		resultado[j] = valor;//se a multiplicacao foi menor que 10, o unico algarismo fica na posicao atual
	}
	
}

void AcrescentaExpoente(int *resultado, int *expoente){
	int soma;
	for(int i=0;i<PADRAO;i++){ // percorre ambos os vetores
		soma = resultado[i] + expoente[i]; 	
		if(soma>9){ // se a soma for maior que 9, o segundo algarismo soma com o expoente da proxima posicao
			expoente[i+1] += soma/10;
			resultado[i] = soma%10; //primeiro algarismo fica como valor da posicao atual
		}
		else 
			resultado[i] = soma;//se a soma foi menor qur 10, o unico algarismo fica na posicao atual
	}

}

void PreencheVetor(int *resultado, int *expoente ){
	for(int i=0;i<PADRAO;i++){
		resultado[i] = 0;
		expoente[i] = 0;
		
	}
}

void ImprimeResultado(int *resultado,int tamanho){
	for(int i=0;i<=tamanho;i++){
		printf("%d",resultado[tamanho-i]); // imprime o vetor de tras para frente, ja que o algarismo mais significativo esta na ultima posicao
	}
	printf("\n");
}

void CalculaFatorial(int numero,int *resultado, int *expoente){
	int valor,i,j,tamanho; 
	for(i=1;i<=numero;i++){ // loop que realiza a multiplicacao do fatorial comecando por: 1x2x3x4 ...xn
		for(j=0;j<PADRAO;j++){ //loop que percorre o vetor resultado
			valor = i*resultado[j]; //multiplicacao do numero em seu estado i com uma certa posicao no vetor resultado
			if(valor>0){ // se a multiplicacao nao for zero
				AcrescentaValor(valor,numero,resultado,expoente,j);	
			}
		}
		AcrescentaExpoente(resultado,expoente); // apos a multiplicacao de um estado do numero por todas as posicoes do vetor resultado,
							//soma-se os expoentes resultantes dessa multiplicacao com o vetor resultado
		ZeraExpoente(expoente); // a cada ciclo de multiplicacao, zera-se os expoentes
	}
	tamanho = CalculaTamanho(resultado); //armazena o numero de posicoes do resultado
	printf("Resultado: ");
	ImprimeResultado(resultado,tamanho); // imprime o resultado
}

int main(){
	int resultado[PADRAO]; //vetor que sera armazenado o resultado do fatorial
	int expoente[PADRAO]; //vetor que armazena os expoentes de uma multiplicacao ou adicao
	int numero; // variavel que armazena o numero do fatorial
	PreencheVetor(resultado,expoente); //inicia os vetores em zero
	resultado[0] = 1; // 0! = 1;
	printf("Digite um numero inteiro: ");
	scanf("%d",&numero);
	CalculaFatorial(numero,resultado,expoente);
}
