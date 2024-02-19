#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

NodoAvl* inicializaAvl(){
    return NULL;
}

NodoAvl* InsereAvl (NodoAvl *a, int *ok, int *rot, int cal, char *nome){
    if (a == NULL) {
        a = (NodoAvl*) malloc(sizeof(NodoAvl));
        a->cal = cal;
        strcpy(a->nome,nome);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcmp(nome,a->nome) < 0) {
        a->esq = InsereAvl(a->esq,ok,rot,cal,nome);
        if (*ok) {
            switch (a->FB) {
                case -1:    a->FB = 0; 
                            *ok = 0;
                            break;
                case 0:
                            a->FB = 1;
                            break;
                case 1:
                            a = Caso1(a,ok);
                            (*rot)++;
                            break;
            }
        }
    }
    else {
        a->dir = InsereAvl(a->dir,ok,rot,cal,nome);
        if (*ok) {
            switch (a->FB) {
                case 1:
                        a->FB = 0;
                        *ok = 0;
                        break;
                case 0:
                        a->FB = -1;
                        break;
                case -1: 
                        a = Caso2(a,ok);
                        (*rot)++;
                        break;
            }
        }
    }
    return a;
}

NodoAvl* consultaAvl(NodoAvl *a, char *chave){
    while(a != NULL){
        compAvl++;
        if(!strcmp(chave,a->nome)){
            return a;
        }
        else{
            if(strcmp(a->nome,chave) > 0){
                a = a->esq;
            }else{
                a = a->dir;
            }
        }
    }
    return NULL;
}

NodoAvl* Caso1 (NodoAvl *a , int *ok){
    NodoAvl *z;
    z = a->esq;
    if (z->FB == 1)
    a = rotacao_direita(a);

    else
    a = rotacao_dupla_direita(a);

    a->FB = 0;
    *ok = 0;
    return a;
}

NodoAvl* Caso2 (NodoAvl *a , int *ok){
    NodoAvl *z;
    z = a->dir;
    if (z->FB == -1)
    a = rotacao_esquerda(a);

    else
    a = rotacao_dupla_esquerda(a);

    a->FB = 0;
    *ok = 0;
    return a;
}

NodoAvl* rotacao_dupla_esquerda (NodoAvl *p){
    NodoAvl *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
    else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    p = y;
    return p;
}

NodoAvl* rotacao_dupla_direita (NodoAvl* p){
    NodoAvl *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
    else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;
    p = v;
    return p;
} 

NodoAvl* rotacao_esquerda(NodoAvl *p){
    NodoAvl *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
} 

NodoAvl* rotacao_direita(NodoAvl* p){
    NodoAvl *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

int calculaFB (NodoAvl *a){
    return abs(alturaAvl(a->esq) - alturaAvl(a->dir));
}

void fator(NodoAvl *a, int *maiorFat){
    int fb;
    if(a != NULL){
        fb = calculaFB(a);
        if(fb>*maiorFat){
            *maiorFat = fb;
        }
        fator(a->esq, maiorFat);
        fator(a->dir, maiorFat);
    }
}

int alturaAvl (NodoAvl *a){
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
    return 0;
    else{
        Alt_Esq = alturaAvl(a->esq);
        Alt_Dir = alturaAvl(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}