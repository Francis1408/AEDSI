/*Francisco Abreu Goncalves AEDSI*/

#include <stdio.h>

#define PADRAO 1000

void Permutacao(char *mensagem, int tamanho){
	int indice = tamanho/2;	
	char aux1,aux2;
		for(int i=0;i<indice;i=i+4){ //Permuta os blocos de quatro em quatro posicoes(Primeiro-Ultimo/Terceiro-Antepenultimo...)
			aux1 = mensagem[i];
			aux2 = mensagem[i+1];
			mensagem[i] = mensagem[(tamanho-2)-i];
			mensagem[i+1] = mensagem[(tamanho-1)-i];
			mensagem[(tamanho-1)-i] = aux2;
			mensagem[(tamanho-2)-i] = aux1;
		}
}

void InverteBlocos(char *mensagem,int tamanho){
	char aux;
	if(tamanho%2!=0){ //Caso o numero de caracteres da string seja impar, deve-se adicionar um espaco no final dela
		mensagem[tamanho] = ' '; 
		mensagem[tamanho+1] = '\0';
	}
	for(int i=0;mensagem[i]!='\0';i=i+2){ //Troca de posicao os caracteres
		aux = mensagem[i];
		mensagem[i] = mensagem[i+1];
		mensagem[i+1] = aux; 
	}
	

}

void CifraDeCesar(char *mensagem){
	//OBS : os numeros a seguir sao valores dos caracteres segundo a tabela ASCII
	int diferenca;
	int i;
	for(i=0;mensagem[i]!='\0';i++){
		if(mensagem[i]!=' '){ //Caso o caractere n seja um espaco
			diferenca = mensagem[i] - 3; // O caractere novo sera a letra com tres casas atras do caractere antigo
			if(diferenca>=65 && diferenca <=90) // Caso a letra nao esteja nas extremidades do alfabeto(Maiusculo)
				mensagem[i] = diferenca;

			else if(diferenca>=97 && diferenca<=122)// Caso a letra nao esteja nas extremidades do alfabeto(Minusculo)
				mensagem[i] = diferenca;

			else{ //Caso esteja nas extremidades, deve-se voltar as tres casas e adicionar 26 para voltar ao final do alfabeto
				diferenca = diferenca + 26;
				mensagem[i] = diferenca;
			}
		}
	}
	mensagem[i-1] = '\0';// Reestabelecendo o final da String
}

void SubstituirEspacos(char *mensagem){
	for(int i=0;mensagem[i]!='\0';i++){ // for que pecorre a string
		if(mensagem[i]=='#')
			mensagem[i] = ' ';
		}
		
}

void Criptografia(char *mensagem,int tamanho){
	SubstituirEspacos(mensagem); // Funcao que substitui os #'s por espacos	
	CifraDeCesar(mensagem); //Funcao que aplica a cifra de Cesar 
	InverteBlocos(mensagem,tamanho);//Funcao que troca de posicao os caracteres de cada bloco
	Permutacao(mensagem,tamanho); //Funcao que permuta os blocos

}

int main(){
	char mensagem[PADRAO]; //String que vai ser armazenado o texto
	FILE *fp;
	char file[100];
	printf("Digite o nome do arquivo: ");
	scanf("%s",file);
	fp = fopen( file, "r"); // ABRE ARQUIVO
	if(!fp){
		printf("Erro na abertura do arquivo.\n");
		return 0;
	}
	int contador=0;
	char c;
	int tamanho; // Numero de caracteres do texto
	while(!feof(fp)){
		c = fgetc(fp);
		mensagem[contador] = c; //LE O ARQUIVO E SALVA NA STRING
		contador++;
	}
	tamanho = contador-1;
	mensagem[tamanho] = '\0'; //Adiciona o \0 no final da string
	tamanho = tamanho -1;
	printf("\n");
	printf("--------------------\n");
	printf("Mensagem codificada:\n");
	printf("--------------------\n");
	for(int i=0;mensagem[i]!='\0';i++){
		printf("%c",mensagem[i]); //Printa a mensagem codificada
	}
	printf("\n");
	printf("----------------------\n");
	printf("Mensagem decodificada:\n");
	printf("----------------------\n");
	Criptografia(mensagem,tamanho); //Funcao de decodificacao
	for(int i=0;mensagem[i]!='\0';i++){
		printf("%c",mensagem[i]); //Printa a mensagem decodificada
	}
	printf("\n");
}
