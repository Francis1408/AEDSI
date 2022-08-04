//FRANCISCO ABREU GONCALVES-  AEDS I - PROFA. NATAILA BATISTA

#include <stdio.h>

int mult(int base, int exp){ // Funcao que calcula a potenciacao
	int resultado; // Resultado da potenciacao
	if(exp==0){ // Se o expoente e igual a zero
		resultado = 1; // Qualquer numero elevado a zero sera 1
	}else{
		resultado = base * mult(base, exp-1); // Caso o expoente n seja zero, a funcao ira chama-la
	}                                        // novamente, porem com o expoente reduzido em 1 
	return resultado;
}

int main(){
	int base; // Variavel que armazena a base
	int exp; // Variavel que armazena o expoente
	printf("Digite a base e o expoente inteiros: ");
	scanf("%d %d", &base, &exp);
	printf("Resultado: %d",mult(base, exp));


}

