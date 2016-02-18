#include <stdio.h>
#include <stdlib.h>
#include "header.c"
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int freq_min = atoi(argv[1]);
    int freq_max = atoi(argv[2]);
    char nomearq[50] = "arquivo.txt";
    stringcopy(nomearq,argv[3]);
    char saida[50] = "saida.txt";
    char saidalenta[50] = "saidalenta.txt";
    clock_t t1, t2 ,t3;
    t1 = clock();

    NOarv* arvore = iniArvore();
    NOlista* lista = iniLista();
    arvore = arvLeArquivo(arvore, nomearq);
    lista = arvToLista(arvore, lista, freq_min, freq_max);
    escreveSaida(lista, freq_min, freq_max, saida);
    t2 = clock();
    lista = iniLista();
    lista = listLeArquivo(lista, nomearq);
    escreveSaida(lista, freq_min, freq_max, saidalenta);
    t3 = clock();

    printf("Tempo (arvore): %.2f segundos\n", (((float)t2 - (float)t1) / 1000000.0F ) * 1000);
    printf("Tempo (lista): %.2f segundos\n", (((float)t3 - (float)t2) / 1000000.0F ) * 1000);


    //return 0;
}
