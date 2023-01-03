#include <stdio.h>
#include <stdlib.h>

struct Nodo {
  int codigo;
  struct Nodo *esquerda;
  struct Nodo *direita;
  int peso;
};

int max(int a, int b);

int peso(struct Nodo *N) {
  if (N == NULL)
    return 0;
  return N->peso;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

struct Nodo *novoNodo(int codigo) {
  struct Nodo *nodo = (struct Nodo *)malloc(sizeof(struct Nodo));
  nodo->codigo = codigo;
  nodo->esquerda = NULL;
  nodo->direita = NULL;
  nodo->peso = 1;
  return (nodo);
}

struct Nodo *direitaRotacao(struct Nodo *y) {
  struct Nodo *x = y->esquerda;
  struct Nodo *T2 = x->direita;

  x->direita = y;
  y->esquerda = T2;

  y->peso = max(peso(y->esquerda), peso(y->direita)) + 1;
  x->peso = max(peso(x->esquerda), peso(x->direita)) + 1;

  return x;
}

struct Nodo *esquerdaRotacao(struct Nodo *x) {
  struct Nodo *y = x->direita;
  struct Nodo *T2 = y->esquerda;

  y->esquerda = x;
  x->direita = T2;

  x->peso = max(peso(x->esquerda), peso(x->direita)) + 1;
  y->peso = max(peso(y->esquerda), peso(y->direita)) + 1;

  return y;
}

int getBalance(struct Nodo *N) {
  if (N == NULL)
    return 0;
  return peso(N->esquerda) - peso(N->direita);
}

struct Nodo *insertNodo(struct Nodo *nodo, int codigo) {
  if (nodo == NULL)
    return (novoNodo(codigo));

  if (codigo < nodo->codigo)
    nodo->esquerda = insertNodo(nodo->esquerda, codigo);
  else if (codigo > nodo->codigo)
    nodo->direita = insertNodo(nodo->direita, codigo);
  else
    return nodo;

  nodo->peso = 1 + max(peso(nodo->esquerda),
               	 peso(nodo->direita));

  int balance = getBalance(nodo);
  if (balance > 1 && codigo < nodo->esquerda->codigo)
    return direitaRotacao(nodo);

  if (balance < -1 && codigo > nodo->direita->codigo)
    return esquerdaRotacao(nodo);

  if (balance > 1 && codigo > nodo->esquerda->codigo) {
    nodo->esquerda = esquerdaRotacao(nodo->esquerda);
    return direitaRotacao(nodo);
  }

  if (balance < -1 && codigo < nodo->direita->codigo) {
    nodo->direita = direitaRotacao(nodo->direita);
    return esquerdaRotacao(nodo);
  }

  return nodo;
}

struct Nodo *minValueNodo(struct Nodo *nodo) {
  struct Nodo *atual = nodo;

  while (atual->esquerda != NULL)
    atual = atual->esquerda;

  return atual;
}

struct Nodo *deletaNodo(struct Nodo *raiz, int codigo) {
  if (raiz == NULL)
    return raiz;

  if (codigo < raiz->codigo)
    raiz->esquerda = deletaNodo(raiz->esquerda, codigo);

  else if (codigo > raiz->codigo)
    raiz->direita = deletaNodo(raiz->direita, codigo);

  else {
    if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
      struct Nodo *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

      if (temp == NULL) {
        temp = raiz;
        raiz = NULL;
      } else
        *raiz = *temp;
      free(temp);
    } else {
      struct Nodo *temp = minValueNodo(raiz->direita);

      raiz->codigo = temp->codigo;

      raiz->direita = deletaNodo(raiz->direita, temp->codigo);
    }
  }

  if (raiz == NULL)
    return raiz;

  raiz->peso = 1 + max(peso(raiz->esquerda),
               peso(raiz->direita));

  int balance = getBalance(raiz);
  if (balance > 1 && getBalance(raiz->esquerda) >= 0)
    return direitaRotacao(raiz);

  if (balance > 1 && getBalance(raiz->esquerda) < 0) {
    raiz->esquerda = esquerdaRotacao(raiz->esquerda);
    return direitaRotacao(raiz);
  }

  if (balance < -1 && getBalance(raiz->direita) <= 0)
    return esquerdaRotacao(raiz);

  if (balance < -1 && getBalance(raiz->direita) > 0) {
    raiz->direita = direitaRotacao(raiz->direita);
    return esquerdaRotacao(raiz);
  }

  return raiz;
}

void printPreOrder(struct Nodo *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->codigo);
    printPreOrder(raiz->esquerda);
    printPreOrder(raiz->direita);
  }
}

bool checkPesoBalance(struct Nodo *raiz, int *peso) {
  int esquerdaPeso = 0, direitaPeso = 0;
  int e = 0, d = 0;

  if (raiz == NULL) {
    *peso = 0;
    return 1;
  }

  e = checkPesoBalance(raiz->esquerda, &esquerdaPeso);
  d = checkPesoBalance(raiz->direita, &direitaPeso);

  *peso = (esquerdaPeso > direitaPeso ? esquerdaPeso : direitaPeso) + 1;

  if ((esquerdaPeso - direitaPeso >= 2) || (direitaPeso - esquerdaPeso >= 2))
    return 0;

  else
    return e && d;
}

int main() {
  struct Nodo *raiz = NULL;
  int peso = 0;

  raiz = insertNodo(raiz, 78);
  raiz = insertNodo(raiz, 54);
  raiz = insertNodo(raiz, 63);
  raiz = insertNodo(raiz, 87);
  raiz = insertNodo(raiz, 82);
  raiz = insertNodo(raiz, 96);
  raiz = insertNodo(raiz, 99);
  raiz = insertNodo(raiz, 100);


  printPreOrder(raiz);
  
  if (checkPesoBalance(raiz, &peso))
    printf("\nArvore balanceada.");
  else
    printf("\nArvore nao balanceada.");
    
  //Professora eu fiquei com preguiça de fazer um contrutor de desenhos printf pra ficar melhor visualizavel a arvore

  //raiz = deletaNodo(raiz, 1);
  //printf("\nDepois de deletar: ");
  //printPreOrder(raiz);

  return 0;
}
