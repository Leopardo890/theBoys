// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui

#include <stdio.h>

#include <stdlib.h>

#include "eventos.c" 

// seus #defines vão aqui

#define T_INICIO 0
#define T_FIM_DO_MUNDO 500
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10

// minimize o uso de variáveis globais

struct herois * iniciaHerois(unsigned int nherois){

  struct herois *h;
  if (!(h = malloc(sizeof(struct herois) * nherois)))
    return NULL;
  
  for(unsigned int i = 0; i < nherois; ++i){
    
    h[i].id = i;
    h[i].paci = rand()%101;
    h[i].vel = (rand()%4051 + 50);
    h[i].xp = 0;
    h[i].idBase = 0;
    unsigned int tam = rand()%3 + 1;
    h[i].habili = cjto_aleat(tam, N_HABILIDADES);
  
  }

  return h;
}

struct base * iniciaBase(unsigned int nbase){

  struct base *b;
  if (!(b = malloc(sizeof(struct base) * nbase)))
    return NULL;

  for(unsigned int i = 0; i < nbase; ++i){

    b[i].id = i;
    b[i].local.x = rand()%N_TAMANHO_MUNDO;
    b[i].local.y = rand()%N_TAMANHO_MUNDO;
    b[i].lotacao = (rand()%8 + 3);
    b[i].presentes = cjto_cria(b->lotacao);
    b[i].espera = lista_cria();
  }

  return b;
}

struct missao * iniciaMissao(unsigned int nmissao){

  struct missao *m;
  if (!(m = malloc(sizeof(struct missao) * nmissao)))
    return NULL;

  for (unsigned int i = 0; i < nmissao; ++i){

    m[i].id = i;
    m[i].local.x = rand()%N_TAMANHO_MUNDO;
    m[i].local.y = rand()%N_TAMANHO_MUNDO;
    unsigned int tam = rand()%5 + 6;
    m[i].habili = cjto_aleat(tam, N_HABILIDADES);
    m[i].perigo = rand()%101;

  }

  return m;
}

struct mundo * iniciarMundo(){

  struct mundo *mun;
  if(!(mun = malloc(sizeof(struct mundo))))
    return NULL;

  mun->Nherois = N_HABILIDADES * 5;
  mun->herois = iniciaHerois(mun->Nherois);
  mun->Nbase = mun->Nherois / 5;
  mun->base = iniciaBase(mun->Nbase);
  mun->Nmissao = T_FIM_DO_MUNDO / 10;
  mun->missao = iniciaMissao(mun->Nmissao);
  mun->Nhabili = N_HABILIDADES;
  mun->tamMundo.x = N_TAMANHO_MUNDO;
  mun->tamMundo.y = N_TAMANHO_MUNDO;
  mun->relogio = 0;
  mun->lista = fprio_cria();

  return mun;
}

struct mundo * destruirMundo(struct mundo *mundo){

  for(unsigned int i = 0; i < mundo->Nherois; ++i)
    mundo->herois[i].habili = cjto_destroi(mundo->herois[i].habili);
  
  for(unsigned int i = 0; i < mundo->Nbase; ++i){
    mundo->base[i].presentes = cjto_destroi(mundo->base[i].presentes);
    mundo->base[i].espera = lista_destroi(mundo->base[i].espera);
  }

  for(unsigned int i = 0; i < mundo->Nmissao; ++i)
    mundo->missao[i].habili = cjto_destroi(mundo->missao[i].habili);
  
  mundo->lista = fprio_destroi(mundo->lista);

  free(mundo->herois);
  free(mundo->base);
  free(mundo->missao);
  free(mundo);

  return NULL;
}

void printHerois(struct mundo *mundo){

  printf("Heroi paciencia velocidade experiencia idBase habilidades");
  printf("\n");
  for(unsigned int i = 0; i < mundo->Nherois; ++i){

    printf("%u     ", mundo->herois[i].id);
    printf("%u         ", mundo->herois[i].paci);
    printf("%u          ",mundo->herois[i].vel);
    printf("%u            ", mundo->herois[i].xp);
    printf("%u      ", mundo->herois[i].idBase);
    cjto_imprime(mundo->herois[i].habili);
    printf("\n");

  }
}

void printBase(struct mundo *mundo){

  printf("base lotacao localX localY presentes espera\n");

  for (unsigned int i = 0; i < mundo->Nbase; ++i){

    printf("%u    ", mundo->base[i].id);
    printf("%u       ", mundo->base[i].lotacao);
    printf("%u      ", mundo->base[i].local.x);
    printf("%u      ", mundo->base[i].local.y);
    cjto_imprime(mundo->base->presentes);
    lista_imprime(mundo->base->espera);
    printf("\n");
  }
}

void printMissao(struct mundo *mundo){

  printf("missao perigo localX localY habilidades\n");
  
  for (unsigned int i = 0; i < mundo->Nmissao; ++i){

    printf("%u      ", mundo->missao[i].id);
    printf("%u      ", mundo->missao[i].perigo);
    printf("%u      ", mundo->missao[i].local.x);
    printf("%u      ", mundo->missao[i].local.y);
    cjto_imprime(mundo->missao[i].habili);
    printf("\n");

  }
}


// programa principal
int main (){

  // iniciar mundo

  srand(0);

  struct mundo *mundo;
  mundo = iniciarMundo();

  // executar o laço de simulação

  printHerois(mundo);
  printf("\n\n\n\n");
  printBase(mundo);
  printf("\n\n\n\n");
  printMissao(mundo);

  // destruir o mundo

  mundo = destruirMundo(mundo);

  return (0) ;
}

