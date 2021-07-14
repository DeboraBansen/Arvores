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

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            No* novo = malloc(sizeof(No));
            novo->valor = valor;
            novo->pai = no;

            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            No* novo = malloc(sizeof(No));
			novo->valor = valor;
            novo->pai = no;
			
            no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        No* novo = malloc(sizeof(No));
        novo->valor = valor;
        
        arvore->raiz = novo;
			
        return novo;
    } else {
        return adicionarNo(arvore->raiz, valor);
    }
}

void remover(Arvore* arvore, No* no) {
    if (no->esquerda != NULL) {
        remover(arvore, no->esquerda); 
    }
  
    if (no->direita != NULL) {
        remover(arvore, no->direita);
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

No* localizar(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(No* no, void (callback)(int)) {
    if (no != NULL) {
        percorrerProfundidadeInOrder(no->esquerda,callback);
        callback(no->valor);
        percorrerProfundidadeInOrder(no->direita,callback);
    }
}

void percorrerProfundidadePreOrder(No* no, void (callback)(int)) {
    if (no != NULL) {
        callback(no->valor);
        percorrerProfundidadePreOrder(no->esquerda,callback);
        percorrerProfundidadePreOrder(no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(No* no, void (callback)(int)) {
    if (no != NULL) {
        percorrerProfundidadePosOrder(no->esquerda,callback);
        percorrerProfundidadePosOrder(no->direita,callback);
        callback(no->valor);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

int main() {
    Arvore* a = criar();

    adicionar(a,4);
    adicionar(a,2);
    adicionar(a,1);
    adicionar(a,3);
    adicionar(a,8);
    adicionar(a,9);
    adicionar(a,6);
    adicionar(a,5);
    adicionar(a,7);

    //Implemente uma função para adicionar nós em uma árvore binária que respeite as regras abaixo necessárias para uma pesquisa binária. O valor de cada nó deve ser inteiro. O nó filho à esquerda possui um valor menor ou igual ao valor de seu nó pai.O nó filho à direita possui um valor maior do que o valor de seu nó pai. Exemplo: deve ser gerada a árvore abaixo ao adicionar 4, 2, 1, 3, 8, 9, 6, 5, 7

    printf("In-order: ");
    percorrerProfundidadeInOrder(a->raiz,visitar);
    printf("\nPre-order: ");
    percorrerProfundidadePreOrder(a->raiz,visitar);
    printf("\nPos-order: ");
    percorrerProfundidadePosOrder(a->raiz,visitar);
    printf("\n");
}