// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include "lista.h"

#include <stdlib.h>
#include <stdio.h>


// Cria uma lista vazia.
struct lista_t *lista_cria (){
	
	struct lista_t *lst;
	if (!(lst = malloc(sizeof(struct lista_t))))
		return NULL;
	lst->tamanho = 0;
	lst->prim = NULL;
	lst->ult = NULL;
	return lst;
}

// Remove todos os itens da lista e libera a memória.
struct lista_t *lista_destroi (struct lista_t *lst){

	/*lista vazia*/
	if (lst->tamanho == 0){
		free(lst);
		return NULL;
	}

	while (lst->ult->ant != NULL){
		
		lst->ult = lst->ult->ant;
		free(lst->ult->prox);	
	}
	free(lst->ult);
	free(lst);
	return NULL;
}

// Insere o item na lista na posição indicada.
int lista_insere (struct lista_t *lst, int item, int pos){
	
	/*Lista nao inicializada*/
	if (lst == NULL)
		return -1;
	
	struct item_t *novo;
	if (!(novo = malloc(sizeof(struct item_t))))
		return -1;

	novo->valor = item;
	
	/*Lista vazia*/
	if (lst->tamanho == 0){
		lst->prim = novo;
		lst->ult = novo;
		novo->ant = NULL;
		novo->prox = NULL;
		lst->tamanho++;
		return lst->tamanho;
	}

	/*Primeiro da lista*/
	if (pos == 0){
		novo->prox = lst->prim;
		novo->ant = NULL;
		lst->prim->ant = novo;
		lst->prim = novo;
		lst->tamanho++;
		return lst->tamanho;
	}

	/*Fim da lista*/
	if (pos >= lst->tamanho || pos == -1){
		lst->ult->prox = novo;
		novo->ant = lst->ult;
		lst->ult = novo;
		novo->prox = NULL;
		lst->tamanho++;
		return lst->tamanho;
	}

	/*Meio da lista*/
	struct item_t *aux;
	aux = lst->prim;	
	int i = 0;
	while (i < pos){
		aux = aux->prox;
		i++;
	}
	
	novo->prox = aux;
	novo->ant = aux->ant;
	aux->ant->prox = novo;
	aux->ant = novo;	
	lst->tamanho++;
	return lst->tamanho;

}

// Retira o item da lista da posição indicada.
int lista_retira (struct lista_t *lst, int *item, int pos){

	/*Lista nao inicializada ou vazia*/
	if (lst == NULL || lst->tamanho == 0)
		return -1;

	struct item_t *aux;

	/*Lista com um componente so*/
	if (lst->tamanho == 1){
		aux = lst->prim;
		lst->ult = NULL;
		lst->prim = NULL;
		*item = aux->valor;
		free(aux);
		lst->tamanho--;
		return lst->tamanho;
	}

	/*Primeiro da lista*/
	if (pos == 0){
		aux = lst->prim;
		lst->prim = aux->prox;
		aux->prox->ant = NULL;
		*item = aux->valor;
		free(aux);
		lst->tamanho--;
		return lst->tamanho;
	}

	/*Ultimo da lista*/
	if (pos >= lst->tamanho || pos == -1){
		aux = lst->ult;
		lst->ult = aux->ant;
		lst->ult->prox = NULL;
		*item = aux->valor;
		free(aux);
		lst->tamanho--;
		return lst->tamanho;
	}

	/*Meio da lista*/
	aux = lst->prim;
	int i = 0;
	while (i < pos){
		aux = aux->prox;
		i++;
	}

	aux->ant->prox = aux->prox;
	aux->prox->ant = aux->ant;
	*item = aux->valor;
	free(aux);
	lst->tamanho--;
	return lst->tamanho;

}

// Informa o valor do item na posição indicada, sem retirá-lo.
int lista_consulta (struct lista_t *lst, int *item, int pos){

	/*Lista nao inicializada ou vazia ou posicao invalida*/
	if (lst == NULL || lst->tamanho == 0 || lst->tamanho <= pos)
		return -1;

	struct item_t *aux;

	/*Ultima posicao*/
	if (pos == -1){
		*item = lst->ult->valor;
		return lst->tamanho;	
	}
	
	aux = lst->prim;
	int i = 0;
	while (i < pos){
		aux = aux->prox;
		i++;
	}
	
	*item = aux->valor;
	return lst->tamanho;
}

// Informa a posição da 1ª ocorrência do valor indicado na lista.
int lista_procura (struct lista_t *lst, int valor){

	/*Lista nao inicializada*/
	if (lst == NULL)
		return -1;
	
	struct item_t *aux;
	aux = lst->prim;
	int i = 0;
	while (i < lst->tamanho){
		if (aux->valor == valor)
			return i;
	       	aux = aux->prox;
		i++;	
	}
	return -1;
}

// Informa o tamanho da lista.
int lista_tamanho (struct lista_t *lst){

	/*Lista nao inicializada*/
	if (lst == NULL)
		return -1;
	return lst->tamanho;
}

// Imprime o conteúdo da lista do inicio ao fim.
void lista_imprime (struct lista_t *lst){

	struct item_t *aux;
	aux = lst->prim;
	while (aux != NULL && aux->prox != NULL){
		
		printf("%d ", aux->valor);
		aux = aux->prox;
	}
	if (aux != NULL)
		printf("%d", aux->valor);
}
