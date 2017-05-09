#include <stdio.h>
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



// Funções de Lista

/*
  confere se a listaAtual esta vazia
*/ 
bool listaEstaVazia(Lista* listaAtual);

bool listaNaoEstaVazia(Lista* listaAtual);

bool listaEhUnitaria(Lista* listaAtual;

bool valorEstaNaLista(int valorProcurado, Lista* listaAtual);

Lista* criaLista(int valor);

Lista* insereNoFimDaLista(int valor, Lista* listaAtual);

Lista* insereNaLista(int valor, Lista* listaAtual);

void removeDePilha(Lista* listaAtual);

void removeDeFila(Lista* listaAtual);

void removeDaLista(Lista* listaAtual);

void printLista(Lista* lista);



// Funções de Conferencia em Lista
bool arestaJaExisteNaListaAdj(int verticeProcurado, ListaAdj* listaAtual);

bool arestaNaoExisteNaListaAdj(int verticeProcurado, ListaAdj* listaAtual);

ListaAdj* insereNaListaAdj(int verticeFinal, int peso, ListaAdj* listaAtual);

void insereArestaDirecionada(int verticeInicial, int verticeFinal, int peso, Grafo* grafo);

void insereArestaNaoDirecionada(int verticeInicial, int verticeFinal, int peso, Grafo* grafo);



// Funções de Visualização em Lista
void printListaAdj(int verticeInicial, ListaAdj* listaAtual);

void printGrafo(Grafo* grafo);


// Busca em Profundidade - DFS
Lista* buscaEmProfundidadeRecursiva(int verticeInicial, Grafo* grafo, Lista* marcados);

void buscaEmProfundidade(Grafo* grafo, bool saidaSimples);


// Busca em Largura - BFS
void buscaEmLargura(Grafo* grafo, bool saidaSimples);

// Inicializa e popula o Grafo
Grafo* inicializaGrafo(int numVertices, int numArestas);


// Gets the next line from a file or system input and save it to the current line
// It stop when found a null line
bool bufferizeNextLine (FILE *fr, int currentLine);


// From a string input like 4 5 or 3 6 7 gets the first N integers
int* getIntegersFromSpaceSeparatedString(char *line, int numbersToRead);


Grafo* carregaGrafo(char* arquivoEntrada);
