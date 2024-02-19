#define maxnome 100

typedef struct nodoAbp{
    int cal;
    char nome[maxnome];
    struct nodoAbp *esq;
    struct nodoAbp *dir;   
}NodoAbp;

extern int compAbp;

NodoAbp* inicializaAbp();

NodoAbp* insereAbp(NodoAbp *raiz, int cal, char *nome);

void imprimePreEsq(NodoAbp *raiz);

void imprimeCentEsq(NodoAbp *raiz);

void imprimePosEsq(NodoAbp *raiz);

int contaNodo(NodoAbp *raiz);

void desenhaArvore(NodoAbp *raiz, int nivel);

NodoAbp* consultaAbp(NodoAbp *raiz, char *chave);

int alturaAbp(NodoAbp *raiz);
