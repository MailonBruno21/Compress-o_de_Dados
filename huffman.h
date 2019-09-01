#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 127

typedef struct TrieNode {
    int frequencia; // frequencia de ocorrencia das letras
    char letra[MAX];
    struct TrieNode *esquerda; // esquerda recebe 0
    struct TrieNode *direita; // direita recebe 1
} TrieNode;

typedef struct NodeList {
    struct TrieNode *arvore;
    struct NodeList *next;
} NodeList;

typedef struct LinkedList {
    struct NodeList *first; // primeiro nó da lista que tambem é um nó da arvore
    int elementos; // numero de elementos que compoe a arvore
} LinkedList;

typedef struct ASC {
    char letra[MAX];
    int frequencia;
} ASC;

typedef struct tabela {
    ASC vetor[MAX];
} tabelaASC;


void initTabela(tabelaASC *tabela);
void initLinkedList(LinkedList *list);
NodeList *NovoNodeLista(TrieNode *nArv);
TrieNode *NovoNodeArv(int frequencia, char letra, int tamanhoPalavra, TrieNode *esquerda, TrieNode *direita);
void insereLista(LinkedList *list, int frequencia, char letra, int tamanhoPalavra, TrieNode *esquerda, TrieNode *direita);
void IniciaLista(LinkedList *list, tabelaASC *tabela);
void trocar(NodeList *destino, NodeList *origem);
void ordenaLista(LinkedList *list);
void PopUltimos(LinkedList *list);
void construirArvHuffman(LinkedList *list);
void buscaBinario(LinkedList *list);

NodeList *NovoNodeLista(TrieNode *nArv) { // Função que aloca memoria para novos elementos da lista

    NodeList *NewNode = (NodeList*) malloc(sizeof (NodeList));
    NewNode->arvore = nArv;
    NewNode->next = NULL;
    return NewNode;
}

TrieNode *NovoNodeArv(int frequencia, char letra, int tamanhoPalavra, TrieNode *esquerda, TrieNode *direita) { // Função que aloca memoria para novos elementos da arvore

    TrieNode *NewNode = (TrieNode*) malloc(sizeof (NodeList));
    NewNode->frequencia = frequencia;
    NewNode->letra[tamanhoPalavra] = letra;
    NewNode->esquerda = esquerda;
    NewNode->direita = direita;

    return NewNode;
}

void initLinkedList(LinkedList *list) {
    TrieNode *NewNodeTrie = (TrieNode*) malloc(sizeof (TrieNode));
    NodeList *NewNodeList = (NodeList*) malloc(sizeof (NodeList));

    NewNodeTrie = NovoNodeArv(0, '#', 0, NULL, NULL); //Criei um novo nó da arvore
    NewNodeList = NovoNodeLista(NewNodeTrie);
    list->first = NewNodeList;
    list->elementos = 0;
}

void initTabela(tabelaASC *tabela) {
    int i;
    for (i = 0; i <= 127; i++) {
        tabela->vetor[i].letra[0] = i;
        tabela->vetor[i].frequencia = 0;
    }
}

void IniciaLista(LinkedList *list, tabelaASC *tabela) {
    int i;
    for (i = 0; i < MAX; i++) {
        if (tabela->vetor[i].frequencia != 0) {
            insereLista(list,tabela->vetor[i].frequencia,tabela->vetor[i].letra[0],0,NULL,NULL);
            list->elementos++;
        }
    }
}

void insereLista(LinkedList *list, int frequencia, char letra, int tamanhoPalavra, TrieNode *esquerda, TrieNode *direita) {

    TrieNode *NewNodeTrie = (TrieNode*) malloc(sizeof (TrieNode));
    NodeList *NewNodeList = (NodeList*) malloc(sizeof (NodeList));

    NewNodeTrie = NovoNodeArv(frequencia, letra, tamanhoPalavra, esquerda, direita); //Criei um novo nó da arvore
    NewNodeList = NovoNodeLista(NewNodeTrie); //Criei um novo nó da lista

    NodeList *aux = list->first; // Auxiliar recebe o começo da lista
    while (aux->next != NULL) {
        aux = aux->next; // Procura o final para inserir o novo nó;
    }
    aux->next = NewNodeList;
    list->elementos++;
}

void trocar(NodeList *destino, NodeList *origem){            // Troco os dois nós um destino e outro origem

    NodeList *aux = (NodeList*) malloc(sizeof (NodeList));

    aux->arvore->frequencia = destino->arvore->frequencia;
    strcpy(aux->arvore->letra,destino->arvore->letra);
    aux->arvore = destino->arvore;

    destino->arvore->frequencia = origem->arvore->frequencia;
    strcpy(destino->arvore->letra,origem->arvore->letra);
    destino->arvore = origem->arvore;

    origem->arvore->frequencia = aux->arvore->frequencia;
    strcpy(origem->arvore->letra,aux->arvore->letra);
    origem->arvore = aux->arvore;

    free(aux);
}

void ordenaLista(LinkedList *list) {
    int i, j;

    NodeList *controler = list->first;
    NodeList *aux1 = list->first;
    int cont = list->elementos;

    for (i = 0; i < cont; i++) {
        for (j = 0; j< cont; j++) {
            if (controler->arvore->frequencia < aux1->arvore->frequencia) {
                trocar(controler, aux1);
            }
            aux1 = aux1->next;
        }
        controler = controler->next;
    }
    printf("essa bosta aqui\n");
}

void PopUltimos(LinkedList *list) {
    NodeList *aux = list->first;
    NodeList *aux2 = list->first->next;
    while (aux->next->next != NULL) {
        aux = aux->next;
        aux2 = aux2->next;
    }
    NodeList *aux3 = aux->next->next;
    aux->next = NULL; //   Aux recebe o next num porque agora é o ultimo nó
    free(aux3); // Liberei o ultimo
    free(aux2); //  Liberei o penultimo
}

void construirArvHuffman(LinkedList *list) {
    NodeList *aux = list->first;
    ordenaLista(list);

    while(aux->next != NULL){
        if (aux->arvore->frequencia != 0) {
            printf("Frequencia : %d    Letra: %c\n", aux->arvore->frequencia, aux->arvore->letra[0]);
        }
        aux = aux->next;
    }
   printf("Frequencia : %d    Letra: %c\n", aux->arvore->frequencia, aux->arvore->letra[0]);
}

#endif /* HUFFMAN_H */
