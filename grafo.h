#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
  Lista de inteiros para fins genéricos
*/
typedef struct TipoLista {
  int valor;
  struct TipoLista* proximo;
} Lista;

/*
  Lista de adjacencias para vértices
*/
typedef struct TipoListaAdj {
  int verticeFinal;
  int peso;
  struct TipoListaAdj* proximo;
} ListaAdj;

/*
  Estrutura de um Grafo
*/
typedef struct TipoGrafo {
  int numVertices;
  int numArestas;
  ListaAdj** listaAdj;
} Grafo;



/*
  Variáveis Úteis
*/
Lista* pilhaAuxiliar;
char readLines[1000][20];
char *pch;


// Funções de Lista

/*
  Verifica se a lista esta vazia, retornando true se estiver vazia
*/
bool listaEstaVazia(Lista* listaAtual);

/*
  Verifica se a lista esta vazia, retornando false se estiver vazia
*/
bool listaNaoEstaVazia(Lista* listaAtual);

/*
  Verifica se a lista contem um único elemento, útil para saber como proceder na remoção
*/
bool listaEhUnitaria(Lista* listaAtual);

/*
  Verifica se um dado elemento esta na lista
*/
bool valorEstaNaLista(int valorProcurado, Lista* listaAtual);

/*
  Instancia e popula uma nova lista com um dado elemento inicial
*/
Lista* criaLista(int valor);

/*
  Insere um elemento no fim da lista
*/
Lista* insereNoFimDaLista(int valor, Lista* listaAtual);

/*
  Insere um elemento na posição padrão (fim da lista)
*/
Lista* insereNaLista(int valor, Lista* listaAtual) ;

/*
  Remove o último elemento da lista
*/
void removeDePilha(Lista* listaAtual);

/*
  Remove o primeiro elemento da lista
*/
void removeDeFila(Lista* listaAtual);

/*
  Remove um certo elemento da lista, dependendo do tipo dela invoca removeDeFila ou removeDePilha
*/
void removeDaLista(Lista* listaAtual);

/*
  Imprime todos os elementos da lista
*/
void printLista(Lista* lista);



// Funções de Lista de Adjacencia

/*
  Verifica se uma dada aresta já se encontra na lista de adjacencia, retornando true caso se encontre
*/
bool arestaJaExisteNaListaAdj(int verticeProcurado, ListaAdj* listaAtual);

/*
  Verifica se uma dada aresta já se encontra na lista de adjacencia, retornando false caso se encontre
*/
bool arestaNaoExisteNaListaAdj(int verticeProcurado, ListaAdj* listaAtual);


/*
  Instancia e popula uma nova lista de adjacencia com uma aresta inicial
*/
ListaAdj* criaListaAdj(int verticeFinal, int peso)

/*
  Insere uma aresta na posição padrão (fim da lista)
*/
ListaAdj* insereNaListaAdj(int verticeFinal, int peso, ListaAdj* listaAtual);

/*
  Insere uma nova aresta direcionada no grafo
*/
void insereArestaDirecionada(int verticeInicial, int verticeFinal, int peso, Grafo* grafo);

/*
  Insere uma nova aresta não direcionada no grafo
*/
void insereArestaNaoDirecionada(int verticeInicial, int verticeFinal, int peso, Grafo* grafo);



/*
  Imprime todas as arestas saindo de um dado vértice
*/
void printListaAdj(int verticeInicial, ListaAdj* listaAtual);

/*
  Imprime todas as arestas do grafo
*/
void printGrafo(Grafo* grafo);


// Busca em Profundidade - DFS

/*
  Realiza uma busca em profundidade utilizando algoritmo recursivo
*/
Lista* buscaEmProfundidadeRecursiva(int verticeInicial, Grafo* grafo, Lista* marcados);

/*
  Realiza uma busca em profundidade no grafo
*/
void buscaEmProfundidade(Grafo* grafo);

// Busca em Largura - BFS

/*
  Realiza uma busca em largura no grafo
*/
void buscaEmLargura(Grafo* grafo);


// Calcula Componentes Conexos

/*
  Realiza o cálculo por componentes conexos no grafo
*/
void calculaComponentesConexos(Grafo* grafo);


// Inicializa e popula o Grafo

/*
  Instancia e popula um novo grafo, já prealocando listas de adjacencia saindo de cada vértice
*/
Grafo* inicializaGrafo(int numVertices, int numArestas);


/*
  Função que bufferiza as linhas da entrada do arquivo para linhas de buffer que possam ser carregadas eficientemente
*/
bool bufferizeNextLine (FILE *fr, int currentLine);


/*
  Função que quebra o dado bufferizado em dados no padrão das linhas de adjacencia
*/
int* getIntegersFromSpaceSeparatedString(char *line, int numbersToRead);

/*
  Função que carrega o grafo a partir do arquivo de entrada
*/
Grafo* carregaGrafo(char* arquivoEntrada);
