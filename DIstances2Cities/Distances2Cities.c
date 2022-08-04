//FRANCISCO ABREU GONCALVES AEDSI
/*REFERENCIAS : https://github.com/kelvins/Algoritmos-e-Estruturas-de-Dados/blob/master/C/AlgoritmoDijkstra.c#L44
		http://www2.dcc.ufmg.br/livros/algoritmos/cap7/codigo/c/7.22-dijkstramatriz.c 
*/


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1
#define INFINITO       INT_MAX
#define PADRAO         20


typedef int TipoValorVertice;
typedef int TipoPeso;
typedef char TipoVertice[20];

typedef struct TipoGrafo {
  TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
  int  NumVertices;
  int  NumArestas;
} TipoGrafo;

typedef TipoValorVertice TipoApontador;
typedef int TipoIndice;
typedef struct TipoItem {
  TipoPeso Chave;
} TipoItem;

typedef struct{
	char Cidade[PADRAO];
	int codigo; 
}Cidades;

typedef struct {
	Cidades A;
	Cidades B;
	int distancia;
}Estradas;

typedef TipoItem TipoVetor[MAXNUMVERTICES + 1];

TipoApontador Aux;
int  i, NArestas;
short FimListaAdj;
TipoValorVertice V1, V2, Adj, o, d; /*DECLARACAO DAS VARIAVEIS*/
TipoPeso Peso;
TipoGrafo Grafo;
TipoValorVertice NVertices;
TipoIndice n;   /*Tamanho do heap*/
TipoValorVertice Raiz;
TipoVertice v1, v2;

void FGVazio(TipoGrafo *Grafo)
{ int  i, j;
  for (i = 0; i <= Grafo->NumVertices; i++) /*PREENCHE GRAFO COM ZEROS*/
    for (j = 0; j <= Grafo->NumVertices; j++)
      Grafo->Mat[i][j] = 0;
}

int PesquisaCidade(Cidades *cities, char *V, int j){
  for(int i=0;i<j;i++){
	if(strcmp(cities[i].Cidade,V)==0){
		return 0;
  	}
  }
   return 1; 
}

void PesquisaOrDes(Cidades *cities, char *or, char *des, TipoValorVertice *o, TipoValorVertice *d,int j){
  for(int i=0;i<j;i++){
	if(strcmp(cities[i].Cidade,or)==0){
		*o = i;
  	}
	if(strcmp(cities[i].Cidade,des)==0){
		*d = i;
  	}
  } 
}
void PreencheCidadeVazio(Cidades *cities){
  char preenche[10] = "vazio";
  for(int i=0;i<PADRAO;i++){
	strcpy(cities[i].Cidade,preenche);
  }
}

void InsereAresta(TipoGrafo *Grafo, Estradas *arcos, int i){ 
  Grafo->Mat[arcos[i].A.codigo][arcos[i].B.codigo] = arcos[i].distancia;
  Grafo->Mat[arcos[i].B.codigo][arcos[i].A.codigo] = arcos[i].distancia;
}

short ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, 
            TipoGrafo *Grafo){ 
  return (Grafo->Mat[Vertice1][Vertice2] > 0);
}

/*-- Operadores para obter a lista de adjacentes --*/

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoApontador Aux = 0;
  short ListaVazia = TRUE;
  while (Aux < Grafo->NumVertices && ListaVazia) 
    { if (Grafo->Mat[*Vertice][Aux] > 0)
      ListaVazia = FALSE;
      else
      Aux++;
    }
  return (ListaVazia == TRUE);
} 

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoValorVertice Result;
  TipoApontador Aux = 0;
  short Listavazia = TRUE;
  while (Aux < Grafo->NumVertices && Listavazia) 
    { if (Grafo->Mat[*Vertice][Aux] > 0) 
      { Result = Aux; Listavazia = FALSE;
      } 
      else  Aux++;
    }
  if (Aux == Grafo->NumVertices)
  printf("Erro: Lista adjacencia vazia (PrimeiroListaAdj)\n");
  return Result;
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo, 
         TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox, 
         short *FimListaAdj)
{ /* --Retorna Adj apontado por Prox--*/
  *Adj = *Prox;
  *Peso = Grafo->Mat[*Vertice][*Prox];
  (*Prox)++;
  while (*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)
    (*Prox)++;
  if (*Prox == Grafo->NumVertices)  *FimListaAdj = TRUE;
} 

void ImprimeGrafo(TipoGrafo *Grafo)

{ int i, j;
  printf("   ");
  for (i = 0; i < Grafo->NumVertices; i++) printf("%4d", i); putchar('\n');
  for (i = 0; i < Grafo->NumVertices; i++) 
    { printf("%4d", i);
      for (j = 0; j < Grafo->NumVertices; j++)
        printf("%4d", Grafo->Mat[i][j]);
      putchar('\n');
    }
}  

void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P, 
            TipoValorVertice *Pos)

{ TipoIndice i = Esq;  int j;  TipoItem x;
  j = i * 2;  x = A[i];
  while (j <= Dir) 
    { if (j < Dir) 
      { if (P[A[j].Chave] > P[A[j+1].Chave]) j++; 
      }
      if (P[x.Chave] <= P[A[j].Chave])  goto L999;
      A[i] = A[j]; Pos[A[j].Chave] = i;
      i = j;   j = i * 2;
    }
  L999:  A[i] = x;  Pos[x.Chave] = i;
} 

void Constroi(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos){ 
  TipoIndice Esq;
  Esq = n / 2 + 1;
  while (Esq > 1) { 
  	Esq--;
        RefazInd(Esq, n, A, P, Pos);
        }
} 

