/*
 * PCO003 - Lab 2 - Criando seu primeiro kernel (item 3)
 * Anderson André Pereira Eleutério
 */
#include <stdio.h>
#include "kernel.h"

#define MEU_NOME      "Anderson André Pereira Eleutério"
#define MINHA_MATRICULA "2024104010"

// a) imprime o nome e termina
char procNome(void){
    printf("Nome: %s\n", MEU_NOME);
    return SUCCESS;
}

// b) imprime a matricula e termina
char procMatricula(void){
    printf("Matricula: %s\n", MINHA_MATRICULA);
    return SUCCESS;
}

// c) imprime UNIFEI e pede para ser reexecutado
char procUnifei(void){
    printf("UNIFEI\n");
    return REPEAT;
}

// d) imprime PCO003 e quantas vezes ja foi executado
char procPco(void){
    static int execucoes = 0;
    execucoes++;
    printf("PCO003 - execucao %d\n", execucoes);
    return REPEAT;
}

int main(void){
    // prioridades do maior para o menor
    static process p1 = {procNome,      4};
    static process p2 = {procMatricula, 3};
    static process p3 = {procUnifei,    2};
    static process p4 = {procPco,       1};

    kernelInit();
    kernelAddProc(&p1);
    kernelAddProc(&p2);
    kernelAddProc(&p3);
    kernelAddProc(&p4);
    kernelLoop();   // nunca retorna

    return 0;
}
