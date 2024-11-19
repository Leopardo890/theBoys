// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui

#include <stdio.h>

#include <stdlib.h>

#include "mundo.c" 

// seus #defines vão aqui

#define T_INICIO 0
#define T_FIM_DO_MUNDO 10
#define N_TAMANHO_MUNDO 100
#define N_HABILIDADES 1

// minimize o uso de variáveis globais

struct heroi * iniciaHerois(unsigned int nherois){

  struct heroi *h;
  if (!(h = malloc(sizeof(struct heroi) * nherois)))
    return NULL;
  
  for(unsigned int i = 0; i < nherois; ++i){
    
    h->id = i;
    h->paci = rand()%101;
    h->vel = (rand()%4051 + 50);
    h->xp = 0;
    h->idBase = 0;
    h->habili = cjto_aleat(N_HABILIDADES, 3);
  
  }

  return h;
}

struct base * iniciaBase(unsigned int nbase){

  struct base *b;
  if (!(b = malloc(sizeof(struct base) * nbase)))
    return NULL;

  for(unsigned int i = 0; i < nbase; ++i){

    b->id = i;
    b->local.x = rand()%N_TAMANHO_MUNDO;
    b->local.y = rand()%N_TAMANHO_MUNDO;
    b->lotacao = (rand()%8 + 3);
    b->presentes = cjto_cria(b->lotacao);
    b->espera = lista_cria();
  }

  return b;
}

struct missao * iniciaMissao(unsigned int nmissao){

  struct missao *m;
  if (!(m = malloc(sizeof(struct missao) * nmissao)))
    return NULL;

  for (unsigned int i = 0; i < nmissao; ++i){

    m->id = i;
    m->local.x = rand()%N_TAMANHO_MUNDO;
    m->local.y = rand()%N_TAMANHO_MUNDO;
    m->habili = cjto_aleat(N_HABILIDADES, 10);
    m->perigo = rand()%101;

  }

  return m;
}

struct mundo * iniciarMundo(){

  struct mundo *mun;
  if(!(mun = malloc(sizeof(struct mundo))))
    return NULL;

  mun->Nherois = N_HABILIDADES * 5;
  mun->herois = iniciaHerois(mun->Nherois);
  mun->Nbase = N_HEROIS / 5;
  mun->base = iniciaBase(mun->Nbase);
  mun->Nmissao = T_FIM_DO_MUNDO / 10;
  mun->missao = iniciaMissao(mun->Nmissao);
  mun->Nhabili = N_HABILIDADES;
  mun->tamMundo.x = N_TAMANHO_MUNDO;
  mun->tamMundo.y = N_TAMANHO_MUNDO;
  mun->relogio = 0;

  return mun;
}

struct mundo * destruirMundo(struct mundo *mundo){

  cjto_destroi(mundo->heroi->habili);
  cjto_destroi(mundo->base->presentes);
  cjto_destroi(mundo->missao->habili);
  free(mundo->heroi);
  free(mundo->base);
  free(mundo->missao);
  free(mundo);

  return NULL;
}

// programa principal
int main (){

  // iniciar mundo

  srand(0);

  struct mundo *mundo;
  mundo = iniciarMundo();

  // executar o laço de simulação



  // destruir o mundo

  mundo = destruirMundo(mundo);

  return (0) ;
}

