#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
  int info;
  struct arvore* esq;
  struct arvore* dir;
} Arvore;

int estaVazia(Arvore* a) {
  return (a == NULL);
}

Arvore* insere(Arvore* a, int v) {
  if(estaVazia(a)) {
    a = (Arvore*)malloc(sizeof(Arvore));
    a->info = v;
    a->esq = a->dir = NULL;
  }
  else {
    if(v < a->info)
      a->esq = insere(a->esq, v);
    else
      a->dir = insere(a->dir, v);
  }
  return a;
}

Arvore* busca(Arvore* a, int v) {
  if(estaVazia(a))
    return NULL;
  else {
    if(v == a->info)
      return a;
    else if(v < a->info)
      return busca(a->esq, v);
    else
      return busca(a->dir, v);
  }
}

Arvore* remover(Arvore* a, int v) {
  if(estaVazia(a))
    return NULL;
  else {
    if(v < a->info)
      a->esq = remover(a->esq, v);
    else if(v > a->info)
      a->dir = remover(a->dir, v);
    else {
      if(a->esq == NULL && a->dir == NULL) {
        free(a);
        a = NULL;
      }
      else if (a->dir == NULL) {
        Arvore* t = a;
        a = a->esq;
        free(t);
      }
      else if(a->esq == NULL) {
        Arvore* t = a;
        a = a->dir;
        free(t);
      }
      else {
        Arvore* t = a->esq;
        while(t->dir != NULL)
          t = t->dir;
        a->info = t->info;
        t->info = v;
        a->esq = remover(a->esq, v);
      }
    }
    return a;
  }
}

void imprime(Arvore* a) {
  printf("<");
  if(!estaVazia(a)) {
    printf("%d", a->info);
    imprime(a->esq);
    imprime(a->dir);
  }
  printf(">");
}

Arvore* liberar(Arvore* a) {
  if(!estaVazia(a)) {
    liberar(a->esq);
    liberar(a->dir);
    free(a);
  }
  return NULL;
}

int contNos(Arvore* a) {
  if(estaVazia(a))
    return 0;
  else
    return (contNos(a->esq) + contNos(a->dir) + 1);
}

int altura(Arvore* a) {
  if(estaVazia(a))
    return -1;
  else if(estaVazia(a->esq) && estaVazia(a->dir))
    return 0;
  else {
    int e = altura(a->esq);
    int d = altura(a->dir);
    if(e > d)
      return (e + 1);
    else
      return (d + 1);
  }
}

int impares(Arvore* a) {
  if(estaVazia(a))
    return 0;
  else {
    if(a->info % 2 == 1)
      return impares(a->esq) + impares(a->dir) + 1;
    else
      return impares(a->esq) + impares(a->dir);
  }
}

Arvore* maior(Arvore* a) {
  if(estaVazia(a))
    return NULL;
  else {
    if(a->info < a->dir->info && a->dir != NULL)
      return maior(a->dir);
    else
      return a;
  }
}

Arvore* menor(Arvore* a) {
  if(estaVazia(a))
    return NULL;
  else {
    if(a->info > a->esq->info && a->esq != NULL)
      return menor(a->esq);
    else
      return a;
  }
}

Arvore* balancear(Arvore* a) {
  if (estaVazia(a))
    return NULL;
  else {
    int nosEsq = contNos(a->esq);
    int nosDir = contNos(a->dir);

    if (nosDir >= nosEsq + 2) {
      a->esq = insere(a->esq, a->info);
      Arvore* aux = menor(a->dir);
      a->info = aux->info;
      a->dir = remover(a->dir, aux->info);
      return a;
    } else if (nosEsq >= nosDir + 2) {
      a->dir = insere(a->dir, a->info);
      Arvore* aux = maior(a->esq);
      a->info = aux->info;
      a->esq = remover(a->esq, aux->info);
      return a;
    } else {
      a->esq = balancear(a->esq);
      a->dir = balancear(a->dir);
      return a;
    }
  }
}

int main(void) {
  Arvore* a = NULL;

  a = insere(a, 5);
  insere(a, 3);
  insere(a, 2);
  insere(a, 4);
  // insere(a, 7);
  // insere(a, 6);
  // insere(a, 8);
  insere(a, 1);
  insere(a, 10);
  insere(a, 9);
   imprime(a);
   printf("\n");

  // // remover(a, 7);

  // // imprime(a);
  // // printf("\n");

  // printf("Qtd N° impares: %d\n",impares(a));
  // printf("N° nós: %d\n\n", contNos(a));
  
  // remover(a, 3);
  // remover(a, 5);

  // imprime(a);
  // printf("\n");
  // printf(" N° impares: %d\n",impares(a));
  // printf("N° nós: %d\n\n", contNos(a));

  // imprime(maior(a));
  // remover(a, 10);
  // printf("\n");
  // imprime(maior(a));
  // printf("\n");
  // imprime(menor(a));
  // printf("\n");
  // remover(a, 1);
  // imprime(menor(a));
  // printf("\n");
  
  
  
  balancear(a);

  imprime(a);
  printf("\n");
  
  return 0;
}
