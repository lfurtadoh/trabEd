#define maxnome 100

typedef struct nodoAvl{
    int cal;
    char nome[maxnome];
    struct nodoAvl *esq;
    struct nodoAvl *dir; 
    int FB;  
}NodoAvl;

extern int compAvl;

NodoAvl* inicializaAvl();

NodoAvl* InsereAvl (NodoAvl *a, int *ok, int *rot, int cal, char *nome);

NodoAvl* consultaAvl(NodoAvl *a, char *chave);

NodoAvl* Caso1 (NodoAvl *a , int *ok);

NodoAvl* Caso2 (NodoAvl *a , int *ok);

NodoAvl* rotacao_dupla_esquerda (NodoAvl *p);

NodoAvl* rotacao_dupla_direita (NodoAvl* p);

NodoAvl* rotacao_esquerda(NodoAvl *p);

NodoAvl* rotacao_direita(NodoAvl* p);

int alturaAvl (NodoAvl *a);