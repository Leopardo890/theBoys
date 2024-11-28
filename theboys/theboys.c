// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui

#include <stdio.h>

#include <stdlib.h>

#include "eventos.c" 

// seus #defines vão aqui

#define T_INICIO 0
#define T_FIM_DO_MUNDO 10000
#define N_TAMANHO_MUNDO 2000
#define N_HABILIDADES 3

// minimize o uso de variáveis globais

struct herois * iniciaHerois(int nherois){

    struct herois *h;
    if (!(h = malloc(sizeof(struct herois) * nherois)))
        return NULL;
    
    for(int i = 0; i < nherois; ++i){
      
        h[i].id = i;
        h[i].paci = rand()%101;
        h[i].vel = (rand()%4051 + 50);
        h[i].xp = 0;
        h[i].idBase = 0;
        int tam = rand()%3 + 1;
        h[i].habili = cjto_aleat(tam, N_HABILIDADES);
        h[i].vivo = 1;
    
    }

    return h;
}

struct base * iniciaBase(int nbase, int nherois){

    struct base *b;
    if (!(b = malloc(sizeof(struct base) * nbase)))
        return NULL;

    for(int i = 0; i < nbase; ++i){

        b[i].id = i;
        b[i].local.x = rand()%N_TAMANHO_MUNDO;
        b[i].local.y = rand()%N_TAMANHO_MUNDO;
        b[i].lotacao = (rand()%8 + 3);
        b[i].presentes = cjto_cria(nherois);
        b[i].espera = lista_cria();
        b[i].fimaMax = 0;
        b[i].missaos = 0;
    }

    return b;
}

struct missao * iniciaMissao(int nmissao){

    struct missao *m;
    if (!(m = malloc(sizeof(struct missao) * nmissao)))
       return NULL;

    for (int i = 0; i < nmissao; ++i){

        m[i].id = i;
        m[i].local.x = rand()%N_TAMANHO_MUNDO;
        m[i].local.y = rand()%N_TAMANHO_MUNDO;
        int tam = rand()%5 + 6;
        m[i].habili = cjto_aleat(tam, N_HABILIDADES);
        m[i].perigo = rand()%101;
        m[i].cumprida = 0;
        m[i].tent = 0;

    }

    return m;
}

struct fprio_t * fprio_inicia(struct mundo *mundo){

    int tempo;
    
    for (int i = 0; i < mundo->Nherois; ++i){  
      
        struct evento0 *e;
        if (!(e = malloc(sizeof(struct evento0))))
            return NULL;

        e->h = i;
        e->b = rand()%mundo->Nbase;

        tempo = rand()%4321;

        fprio_insere(mundo->lista, e, 0, tempo);
    
    }

    for (int i = 0; i < mundo->Nmissao; ++i){

        struct evento3 *e;
        if(!(e = malloc(sizeof(struct evento3))))
            return NULL;
        
        e->m = i;

        tempo = rand()%(T_FIM_DO_MUNDO+1);

        fprio_insere(mundo->lista, e, 7, tempo);

    }

    void *p;
    p = malloc(sizeof(int));

    fprio_insere(mundo->lista, p , 9, T_FIM_DO_MUNDO);

    return mundo->lista;
}

struct mundo * iniciarMundo(){

    struct mundo *mun;
    if(!(mun = malloc(sizeof(struct mundo))))
        return NULL;

    mun->Nherois = N_HABILIDADES * 5;
    mun->herois = iniciaHerois(mun->Nherois);
    mun->Nbase = mun->Nherois / 5;
    mun->base = iniciaBase(mun->Nbase, mun->Nherois);
    mun->Nmissao = T_FIM_DO_MUNDO / 10;
    mun->missao = iniciaMissao(mun->Nmissao);
    mun->Nhabili = N_HABILIDADES;
    mun->tamMundo.x = N_TAMANHO_MUNDO;
    mun->tamMundo.y = N_TAMANHO_MUNDO;
    mun->relogio = 0;
    mun->lista = fprio_cria();
    mun->eventos = 0;
    mun->lista = fprio_inicia(mun);

    return mun;
}

struct mundo * destruirMundo(struct mundo *mundo){

    for(int i = 0; i < mundo->Nherois; ++i)
        mundo->herois[i].habili = cjto_destroi(mundo->herois[i].habili);
    
    for(int i = 0; i < mundo->Nbase; ++i){
        mundo->base[i].presentes = cjto_destroi(mundo->base[i].presentes);
        mundo->base[i].espera = lista_destroi(mundo->base[i].espera);
    }

    for(int i = 0; i < mundo->Nmissao; ++i)
        mundo->missao[i].habili = cjto_destroi(mundo->missao[i].habili);
    
    mundo->lista = fprio_destroi(mundo->lista);

    free(mundo->herois);
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

    printf("\n\n");

    while (mundo->relogio < T_FIM_DO_MUNDO){

        int tipo;
        int tempo;
        void *item;
        item = fprio_retira(mundo->lista, &tipo, &tempo);

        if (tempo > mundo->relogio)
            mundo->relogio = tempo;

        switch(tipo){
            case 0:{
                chega(mundo, item);
                break;
            }
            case 1:{
                espera(mundo, item);
                break;
            }
            case 2:{
                desiste(mundo, item);
                break;
            }
            case 3:{
                avisa(mundo, item);
                break;
            }
            case 4:{
                viaja(mundo, item);
                break;
            }
            case 5:{
                entra(mundo, item);
                break;
            }
            case 6:{
                sai(mundo, item);
                break;
            }
            case 7:{
                missao(mundo, item);
                break;
            }
            case 8:{
                morre(mundo, item);
                break;;
            }
            case 9:{
                fim(mundo);
                break;
            }
        }

        mundo->eventos++;

        free(item);
      
    }

    // destruir o mundo

    mundo = destruirMundo(mundo);

    return (0) ;
  }

