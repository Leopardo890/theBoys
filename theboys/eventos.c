#include "mundo.c"

void chega(struct mundo *mundo, unsigned int t, unsigned int h, 
            unsigned int b){

    mundo->herois[h].idBase = b;

    int esp;
    int presentes;
    presentes = cjto_card(mundo->base[b].presentes);
    int fila;
    fila = lista_tamanho(mundo->base[b].espera);
  
    if ((unsigned int)presentes < mundo->base[b].lotacao && fila == 0)
        esp = 1;
    else if ((mundo->herois[h].paci) > (unsigned int)(10 * fila))
        esp = 1;

    struct evento0 *e;
    if (!(e = malloc(sizeof(struct evento0))))
        return;

    e->idHeroi = h;
    e->idBase = b;  

    if (esp)
        fprio_insere(mundo->lista, e, 0, t);
    else
        fprio_insere(mundo->lista, e, 1, t);
}

void espera(struct mundo *mundo, unsigned int h, unsigned int t,
            unsigned int b){

    lista_insere(mundo->base[b].espera, h, -1);

    struct evento1 *e;
    if (!(e = malloc(sizeof(struct evento1))))
        return;
    e->idBase = b;
    fprio_insere(mundo->lista, e, 2, t);
}

void desiste(struct mundo *mundo, unsigned int h, unsigned int t){

    unsigned int d;
    d = rand()%mundo->Nbase;

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;
    
    e->idHeroi = h;
    e->idBase = d;

    fprio_insere(mundo->lista, e, 3, t);
}
