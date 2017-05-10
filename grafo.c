#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct TipoLista {
	int valor;
	struct TipoLista* proximo;
} Lista;

typedef struct TipoListaAdj {
	int verticeFinal;
	int peso;
	struct TipoListaAdj* proximo;
} ListaAdj;

typedef struct TipoGrafo {
	int numVertices;
	int numArestas;
	ListaAdj** listaAdj;
} Grafo;


int tipoDeListaUtilizada;
int pilha = 1;
int fila = 2;

bool saidaSimples = true;
Lista* pilhaAuxiliar;

// working with maximum 1000 edges of 20 words
char readLines[1000][20];
char *pch;


// Funções de Lista
bool listaEstaVazia(Lista* listaAtual) {
	return listaAtual == NULL || listaAtual->valor == -1;
}

bool listaNaoEstaVazia(Lista* listaAtual) {
	return !listaEstaVazia(listaAtual);
}

bool listaEhUnitaria(Lista* listaAtual) {
	return listaAtual->proximo == NULL;
}

bool valorEstaNaLista(int valorProcurado, Lista* listaAtual) {
	bool existe = false;

	Lista* proximo = listaAtual;
	while (proximo != NULL) {
		if (proximo->valor == valorProcurado) {
			existe = true;
			break;
		}
		proximo = proximo->proximo;
	}


	return existe;
}

Lista* criaLista(int valor) {
	Lista* novaLista = (Lista *) malloc (sizeof(Lista *));
	novaLista->valor = valor;
	novaLista->proximo = NULL;

	return novaLista;
}

Lista* insereNoFimDaLista(int valor, Lista* listaAtual) {
	Lista* proximo = listaAtual;
	while (proximo->proximo != NULL) {
		proximo = proximo->proximo;
	}

	proximo->proximo = criaLista(valor);

	return listaAtual;
}

Lista* insereNaLista(int valor, Lista* listaAtual) {
	Lista* listaResultante;
	if (listaEstaVazia(listaAtual)) {
		listaResultante = criaLista(valor);
	} else {
		listaResultante = insereNoFimDaLista(valor, listaAtual);
	}

	return listaResultante;
}

void removeDePilha(Lista* listaAtual) {
	Lista* anterior = listaAtual;
	Lista* proximo = listaAtual;

	while (proximo->proximo != NULL) {
		anterior = proximo;
		proximo = proximo->proximo;
	}

	free(anterior->proximo);
	anterior->proximo = NULL;
}

void removeDeFila(Lista* listaAtual) {
	Lista* proximo = listaAtual->proximo;

	listaAtual->valor = proximo->valor;
	listaAtual->proximo = proximo->proximo;

	free(proximo);
}

void removeDaLista(Lista* listaAtual) {
	if (!listaEstaVazia(listaAtual)) {
		if (listaEhUnitaria(listaAtual)) {
			listaAtual->valor = -1;

		} else {
			if (tipoDeListaUtilizada == pilha) {
				removeDePilha(listaAtual);
			} else if (tipoDeListaUtilizada == fila){
				removeDeFila(listaAtual);
			}
		}
	}
}

void printLista(Lista* lista) {
	if (listaEstaVazia(lista)) {
		printf("Lista Vazia\n");

	} else {
		Lista* proximo = lista;
		while (proximo != NULL) {
			printf("%d ", proximo->valor + 1);
			proximo = proximo->proximo;
		}
		printf("\n");
	}
}




// Funções de Conferencia em Lista
bool arestaJaExisteNaListaAdj(int verticeProcurado, ListaAdj* listaAtual) {
	bool existe = false;

	ListaAdj* proximo = listaAtual;
	while (proximo != NULL) {
		if (proximo->verticeFinal == verticeProcurado) {
			existe = true;
			break;
		}
		proximo = proximo->proximo;
	}

	return existe;
}

bool arestaNaoExisteNaListaAdj(int verticeProcurado, ListaAdj* listaAtual) {
	return !arestaJaExisteNaListaAdj(verticeProcurado, listaAtual);
}

// Funções de Inserção em Lista
ListaAdj* criaListaAdj(int verticeFinal, int peso) {
	ListaAdj* novaLista = (ListaAdj *) malloc (sizeof(ListaAdj *));
	novaLista->verticeFinal = verticeFinal;
	novaLista->peso = peso;
	novaLista->proximo = NULL;

	return novaLista;
}

