#include <stdio.h>
#include <stdlib.h>

// Problema da Mochila - 24/9/2020 - LAEDS 1 - Francisco Abreu e Caio Lott

int verifica(int Peso[],int Valor[],int Vatual, int pesoTotal, int tam, int i, int Balanca, int Vanterior){

	int ValorAtual = Vatual; // O valor desse nodulo começa com o valor de procura feito ate o nodulo anterior
	int PesoAtual = Balanca + Peso[i]; // Acrecenta-se o peso desse nodulo
	int j = i; // Marca a posicao desse nodulo
  	int ValorAnterior = 0;  // O valor desse nodulo n pode ser computado ainda, caso seu peso exceda
  	if(PesoAtual < pesoTotal){ // Se o peso ate esse nodulo e menor q a capacidade da mochila
		ValorAtual = ValorAtual + Valor[i]; // Computa o valor desse nodulo
		ValorAnterior = ValorAtual;
  		for(;j<tam;j++){
        	ValorAtual = verifica(Peso, Valor, ValorAtual, pesoTotal, tam, j+1, PesoAtual, Vanterior); // Chama a funcao novamente para fazer uma busca exaustiva a partir desse nodulo
        	if(ValorAtual > ValorAnterior) // Se o resultado da busca foi maior que o valor ate agora computado
            	ValorAnterior = ValorAtual; // Computa o maior valor
		}
  	}else if(j+1 < tam){ // Caso o peso desse nodulo ultrapasse a capacidade da mochila
	  	ValorAtual = verifica(Peso, Valor, ValorAtual, pesoTotal, tam, j+1, PesoAtual, Vanterior); // Faz uma busca exaustica em outro nodulo, caso exista
		if(ValorAtual > ValorAnterior) // Se o resultado da busca foi maior que o valor ate agora computado
            	ValorAnterior = ValorAtual;// Computa o maior valor
	}else // Caso n tenha mais nodulo para explorar
	{
		return ValorAtual; //retorna o valor achado ate esse ponto
	}
      
   	return ValorAnterior; // retorna o maior valor encontrado nessa busca

}

int melhorCaso(int Valor[], int Peso[], int pesoTotal, int tam){
    
    int Vmelhor =0 , Vatual= 0, Vanterior=0 , Balanca = 0; //Variaveis que armazenarao os valores das combinacoes e o peso

    for(int i=0; i<tam; i++){ //Cada Loop e referente a um nodulo da arvore de busca
        if(Peso[i]<=pesoTotal){ // Caso o primeiro nodulo ja n ultrapasse o peso
            Balanca = Peso[i]; // Armazena o peso inicial do nodulo
            Vatual = Valor[i]; // Armazena o valor inicial do nodulo
			if(i+1<tam) 
            Vatual = verifica(Peso,Valor,Vatual,pesoTotal, tam, i+1, Balanca, Vanterior); // chama a funcao que fara a busca exaustiva a partir do nodulo 

        }else
            Vatual = 0; // O primeiro nodulo ja excede a capacidade da mochila, logo, nao se pode computar o seu valor
        
        if(Vatual>Vmelhor){ // Se o maior valor da busca for o maior valor geral
            Vmelhor = Vatual; // Substitui o valor
			}
		Vanterior = 0; // Reseta o valor anterior
    }
        
    return Vmelhor; // Retorna o maior valor

}

void seleciona(int Valor[], int Peso[], int Itens[], int PesoTotal, int melhor, int tam){

	int SomaPesos=0, SomaValor=0; // Variaveis que armazenaram os valores de peso e valor

	for(int i = 0; i<tam; i++){ // Pecorre o vetor de itens selecionado
		if(Itens[i]){ // Se o item foi selecionado
			SomaPesos = SomaPesos + Peso[i]; // Computa seu Peso
			SomaValor = SomaValor + Valor[i]; // Computa seu valor
		}
			
	}
	
	if(SomaPesos>PesoTotal) // Caso ultrapasse a capacidade da mochila
		printf("Solucao inviavel. ");
	else if(SomaValor == melhor) // Caso seja a melhor combinacao
		printf("Solucao otima. ");
	else if(SomaValor < melhor) // Caso seja uma combinacao pior
		printf("Solucao viavel mas nao otima. ");
}

int main(){


	char nome[1000];
	FILE *arquivo;

	printf("Digite o nome do arquivo: ");
	scanf("%s", nome);
	getchar();

	arquivo = fopen(nome, "r");

	if(!arquivo){
		printf("Erro na abertura do arquivo!");
	}

	//le o numero de itens e o peso total da mochila (segunda linha do arquivo)

	int pesoTotal, QtdItens, melhorValor;

	fscanf(arquivo, "%d", &pesoTotal);
	fscanf(arquivo, "%d", &QtdItens);

	int Peso[QtdItens], Valor[QtdItens], ItensSelecionados[QtdItens];
	
	//preenche os vetores com os pesos e os valores de cada item associados a cada posição do array

	for(int i = 0; i<QtdItens; i++)
		fscanf(arquivo, "%d %d", &Peso[i], &Valor[i]);


	//preenche o vetor dos itens escolhidos associados com cada posição do array de pesos e valores

	for(int i = 0; i<QtdItens; i++)
		fscanf(arquivo,"%d", &ItensSelecionados[i]);


	melhorValor = melhorCaso(Valor, Peso, pesoTotal, QtdItens); //Ao achar o melhor valor dentre todas as combinaçoes, salva em uma variavel
	seleciona(Valor, Peso, ItensSelecionados, pesoTotal, melhorValor, QtdItens); // avalia se a solucao do arquivo e boa
	

	

}