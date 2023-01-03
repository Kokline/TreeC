#include <stdio.h>
#include <stdlib.h>

struct nodo {
  int codigo;
  struct nodo *esquerda, *direita;
};

struct nodo *novoNodo(int item) {
  struct nodo *temp = (struct nodo *)malloc(sizeof(struct nodo));
  temp->codigo = item;
  temp->esquerda = temp->direita = NULL;
  return temp;
}

void ordenar(struct nodo *raiz) {
  if (raiz != NULL) {
    ordenar(raiz->esquerda);

    printf("%d ", raiz->codigo);

    ordenar(raiz->direita);
  }
}

struct nodo *insert(struct nodo *nodo, int codigo) {
  if (nodo == NULL) return novoNodo(codigo);

  if (codigo < nodo->codigo)
    nodo->esquerda = insert(nodo->esquerda, codigo);
  else
    nodo->direita = insert(nodo->direita, codigo);

  return nodo;
}

struct nodo *minValueNodo(struct nodo *nodo) {
  struct nodo *atual = nodo;

  while (atual && atual->esquerda != NULL)
    atual = atual->esquerda;

  return atual;
}

struct nodo *deletaNodo(struct nodo *raiz, int codigo) {
  if (raiz == NULL) return raiz;

  if (codigo < raiz->codigo)
    raiz->esquerda = deletaNodo(raiz->esquerda, codigo);
  else if (codigo > raiz->codigo)
    raiz->direita = deletaNodo(raiz->direita, codigo);

  else {
    if (raiz->esquerda == NULL) {
      struct nodo *temp = raiz->direita;
      free(raiz);
      return temp;
    } else if (raiz->direita == NULL) {
      struct nodo *temp = raiz->esquerda;
      free(raiz);
      return temp;
    }

    struct nodo *temp = minValueNodo(raiz->direita);

    raiz->codigo = temp->codigo;

    raiz->direita = deletaNodo(raiz->direita, temp->codigo);
  }
  return raiz;
}

int main() {
  struct nodo *raiz = NULL;
  raiz = insert(raiz, 81);
  raiz = insert(raiz, 79);
  raiz = insert(raiz, 1);
  raiz = insert(raiz, 39);
  raiz = insert(raiz, 26);
  raiz = insert(raiz, 41);
  raiz = insert(raiz, 13);
  raiz = insert(raiz, 64);
  raiz = insert(raiz, 55);
  raiz = insert(raiz, 51);

  ordenar(raiz);

  //printf("\nDepois de deletar: \n");
  //raiz = deletaNodo(raiz, 81);
  //ordenar(raiz);
}
