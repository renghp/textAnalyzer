#include "header.h"



void stringcopy(char destino[30], char origem[30]){
    //similiar a strcpy
    char buffer = 'a';
    int indice =0;

    while(buffer != '\0'){
        buffer = origem[indice];
        destino[indice] = buffer;
        indice++;
    }
}

//LISTa
NOlista* iniLista(){
    //inicializa uma estrutra de dados do tipo lista
    return NULL;
}

void imprimeLista(NOlista* lista, int freqmin, int freqmax){
    //imprime os elementos (de lista) que respeitam os limites freqmin e freqmax
    NOlista* ptaux; //percorrerá a lista

    if(lista==NULL)
        printf("\nLista vazia!\n");

    else{
        ptaux = lista;
        do{
            if (ptaux->freq >= freqmin && ptaux->freq <= freqmax) //dentro dos limites
                printf("%i %s\n", ptaux->freq, ptaux->word);
            ptaux = ptaux->prox;
        }while(ptaux!=NULL);
    }

    printf("\n");
}

void swap(NOlista* a, NOlista* b){
    //troca a informação de dois nodos
    char tempword[30];
    strcpy(tempword, a->word);
    int tempfreq = a->freq;
    strcpy(a->word, b->word);
    a->freq = b->freq;
    strcpy(b->word, tempword);
    b->freq = tempfreq;
}

NOlista* listInsertWord(NOlista* lista, char palavra[30]){
    //insere uma palavra numa lista ordenada pelo campo frequência (em empate, ordenada lexicograficamente)
    NOlista* ptaux = lista; //percorrerá a lista
    NOlista* inserido; //novo nó

    if(palavra == NULL) //testa a consistência da palavra
        return lista;

    if (ptaux==NULL){ //caso lista vazia
        //inicializa o novo nó
        inserido = malloc(sizeof(NOlista));
        strcpy(inserido->word,palavra); //teria que ser strcpy
        inserido->freq = 1;
        inserido->ant = NULL;
        inserido->prox = NULL;

        return inserido;
    }

    //busca palavra
    while(ptaux->prox!=NULL && ((strcmp(ptaux->word, palavra)) != 0)){
        ptaux = ptaux->prox;
    }

    if ((strcmp(ptaux->word, palavra))==0){ //se achou, atualiza a frequência
        ptaux->freq++;
        if (ptaux->ant==NULL)
            return lista;

        while(ptaux->ant != NULL && (ptaux->ant->freq < ptaux->freq)){ //e reposiciona a palavra em relação a sua nova frequência
            swap(ptaux->ant, ptaux);
            ptaux = ptaux->ant;
        }
    }

    else{ //se não achou, o insere no final
        //inicializa o novo nó
        inserido = malloc(sizeof(NOlista));
        strcpy(inserido->word, palavra);
        inserido->freq = 1;
        inserido->ant = ptaux;
        inserido->prox = NULL;
        ptaux->prox = inserido;
        ptaux = ptaux->prox;


    }

    //ordena em ordem alfabética
    while(ptaux->ant != NULL && ptaux->ant->freq == ptaux->freq && strcmp(ptaux->ant->word, ptaux->word)==1){
            swap(ptaux->ant, ptaux);
            ptaux = ptaux->ant;
        }

        return lista;

}

NOlista* listInsertProcWord(NOlista* lista, char palavra[30], int frequencia){
    //insere (em lista) uma palavra cuja frequência já foi processada
    NOlista* ptaux = lista; //percorre a lista
    NOlista* inserido = (NOlista*) malloc(sizeof(NOlista)); //inicializa novo nó
    stringcopy(inserido->word, palavra);
    inserido->freq = frequencia;


    if(lista==NULL){ //caso lista vazia
        inserido->ant = NULL;
        inserido->prox = NULL;
        return inserido;
    }

    if(ptaux->freq < frequencia){ //caso palavra deve ser o primeiro elemento
        inserido->prox = ptaux;
        inserido->ant = NULL;
        return inserido;
    }

    while(ptaux->prox != NULL && ptaux->prox->freq > frequencia) //busca posição correta
        ptaux = ptaux->prox;

    inserido->ant = ptaux; //atualiza ponteiros
    inserido->prox = ptaux->prox;
    ptaux->prox = inserido;

    return lista;
}

void stolower(char string[]){
    //aplica a função tolower(char c) a todos os caracteres de string
    int index=0;

    while(string[index] != '\0'){
        string[index] = tolower(string[index]);
        index++;
    }
}

NOlista* listInsertSentence(NOlista* lista, char *str){
    //quebra uma frase em várias palavras e as insere em lista
    char * palavra;

    palavra = strtok(str, " ,.-*+&¨%/#@!?\n\t:;´~'^`0123456789{}[]()_»«<>\"°"); //quebra e insere a primeira palavra
    lista = listInsertWord(lista, palavra);

    while(palavra != NULL){ //quebra e insere o até o fim
        palavra = strtok(NULL, " ,.-*+&¨%/#@!?\n\t:;´~'^`0123456789{}[]()_»«<>\"°");
        lista = listInsertWord(lista, palavra);
    }
    return lista;
}



