#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nodolista{
    // lista duplamente encadeada
    char word[30];
    int freq;
    struct nodolista* ant;
    struct nodolista* prox;
};

struct nodoarv{
    // árvore binária de pesquisa
    char word[30];
    int freq;
    struct nodoarv* esq;
    struct nodoarv* dir;
};

typedef struct nodolista NOlista;
typedef struct nodoarv NOarv;

//FUNÇÕES DE LISTA
NOlista* iniLista();
//inicializa uma estrutra de dados do tipo lista

void imprimeLista(NOlista* lista, int freqmin, int freqmax);
//imprime os elementos (de lista) que respeitam os limites freqmin e freqmax

NOlista* listInsertWord(NOlista* lista, char palavra[30]);
//insere uma palavra numa lista ordenada pelo campo frequência (em empate, ordenada lexicograficamente)

NOlista* listInsertProcWord(NOlista* lista, char palavra[30], int frequencia);
//insere (em lista) uma palavra cuja frequência já foi processada

NOlista* listInsertSentence(NOlista* lista, char *str);
//quebra uma frase em várias palavras e as insere em lista

//FUNÇÕES DE ÁRVORE
NOarv* iniArvore();
//inicializa uma estrutra de dados do tipo árvore

void imprimeArv(NOarv* arvore);
//imprime uma arvore usando o caminhamento central esquerda

NOarv* arvInsertWord(NOarv* arvore, char palavra[30]);
//insere uma palavra numa árvore, ordenada lexicograficamente

NOarv* arvInsertSentence(NOarv* arvore, char *str);
//quebra uma frase em várias palavras e as insere em arvore

//FUNÇÕES DE ARQUIVO
NOlista* listLeArquivo(NOlista* lista, char nomearquivo[30]);
//lê todas as linhas de um texto (cujo nome do arquivo é apontado por nomearquivo), as inserindo em lista

NOarv* arvLeArquivo(NOarv* arvore, char nomearquivo[30]);
//lê todas as linhas de um texto (cujo nome do arquivo é apontado por nomearquivo), as inserindo em arvore

void escreveSaida(NOlista* lista, int freqmin, int freqmax, char nomearq[30]);
//escreve (em um arquivo de texto nomeado por nomearq) cada palavra (e sua frequencia) contida em lista que respeite os limites freqmin e freqmax

//FUNÇÃO DE CONVERSÃO
NOlista* arvToLista(NOarv* arvore, NOlista* lista, int freqmin, int freqmax);
//percorre a arvore (utilizando o caminhamento central direita), inserindo (em lista) os elementos que respeitam os limites freqmin e freqmax
