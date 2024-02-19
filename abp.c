#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"

NodoAbp* inicializaAbp(){
    return NULL;
}

NodoAbp* insereAbp(NodoAbp *raiz, int cal, char *nome){
    if(raiz == NULL){
        raiz = (NodoAbp*)malloc(sizeof(NodoAbp));
        raiz->cal = cal;
        strcpy(raiz->nome,nome);
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    else if (strcmp(nome, raiz->nome) < 0){
        raiz->esq = insereAbp(raiz->esq, cal, nome);
    }
    else{
         raiz->dir = insereAbp(raiz->dir, cal, nome);
    }
    return raiz;
}

void imprimePreEsq(NodoAbp *raiz){
    if(raiz != NULL){
        printf("%s|%d\n", raiz->nome,raiz->cal);
        imprimePreEsq(raiz->esq);
        imprimePreEsq(raiz->dir);
    }
}

void imprimeCentEsq(NodoAbp *raiz){
    if(raiz != NULL){
        imprimeCentEsq(raiz->esq);
        printf("%s|%d\n", raiz->nome,raiz->cal);
        imprimeCentEsq(raiz->dir);
    }
}

void imprimePosEsq(NodoAbp *raiz){
    if(raiz != NULL){
        imprimePosEsq(raiz->esq);
        imprimePosEsq(raiz->dir);
        printf("%s|%d\n", raiz->nome,raiz->cal);
    }
}

int contaNodo(NodoAbp *raiz){
    if(raiz != NULL){
        return 1 + contaNodo(raiz->esq) + contaNodo(raiz->dir);
    }
    else return 0;
}

void desenhaArvore(NodoAbp *raiz, int nivel){
    int i = 0;
    if(raiz!=NULL){
        while(i<=nivel){
            printf("=");
            i++;
        }
        printf("%s\n", raiz->nome);
        if (raiz->esq){
            desenhaArvore(raiz->esq, nivel+1);
        }
        if (raiz->dir){
            desenhaArvore(raiz->dir, nivel+1);
        }
    }
    
}

NodoAbp* consultaAbp(NodoAbp *raiz, char *chave){
    while(raiz){
        compAbp++;
        if(!strcmp(raiz->nome,chave)){
            return raiz;
        }
        else{
            if(strcmp(raiz->nome,chave) > 0){
                raiz = raiz->esq;
            }
            else{
                raiz = raiz->dir;
            }
        }
    }
    return NULL;
}

int alturaAbp(NodoAbp *raiz){
    int altEsq, altDir;

    if(raiz){
        altEsq = alturaAbp(raiz->esq);
        altDir = alturaAbp(raiz->dir);
        if(altEsq > altDir)
            return (1+altEsq);
        else
            return (1+altDir);  
    }else{
        return 0;
    }
}