//ARVORE

NOarv* iniArvore(){
    //inicializa uma estrutra de dados do tipo árvore
    return NULL;
}

void imprimeArv(NOarv* arvore){
    //imprime uma arvore usando o caminhamento central esquerda
    if(arvore->esq)
        imprimeArv(arvore->esq);
    if (arvore->word)
        printf("%s, %i\n", arvore->word, arvore->freq);
    else
        puts("ARVORE VAZIA");
    if(arvore->dir)
        imprimeArv(arvore->dir);

}


NOarv* arvInsertWord(NOarv* arvore, char palavra[30]){
    //insere uma palavra numa árvore, ordenada lexicograficamente
    if (palavra == NULL) //testa a consistência da palavra
        return arvore;

    if (arvore==NULL){ //caso arvore vazia
        arvore = (NOarv*) malloc(sizeof(NOarv));
        stringcopy(arvore->word, palavra);
        arvore->freq = 1;
        arvore->esq = NULL;
        arvore->dir = NULL;

        return arvore;
    }

    int compara = strcmp(arvore->word, palavra); //definirá qual galho seguir

    if (compara==0){ //achou a palavra
        arvore->freq++;
        return arvore;
    }

    //se ainda não achou, altera apenas uma das sub-árvores
    if (compara<0)
        arvore->dir = arvInsertWord(arvore->dir, palavra);

    else
        arvore->esq = arvInsertWord(arvore->esq, palavra);

    //retorna a árvore alterada
    return arvore;
}

NOarv* arvInsertSentence(NOarv* arvore, char *str){
    //quebra uma frase em várias palavras e as insere em arvore
    //vide listInsertSentence
    char * palavra;

    palavra = strtok(str, " ,.-*+&¨%/#@!?\n\t:;´~'^`0123456789{}[]()_»«<>\"°");
    arvore = arvInsertWord(arvore, palavra);

    while(palavra != NULL){
        palavra = strtok(NULL, " ,.-*+&¨%/#@!?\n\t:;´~'^`0123456789{}[]()_»«<>\"°");
        arvore = arvInsertWord(arvore, palavra);
    }

    return arvore;
}


//FUNÇÕES DE ARQUIVO
NOlista* listLeArquivo(NOlista* lista, char nomearquivo[30]){
    //lê todas as linhas de um texto (cujo nome do arquivo é apontado por nomearquivo), as inserindo em lista
    FILE* arquivo = fopen(nomearquivo, "r");
    if (arquivo == NULL) perror ("Error opening file"); //consistência na abertura

    char linha [200]; //buffer

    while(fgets(linha, 200, arquivo) != NULL){ //enquanto houver o que ler
        stolower(linha); //normaliza a linha
        lista = listInsertSentence(lista, linha); //e a insere
    }

    fclose(arquivo);

    return lista;
}


NOarv* arvLeArquivo(NOarv* arvore, char nomearquivo[30]){
    //lê todas as linhas de um texto (cujo nome do arquivo é apontado por nomearquivo), as inserindo em arvore
    //vide listLeArquivo

    FILE* arquivo = fopen(nomearquivo, "r");
    if (arquivo == NULL) perror ("Error opening file");

    char linha [200];

    while(fgets(linha, 200, arquivo) != NULL){
        stolower(linha);
        arvore = arvInsertSentence(arvore, linha);
    }

    fclose(arquivo);

    return arvore;
}

void escreveSaida(NOlista* lista, int freqmin, int freqmax, char nomearq[30]){
    //escreve (em um arquivo de texto nomeado por nomearq) cada palavra (e sua frequencia) contida em lista que respeite os limites freqmin e freqmax
    FILE * arq = fopen(nomearq, "w");

    NOlista* ptaux; //percorrerá a lista

    fprintf(arq, "JOSE PEDRO MARTINEZ\tRENAN LUIGI MARTINS GUARESE\n2014 - ESTRUTURAS DE DADOS\n\n");

    if(lista==NULL)
        fprintf(arq, "\nLista vazia!\n");



    else{
        ptaux = lista;
        do{
            if (ptaux->freq >= freqmin && ptaux->freq <= freqmax) //respeitando limites
                fprintf(arq, "%i %s\n", ptaux->freq, ptaux->word);
        ptaux = ptaux->prox;
        }while(ptaux!=NULL);
    }

    printf("\n");
}


//FUNÇÃO DE CONVERSÃO
NOlista* arvToLista(NOarv* arvore, NOlista* lista, int freqmin, int freqmax){
    //percorre a arvore (utilizando o caminhamento central direita), inserindo (em lista) os elementos que respeitam os limites freqmin e freqmax
    if(arvore->dir) //consistência nos galhos
        lista = arvToLista(arvore->dir, lista, freqmin, freqmax);
    if(arvore->freq >= freqmin && arvore->freq <= freqmax)
        lista = listInsertProcWord(lista, arvore->word, arvore->freq);
    if(arvore->esq)
        lista = arvToLista(arvore->esq, lista, freqmin, freqmax);


   return lista;
}






