
// ANALISE DE SEGMENTOS COM NUMEROS IGUAIS - AEDS1 - FRANCISCO ABREU GONCALVES

#include <stdio.h>
#include <stdlib.h>

void preencheMatriz(int *sequencia, int *sequenciaOrdenada, int tamanho){

   int aux1=0,aux2=0, contador = 0, tamMatriz=0; // Variaveis auxiliares e Variavel do tamanho da matriz
   int j = 0, k=0;

   int **Matriz; // Declara a matriz

   Matriz = (int**)malloc(2*sizeof(int*)); // Inicializa o Tamanho da Matriz 
   Matriz[0] = (int*)malloc(sizeof(int));
   Matriz[1] = (int*)malloc(sizeof(int));

    for(int i =0; i<tamanho; i=j){ // Loop que percorre a sequencia 
        aux1 = sequencia[i];// Armazena o valor atual em aux1
        while(aux1 == sequencia[j] && j < tamanho){ // Compara quantas vezes o valor atual se repete na posicao atual da sequencia
            contador++; // Enquanto e igual, conta mais 1
            j++; // Avanca na sequencia
        }
        while(aux1 != sequenciaOrdenada[k]){ // Acha o valor atual na sequencia ordenada
            k++;
        }
        aux2 = k+1; // Armazena o valor da posicao do numero atual  na sequencia ordenada em aux2

        tamMatriz++; // Aumenta o tamanho da matriz
        Matriz[0] = (int*)realloc(Matriz[0], tamMatriz*sizeof(int));
        Matriz[1] = (int*)realloc(Matriz[1], tamMatriz*sizeof(int));

        Matriz[0][tamMatriz-1] = aux2; // Armazena a posicao do numero atual na sequencia ordenada 
        Matriz[1][tamMatriz-1] = contador; // Armazena o valor de quantas vezes o numero atual se repete na posicao atual da sequencia

        contador =0; //  Reseta valores
        k = 0;

    }
    printf("Matriz:\n"); // Imprime a matriz
    for(int i =0; i<2; i++){
        for(int j=0; j< tamMatriz; j++){
        printf("%d ",Matriz[i][j]);
        }
        printf("\n");
    }

}




int *ordenaVetor(int *sequencia, int *sequenciaOrdenada, int tamanho){

    int contador = 0; // Variavel de tamnho do vetor da sequencia ordenada
    int aux1 =0, aux2=0, aux3 = 1; // Variaveis auxiliares

    contador++;
    sequenciaOrdenada = (int*)realloc(sequenciaOrdenada,contador*sizeof(int)); // Inicializa o tamanho do vetor
    sequenciaOrdenada[0] = sequencia[0]; // Armazena o primeiro valor da sequencia no vetor

    for(int i=1; i<tamanho; i++){ // Loop que percorrera a sequencia desordenada
        aux1 = sequencia[i]; // Armazena o valor atual da sequencia disordenada no auxiliar
        for(int j = 0; j<contador; j++){ // Loop que pecorrera a sequencia ordenada
            if(aux1 < sequenciaOrdenada[j] && aux3 == 1){ // Se o numero atual for menor q
                aux2 = j; // Armazena a posicao da variavel maior em aux2
                contador++; // Aumenta o tamanho do Vetor ordenado
                sequenciaOrdenada = (int*)realloc(sequenciaOrdenada,contador*sizeof(int)); // Aloca mais memoria no vetor
                for(int k = 1; contador - k > aux2; k++){ // Loop que percorre o Vetor ordenado ate a posicao de aux2 e
                // "arrasta" todos os valores maiores que ele para a direita do Vetor
                    sequenciaOrdenada[contador-k] = sequenciaOrdenada[contador-1-k];
                }
                sequenciaOrdenada[aux2] = aux1; // Substitui o valor na posicao aux2 no Vetor ordenado pelo valor atual achado
                aux3 = 0; // Variavel que pula as outras condicoes 
            }
            else if(aux1 == sequenciaOrdenada[j]) // Se o valor ja estiver contido no Vetor ordenado
            aux3 = 0; // Pula e vai para o proximo valor da sequencia
        }
        if(aux3){ // Se em nenhum momento o valor atual for menor ou igual aos Valores do Vetor ordenado, entao ele e o maior de todos
            contador++; // Aumenta o tamanho do vetor
            sequenciaOrdenada = (int*)realloc(sequenciaOrdenada,contador*sizeof(int)); // Aloca mais memoria
            sequenciaOrdenada[contador-1] = aux1; // Coloca o valor atual na ultima posicao do Vetor ordenado
        }
        aux3 = 1; // Reseta o aux3
    }
    return sequenciaOrdenada; // Retorna a referencia do Vetor ordenado
}
   


int main(){

    char nome[1000];
    FILE *arquivo;

    // Faz a abertura do arquivo

    printf("Digite o nome do arquivo: ");
	scanf("%s", nome);
	getchar();

	arquivo = fopen(nome, "r");

	if(!arquivo){
		printf("Erro na abertura do arquivo!");
	}

    int *sequencia; // Ponteiro que apontara para a sequencia contida no arquivo
    int tamanho ; // Variavel que armazenara a quantidade de numeros na sequencia
    int contador = 0;// Variavel auxiliar para preencher o vetor de ponteiro

    sequencia = (int*)malloc(1*sizeof(int));

    fscanf(arquivo,"%d", &tamanho);    

    while(!feof(arquivo)){ // Loop que le os valores no arquivo e armazena no vetor
        fscanf(arquivo,"%d", &sequencia[contador]);
        contador++;
        sequencia = (int*)realloc(sequencia,(contador+1)*sizeof(int));

    }

    fclose(arquivo); // Fecha o arquivo

    int *SequenciaOrdenada; // Ponteiro que apontara para os valores do arquivo em ordem crescente e sem repeticao
    
    SequenciaOrdenada = (int*)malloc(sizeof(int)); // Inicializa o tamanho do vetor 

    SequenciaOrdenada =  ordenaVetor(sequencia, SequenciaOrdenada, tamanho); // Funcao que retornara o sequencia em ordem e sem repeticao

    
    preencheMatriz(sequencia, SequenciaOrdenada, tamanho); // Funcao que construira a matriz
}