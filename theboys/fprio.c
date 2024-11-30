// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR

#include <stdio.h>
#include <stdlib.h>

#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria (){

	struct fprio_t *f;
	if (!(f = malloc(sizeof(struct fprio_t))))
		return NULL;
	f->prim = NULL;
	f->num = 0;
	return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f){

	if (f == NULL){
		free(f);
		return NULL;
	}
	
	struct fpnodo_t *aux;

	while (f->prim != NULL){

		free(f->prim->item);
		aux = f->prim;
		f->prim = aux->prox;
		free(aux);
	}

	free(f);
	return NULL;

}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){

	if (f == NULL || item == NULL)
		return -1;

	struct fpnodo_t *novo;
	if (!(novo = malloc(sizeof(struct fpnodo_t))))
		return -1;
	
	novo->item = item;
	novo->tipo = tipo;
	novo->prio = prio;

	if (f->num == 0){
		f->prim = novo;
		novo->prox = NULL;
		return ++f->num;
	}

	struct fpnodo_t *aux;
	
	aux = f->prim;

	while (aux != NULL){
		if (aux->item == item){
			free(novo);
			return -1;
		}
		aux = aux->prox;
	}

	if (f->prim->prio > novo->prio){
		novo->prox = f->prim;
		f->prim = novo;
		return ++f->num;
	}

	aux = f->prim;

	while (aux->prox != NULL){

		if (aux->prox->prio > novo->prio){
			novo->prox = aux->prox;
			aux->prox = novo;
			break;
		}

		aux = aux->prox;
	}

	if (aux->prox == NULL){
		aux->prox = novo;
		novo->prox = NULL;
	}

	return ++f->num;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
	
	if (f == NULL || f->num == 0 || tipo == NULL || prio == NULL)
		return NULL;

	void *aux;
	
	*tipo = f->prim->tipo;
	*prio = f->prim->prio;
	aux = f->prim->item;

	struct fpnodo_t *aux1;
	aux1 = f->prim;

	if (f->prim->prox == NULL)
		f->prim = NULL;
	else
		f->prim = aux1->prox;
	
	free(aux1);
	f->num -= 1;

	return aux;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f){

	if (f == NULL)
		return -1;

	return f->num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f){

	if (f == NULL)
		return;

	struct fpnodo_t *aux;
	aux = f->prim;

	while(aux != NULL){
		printf("(%d %d) ", aux->tipo, aux->prio);
		aux = aux->prox;
	}
	
	return;
}
