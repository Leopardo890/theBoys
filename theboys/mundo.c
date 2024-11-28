#include "conjunto.h"
#include "lista.h"
#include "fprio.h"

struct herois{

    int id;
    struct cjto_t *habili;
    int paci;
    int vel;
    int xp;
    int idBase;

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

};

struct missao{

    int id;
    struct cjto_t *habili;
    int perigo;
    struct cordenada local;

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