ListaAdj* insereNaListaAdj(int verticeFinal, int peso, ListaAdj* listaAtual) {
	ListaAdj* proximo = listaAtual;
	while (proximo->proximo != NULL) {
		proximo = proximo->proximo;
	}

	proximo->proximo = criaListaAdj(verticeFinal, peso);

	return listaAtual;
}

void insereArestaDirecionada(int verticeInicial, int verticeFinal, int peso, Grafo* grafo) {
	ListaAdj* listaAtual = grafo->listaAdj[verticeInicial];

	if (arestaNaoExisteNaListaAdj(verticeFinal, listaAtual)) {
		if (listaAtual == NULL) {
			grafo->listaAdj[verticeInicial] = criaListaAdj(verticeFinal, peso);
		} else {
			grafo->listaAdj[verticeInicial] = insereNaListaAdj(verticeFinal, peso, listaAtual);
		}
	} else {
		printf("Aresta já existe\n");
	}
}

void insereArestaNaoDirecionada(int verticeInicial, int verticeFinal, int peso, Grafo* grafo) {
	insereArestaDirecionada(verticeInicial, verticeFinal, peso, grafo);
	insereArestaDirecionada(verticeFinal, verticeInicial, peso, grafo);
}


// Funções de Visualização em Lista
void printListaAdj(int verticeInicial, ListaAdj* listaAtual) {
	ListaAdj* proximo = listaAtual;
	while (proximo != NULL) {
		printf("%d-%d = %d \n", verticeInicial, proximo->verticeFinal, proximo->peso);
		proximo = proximo->proximo;
	}
}

void printGrafo(Grafo* grafo) {
	int counter = 0;
	printf("%d %d\n", grafo->numVertices, grafo->numArestas);

	while (counter < grafo->numVertices) {
		printListaAdj(counter, grafo->listaAdj[counter]);
		printf("---\n");
		counter++;
	}
}

// Busca em Profundidade - DFS

Lista* buscaEmProfundidadeRecursiva(int verticeInicial, Grafo* grafo, Lista* marcados) {
	marcados = insereNaLista(verticeInicial, marcados);
	if (!saidaSimples) {
		pilhaAuxiliar = insereNaLista(verticeInicial, pilhaAuxiliar);
		printLista(pilhaAuxiliar);
	}

	ListaAdj* linkVerticeFinal = grafo->listaAdj[verticeInicial];
	while (linkVerticeFinal != NULL) {
		int verticeFinal = linkVerticeFinal->verticeFinal;
		if (!valorEstaNaLista(verticeFinal, marcados)) {
			marcados = buscaEmProfundidadeRecursiva(verticeFinal, grafo, marcados);
		}

		linkVerticeFinal = linkVerticeFinal->proximo;
	}

	if (!saidaSimples) {
		removeDaLista(pilhaAuxiliar);
	}

	return marcados;
}

void buscaEmProfundidade(Grafo* grafo) {
	if (saidaSimples) {
		printf("DFS:\n");
	} else {
		printf("DFS Paths:\n");
	}
	tipoDeListaUtilizada = pilha;

	int verticeInicial = 0;
	Lista* marcados = NULL;

	marcados = buscaEmProfundidadeRecursiva(verticeInicial, grafo, marcados);

	if (saidaSimples) {
		printLista(marcados);
	}
	printf("\n");
}


// Busca em Largura - BFS
void buscaEmLargura(Grafo* grafo) {
	if (saidaSimples) {
		printf("BFS:\n");
	} else {
		printf("BFS Paths:\n");
	}
	tipoDeListaUtilizada = fila;

	int valorInicial = 0;

	Lista* marcados = criaLista(valorInicial);
	Lista* aVisitar = criaLista(valorInicial);

	if (!saidaSimples) {
		pilhaAuxiliar = insereNaLista(valorInicial, pilhaAuxiliar);
		printLista(pilhaAuxiliar);
	}

	while (listaNaoEstaVazia(aVisitar)) {
		int verticeInicial = aVisitar->valor;

		ListaAdj* linkVerticeFinal = grafo->listaAdj[verticeInicial];
		while (linkVerticeFinal != NULL) {
			int verticeFinal = linkVerticeFinal->verticeFinal;

			if (!saidaSimples) {
				pilhaAuxiliar = insereNaLista(verticeFinal, pilhaAuxiliar);
				printLista(pilhaAuxiliar);
			}

			if (!valorEstaNaLista(verticeFinal, marcados)) {
				marcados = insereNaLista(verticeFinal, marcados);
				aVisitar = insereNaLista(verticeFinal, aVisitar);
				// visite aresta i-f
			} else {
				// visite aresta i-f
			}
			linkVerticeFinal = linkVerticeFinal->proximo;

			if (!saidaSimples) {
				removeDaLista(pilhaAuxiliar);
			}
		}

		
		removeDaLista(aVisitar);
	}

	if (saidaSimples) {
		printLista(marcados);
	}
	printf("\n");
}

