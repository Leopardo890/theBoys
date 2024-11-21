#include "conjunto.h"
#include "lista.h"
#include "fprio.h"

struct herois{

    unsigned int id;
    struct cjto_t *habili;
    unsigned int paci;
    unsigned int vel;
    unsigned int xp;
    unsigned int idBase;

};

struct cordenada{

    unsigned int x;
    unsigned int y;

};

struct base{

    unsigned int id;
    unsigned int lotacao;
    struct cjto_t *presentes;
    struct lista_t *espera;
    struct cordenada local;

};

struct missao{

    unsigned int id;
    struct cjto_t *habili;
    unsigned int perigo;
    struct cordenada local;

};

struct mundo{

    unsigned int Nherois;
    struct herois *herois;
    unsigned int Nbase;
    struct base *base;
    unsigned int Nmissao;
    struct missao *missao;
    unsigned int Nhabili;
    struct cordenada tamMundo;
    unsigned int relogio;
    struct fprio_t *lista;

};

struct evento0{

    unsigned int idHeroi;
    unsigned int idBase;
};

struct evento1{

    unsigned int idBase;
};