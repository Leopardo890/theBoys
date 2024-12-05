#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "conjunto.h"
#include "lista.h"
#include "fprio.h"

#define EV_CHEGA 0
#define EV_ESPERA 1
#define EV_DESISTE 2
#define EV_AVISA 3
#define EV_VIAJA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_MISSAO 7
#define EV_MORRE 8
#define EV_FIM 9

struct herois{

    int id;
    struct cjto_t *habili;
    int paci;
    int vel;
    int xp;
    int idBase;
    int vivo;

};

struct cordenada{

    int x;
    int y;

};

struct base{

    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct lista_t *espera;
    struct cordenada local;
    struct cjto_t *habili;
    int missaos;
    int fimaMax;

};

struct missao{

    int id;
    struct cjto_t *habili;
    int perigo;
    struct cordenada local;
    int tent;

};

struct mundo{

    int Nherois;
    struct herois *herois;
    int Nbase;
    struct base *base;
    int Nmissao;
    struct missao *missao;
    int Nhabili;
    struct cordenada tamMundo;
    int relogio;
    struct fprio_t *lista;
    int eventos;
    int cumpridas;
    int minTent;
    int maxTent;

};

struct evento0{

    int h;
    int b;
};

struct evento1{

    int h;
};

struct evento2{

    int b;
};

struct evento3{
    
    int m;
};

struct evento4{
    
    int h;
    int b;
    int m;
};


void chega(struct mundo *mundo, struct evento0 *item);

void espera(struct mundo *mundo, struct evento0 *item);

void desiste(struct mundo *mundo, struct evento0 *item);

void avisa(struct mundo *mundo, struct evento2 *item);

void entra(struct mundo *mundo, struct evento0 *item);

void viaja(struct mundo *mundo, struct evento0 *item);

void sai(struct mundo *mundo, struct evento0 *item);

void morre(struct mundo *mundo, struct evento4 *item);

void missao(struct mundo *mundo, struct evento3 *item);

void fim(struct mundo *mundo);