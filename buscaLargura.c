#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

typedef struct elemento {
    struct elemento* proximo;
    struct no* valor;
} Elemento;

typedef struct fila {
    struct elemento* cabeca;
    struct elemento* cauda;    
} Fila;

Fila* criarFila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->cabeca = NULL;
    fila->cauda = NULL;
  
    return fila;
}

void adicionarFila(Fila* fila, No* valor) {
    Elemento* elemento = malloc(sizeof(Elemento));
    
    elemento->valor = valor;
    elemento->proximo = NULL;

    if (fila->cauda != NULL) {
        fila->cauda->proximo = elemento;
        fila->cauda = elemento;
    } else {
        fila->cabeca = elemento;
        fila->cauda = elemento;
    }
}

No* removerFila(Fila* fila) {
    Elemento* cabeca = fila->cabeca;
    No* valor = cabeca->valor;

    fila->cabeca = cabeca->proximo;

    if (fila->cabeca == NULL) {
        fila->cauda = NULL;
    }

    free(cabeca);

    return valor;
}

int filaVazia(Fila* fila) {
    return fila->cabeca == NULL;
}

Arvore* criarArvore() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int arvoreVazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarArvore(Arvore* arvore, No* pai, int valor) {
    No *no = malloc(sizeof(No));

    no->pai = pai;
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor;
    
    if (pai == NULL) {
        arvore->raiz = no;
    }

    return no;
}

void removerArvore(Arvore* arvore, No* no) {
    if (no->esquerda != NULL) {
        removerArvore(arvore, no->esquerda); 
    }
  
    if (no->direita != NULL) {
        removerArvore(arvore, no->direita);
    }
  
    if (no->pai == NULL) {
        arvore->raiz = NULL;
    } else {
        if (no->pai->esquerda == no) {
            no->pai->esquerda = NULL;
        } else {
            no->pai->direita = NULL;
        }
    }

    free(no);
}

void percorrerLargura(No* no, void (callback)(int)) {
    Fila* fila = criarFila();
    adicionarFila(fila, no);
    
    while (!filaVazia(fila)) {
        No* no = removerFila(fila);

        if (no->esquerda != NULL) {
            adicionarFila(fila, no->esquerda);
        }

        if (no->direita != NULL) {
            adicionarFila(fila, no->direita);
        }

        callback(no->valor);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

int main() {
    Arvore* a = criarArvore();

    No* no4 = adicionarArvore(a, NULL, 4);
    
    No* no2 = adicionarArvore(a, no4, 2);
    no4->esquerda = no2;

    No* no8 = adicionarArvore(a, no4, 8);
    no4->direita = no8;

    No* no1 = adicionarArvore(a, no2, 1);
    no2->esquerda = no1;

    No* no3 = adicionarArvore(a, no2, 3);
    no2->direita = no3;

    No* no6 = adicionarArvore(a, no8, 6);
    no8->esquerda = no6;

    No* no9 = adicionarArvore(a, no8, 9);
    no8->direita = no9;

    No* no5 = adicionarArvore(a, no6, 5);
    no6->esquerda = no5;

    No* no7 = adicionarArvore(a, no6, 7);
    no6->direita = no7;

    //Implemente um algoritmo que visite todos os nós de uma árvore binária com uma busca em largura.○ Exemplo, para a árvore abaixo a saída deve ser: 4, 2, 8, 1, 3, 6, 9, 5, 7

    printf("Largura: ");
    percorrerLargura(a->raiz,visitar);
    printf("\n");
}