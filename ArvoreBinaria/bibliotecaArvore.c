#include <stdio.h>
#include <stdlib.h>
#include "bibliotecaArvore.h"

void menu(){
	int op;
	arvore *arv = criarNulo(),
	        *buscar = NULL,
	        *pai = NULL;
	int codigo;

	do{
		printf("\n1 - Inserir nó"
				"\n2 - Pesquisar nó"
				"\n3 - Excluir nó"
				"\n4 - Sair"
				"\nDigite sua opção: ");
		scanf("%d",&op);

		switch (op){
		case 1:
		    codigo = gerarCodigoRandomico();
		    percorrerIn(arv);
			break;
		case 2:
		    codigo = solicitarCodigo("\nDigite o código a ser procurado: ");
		    buscar = arv;
		    pai = NULL;
		    pesquisarNo(&buscar, &pai, codigo);
		    if (buscar == NULL) {
		        printf("\nNó não encontrado");
		    }else if (pai != NULL) {
		        printf("\nEncontrado %p - Pai %i %p", buscar, pai->codigo, pai);
		    } else {
		        printf("\nEncontrado %p - Nó raiz", buscar);
		    }
			break;
		case 3:
		    codigo = solicitarCodigo("\nDigite o código a ser excluído: ");
		    deletarNo(arv, codigo);
		    percorrerIn(arv);
			break;
		case 4:
			printf("\nPrograma finalizado.");
			break;
		default:
			printf("\nValor inválido.");
		}
	} while (op != 4);
}

arvore* criarNulo() {
    return NULL;
}

arvore* criarNo(int cod) {
    //Alocar espaço para ele
    arvore *novo = (arvore*) malloc (sizeof(arvore));
    
    //Preencher dados básicos
    novo->codigo = cod;
    
    //Criar os ponteiros
    novo->esquerda = criarNulo();
    novo->direita = criarNulo();
    
    //Retornar o endereço do novo. 
    return novo;
}

arvore* inserirNo(arvore *arv, int cod){
    if (arv == NULL) {
        arv = criarNo(cod);
    } else if (cod < arv->codigo){
        arv->esquerda = inserirNo(arv->esquerda, cod);
    } else {
        arv->direita = inserirNo(arv->direita, cod);
    }
    
    return arv;
}

void percorrerIn(arvore *arv) {
    if (arv != NULL) {
        percorrerIn(arv->esquerda);
        printf("\nEsquerda %p - Nó %i - %p - Direita %p",
                arv->esquerda, arv->codigo, arv, arv->direita);
        percorrerIn(arv->direita);
    }
}

void percorrerPre(arvore *arv) {
    if (arv != NULL) {
        printf("\nEsquerda %p - Nó %i - %p - Direita %p",
                arv->esquerda, arv->codigo, arv, arv->direita);
        percorrerIn(arv->esquerda);
        percorrerIn(arv->direita);
    }
}

void percorrerPos(arvore *arv) {
    if (arv != NULL) {
        percorrerIn(arv->esquerda);
        percorrerIn(arv->direita);
        printf("\nEsquerda %p - Nó %i - %p - Direita %p",
                arv->esquerda, arv->codigo, arv, arv->direita);
    }
}

void pesquisarNo(arvore **no, arvore **pai, int cod) {
    if ((*no) != NULL) {
        if (cod == (*no)->codigo) {
            return;
        } else 
            (*pai) = (*no);
            if (cod < (*no)->codigo) {
                (*no) = (*no)->esquerda;
            } else {
                (*no) = (*no)->direita;
            }
            pesquisarNo(no, pai, cod);
    }    
}

int solicitarCodigo(char *texto){
    int codigo;
    do{
        printf("%s", texto);
        scanf("%i", &codigo);
        if (codigo <= 0) {
            printf("\nInválido.");
        }
    } while (codigo <= 0);
}

int gerarCodigoRandomico(){
    int codigo = rand() % 1000;
    if (codigo > 0) {
        return codigo;
    } else {
        return gerarCodigoRandomico();
    }
}

arvore* deletarNo(arvore *pai, int x){
    if(pai==NULL){
        return NULL;
	}
    if (x > pai->codigo){
        pai->direita = deletarNo(pai->direita, x);
	} else if(x < pai->codigo){
		pai->esquerda = deletarNo(pai->esquerda, x);
	} else{
        if(pai->esquerda==NULL && pai->direita==NULL){
            free(pai);
            return NULL;
        } else if(pai->esquerda==NULL || pai->direita==NULL){
            arvore *temp;
            if(pai->esquerda==NULL){
                temp = pai->direita;
			} else {
                temp = pai->esquerda;
            	free(pai);
           		return temp;
			}
        } else{
            arvore *temp = acharMinimo(pai->direita);
            pai->codigo = temp->codigo;
            pai->direita = deletarNo(pai->direita, temp->codigo);
        }
    }
    return pai;
}

arvore* acharMinimo(arvore *pai){
    if(pai == NULL){
    	return NULL;
	} else if(pai->direita != NULL){
		return acharMinimo(pai->direita);
	}
    return pai;
}
