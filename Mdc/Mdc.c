//FRANCISCO ABREU GONCALVES-  AEDS I - PROFA. NATAILA BATISTA

#include <stdio.h>


int mdc(int a, int b){ // FUNCAO QUE CALCULA O MDC
	if(b==0){
		return a; // O MDC ENTRE UM NUMERO QUALQUER E 0 EH O PROPRIO NUMERO
	}
	else if(a==0){
		return b;
	}else 
		return mdc(b,a%b); //ENQUANTO O RESTO NAO FOR 0, A FUNCAO CHAMA ELA MESMA
}

int main(){
	int a; // PRIMEIRO NUMERO DO MDC
	int b; // SEGUNDO NUMERO DO MDC
	printf("Digite dois numeros inteiros: ");
	scanf("%d %d", &a, &b);
	printf("Resultado: %d",mdc(a,b));

}