TipoItem RetiraMinInd(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos)
{ TipoItem Result;
  if (n < 1) 
  { printf("Erro: heap vazio\n");
    return Result;
  }
  Result = A[1];
  A[1] = A[n]; Pos[A[n].Chave] = 1;
  n--;
  RefazInd(1, n, A, P, Pos);
  return Result;
}  

void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A, 
             TipoPeso *P,  TipoValorVertice *Pos)
{ TipoItem x;
  if (ChaveNova > P[A[i].Chave]) 
  { printf("Erro: ChaveNova maior que a chave atual\n");
    return;
  }
  P[A[i].Chave] = ChaveNova;
  while (i > 1 && P[A[i / 2].Chave] > P[A[i].Chave]) 
    { x = A[i / 2];
      A[i / 2] = A[i];
      Pos[A[i].Chave] = i / 2;
      A[i] = x;
      Pos[x.Chave] = i;
      i /= 2;
    }
} 

void Dijkstra(TipoGrafo *Grafo, TipoValorVertice *Raiz, TipoValorVertice *V2, Cidades *cities, int j){ 
  TipoPeso P[MAXNUMVERTICES + 1];
  TipoValorVertice Pos[MAXNUMVERTICES + 1];
  int Antecessor[MAXNUMVERTICES + 1];
  //short Itensheap[MAXNUMVERTICES + 1];
  TipoVetor A;
  TipoValorVertice u, v, destino;
  TipoItem temp;
  destino = *V2;
  char percurso[PADRAO];
  int contador=0;
  for (u = 0; u <= Grafo->NumVertices; u++){ /*Constroi o heap com todos os valores igual a INFINITO*/
  	Antecessor[u] = -1; 
  	P[u] = INFINITO;
  	A[u+1].Chave = u;   /*Heap a ser construido*/
  	//Itensheap[u] = TRUE;  
  	Pos[u] = u + 1;
  	}

  n = Grafo->NumVertices;
  P[*(Raiz)] = 0;
  Constroi(A, P, Pos);
  while (n >= 1) 
  { /*enquanto heap nao vazio*/
    temp = RetiraMinInd(A, P, Pos);
    u = temp.Chave; 
    //Itensheap[u] = FALSE;
    if (!ListaAdjVazia(&u, Grafo))
    { Aux = PrimeiroListaAdj(&u, Grafo); FimListaAdj = FALSE;
      while (!FimListaAdj) 
      { ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
        if (P[v] > (P[u] + Peso))
        { P[v] = P[u] + Peso; Antecessor[v] = u;
          DiminuiChaveInd(Pos[v], P[v], A, P, Pos);
         // printf("Caminho: v[%d] v[%ld] d[%d]", 
	        // v, Antecessor[v], P[v]);
          //scanf("%*[^\n]");
          //getchar();
        }
      }
    } 
  }
  percurso[contador] = destino;
  contador++;
  while(Antecessor[destino]!=-1){
	for(int i=0;i<j;i++){
		if(cities[i].codigo == Antecessor[destino]){
			percurso[contador]=cities[i].codigo;
			contador++;
		}
	}
	destino = Antecessor[destino];
  }
  printf("Menor percurso:");
  for(int i=1;i<=contador;i++){
	for(int k=0;k<j;k++){
		if(percurso[contador-i]==cities[k].codigo)
		printf(" %s",cities[k].Cidade);
	}
  }
  printf("\n");
  printf("Distancia total: %d Km",P[*V2]);
  
}

/* ============================================================= */
int main(int argc, char *argv[])
{  /*-- Programa principal --*/
  //int TEMP; 
  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/
  //printf("No. vertices:\n");   /*readln(NVertices);*/
  //NVertices = 5;
  //printf("No. arestas:\n");   /*eadln(NArestas);*/
  //NArestas = 7;
  Cidades cities[PADRAO];
  Grafo.NumArestas = 0;
  FGVazio(&Grafo); 
  FILE *fp;
  char file[100];
  printf("Digite o nome do arquivo de entrada: ");
  scanf("%s",file);
  getchar();
  fp = fopen( file, "r");
  if(!fp){
	printf("Erro na abertura do arquivo.\n");
	return 0;
	} 
  fscanf(fp,"%d\n",&Grafo.NumArestas);
  Estradas arcos[Grafo.NumArestas];
  PreencheCidadeVazio(cities);
  int j=0;
  for(int i=0;i < Grafo.NumArestas; i++){
	fscanf(fp,"%s %s %d\n",v1,v2,&Peso);
	strcpy(arcos[i].A.Cidade,v1);
	strcpy(arcos[i].B.Cidade,v2);
	arcos[i].distancia = Peso;
	if(PesquisaCidade(cities,v1,j)){
		strcpy(cities[j].Cidade,v1);
		cities[j].codigo = j;
		j++;
	}
	if(PesquisaCidade(cities,v2,j)){
		strcpy(cities[j].Cidade,v2);
		cities[j].codigo = j;
		j++;
	}
  }
  fscanf(fp,"%s %s",v1,v2);
  PesquisaOrDes(cities,v1,v2,&o,&d,j);

  for(int i=0;i<Grafo.NumArestas;i++){
  	for(int k=0;k<j;k++){
		if(strcmp(arcos[i].A.Cidade,cities[k].Cidade)==0){
			arcos[i].A.codigo = cities[k].codigo;
		}
		if(strcmp(arcos[i].B.Cidade,cities[k].Cidade)==0){
			arcos[i].B.codigo = cities[k].codigo;
		}
	}
  }
  for(int i=0;i<Grafo.NumArestas;i++){
	InsereAresta(&Grafo,arcos,i);
  }
  Grafo.NumVertices = j;
  Dijkstra(&Grafo,&o,&d,cities,j);
  return 0;
}