void calculaComponentesConexos(Grafo* grafo) {
	printf("Connected Components:\n");
	printf("C1:");
}

// Inicializa e popula o Grafo
Grafo* inicializaGrafo(int numVertices, int numArestas) {
	Grafo* grafo = (Grafo *) malloc (sizeof(Grafo *) * numVertices);
	grafo->numVertices = numVertices;
	grafo->numArestas = numArestas;
	grafo->listaAdj = (ListaAdj **) malloc (numVertices * sizeof(ListaAdj *));

	return grafo;
}


// Gets the next line from a file or system input and save it to the current line
// It stop when found a null line
bool bufferizeNextLine (FILE *fr, int currentLine) {
	char readLine[80];
	fgets(readLine, 80, fr);

	strcpy(readLines[currentLine], readLine);

	return readLine != NULL;
}

// From a string input like 4 5 or 3 6 7 gets the first N integers
int* getIntegersFromSpaceSeparatedString(char *line, int numbersToRead) {
	static int values[3] = {0};
	int counter = 0;

	pch = strtok (line," ,-");
	while (pch != NULL && counter < numbersToRead) {
		values[counter] = atoi(pch);

		counter++;
		if (counter < numbersToRead) {
			pch = strtok (NULL, " ,-");
		}
	}
	return values;
}

Grafo* carregaGrafo(char* arquivoEntrada) {
	char* line;
	FILE* fr = fopen(arquivoEntrada, "r");

	Grafo* grafo;

	int numLines = 0;

	if (bufferizeNextLine(fr, numLines) || numLines > 1000){
		numLines++;
	}

	line = readLines[0];
	int* graphSizes = getIntegersFromSpaceSeparatedString(line, 2);

	int numVertex = graphSizes[0];
	int numEdges = graphSizes[1];


	if (numLines > 0) {
		line = readLines[0];
		int* graphSizes = getIntegersFromSpaceSeparatedString(line, 2);

		int numVertex = graphSizes[0];
		int numEdges = graphSizes[1];

		printf("%d %d\n", numVertex, numEdges);

		grafo = inicializaGrafo(numVertex, numEdges);

		int i;
		for(i = 1; i<=numEdges; i++) {
			bufferizeNextLine(fr, numLines);
			numLines++;

			line = readLines[i];
			graphSizes = getIntegersFromSpaceSeparatedString(line, 3);

			int edgeFrom = graphSizes[0] - 1;
			int edgeTo = graphSizes[1] - 1;
			int edgeWeight = graphSizes[2];

			printf("%d %d %d\n", graphSizes[0], graphSizes[1], graphSizes[2]);

			insereArestaNaoDirecionada(edgeFrom, edgeTo, edgeWeight, grafo);
		}
	}

	fclose(fr);
	printf("\n");

	return grafo;
}


// Mainly the main
int main(int numParams, char *params[]){
	char* arquivoEntrada = params[1];

	Grafo* grafoPrincipal = carregaGrafo(arquivoEntrada);


	saidaSimples = true;
	buscaEmLargura(grafoPrincipal);

	saidaSimples = false;
	buscaEmLargura(grafoPrincipal);
	// esvazia pilha auxiliar
	while (listaNaoEstaVazia(pilhaAuxiliar)) {
		removeDaLista(pilhaAuxiliar);
	}


	saidaSimples = true;
	buscaEmProfundidade(grafoPrincipal);

	saidaSimples = false;
	buscaEmProfundidade(grafoPrincipal);


	// Limpa a memória
	free(pilhaAuxiliar);
	free(grafoPrincipal);

	return 0;
}
