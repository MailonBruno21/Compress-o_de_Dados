#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <locale.h>

int main(int argc, char** argv) {
    
    setlocale(LC_ALL, "Portuguese");
    int i, j;
    FILE *texto;
    char string[100];
    LinkedList Huffman;
    tabelaASC tabela;
    initTabela(&tabela);
    initLinkedList(&Huffman);

    texto = fopen("Texto.txt", "r");

    if (texto == NULL) {
        printf("Erro ao abrir o Arquivo");
    }

    while (fgets(string, 100, texto) != NULL) {
        int tamanho = strlen(string);
        tamanho = (tamanho - 2);        
        for (j = 0; j < tamanho; j++) {            
            for (i = 0; i < 127; i++) {
                if (string[j] == i) {
                    tabela.vetor[i].frequencia++;
                    tabela.vetor[i].letra[0] = string[j];
                }
            }
        }
    }

    IniciaLista(&Huffman, &tabela);
    construirArvHuffman(&Huffman);






    return (EXIT_SUCCESS);

}