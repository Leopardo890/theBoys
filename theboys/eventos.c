#include "mundo.c"

void chega(struct mundo *mundo, struct evento0 *item){

    mundo->herois[item->h].idBase = item->b;

    int esp;
    int presentes;
    presentes = cjto_card(mundo->base[item->b].presentes);
    int fila;
    fila = lista_tamanho(mundo->base[item->b].espera);
  
    if ((unsigned int)presentes < mundo->base[item->b].lotacao && fila == 0)
        esp = 1;
    else if ((mundo->herois[item->h].paci) > (unsigned int)(10 * fila))
        esp = 1;

    struct evento0 *e;
    if (!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = item->b;  

    if (esp)
        fprio_insere(mundo->lista, e, 1, mundo->relogio++);
    else
        fprio_insere(mundo->lista, e, 2, mundo->relogio++);
}

void espera(struct mundo *mundo, struct evento0 *item){

    lista_insere(mundo->base[item->b].espera, item->h, -1);

    struct evento2 *e;
    if (!(e = malloc(sizeof(struct evento2))))
        return;
    e->b = item->b;
    fprio_insere(mundo->lista, e, 3, mundo->relogio++);
}

void desiste(struct mundo *mundo, struct evento1 *item){

    unsigned int d;
    d = rand()%mundo->Nbase;

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;
    
    e->h = item->h;
    e->b = d;

    fprio_insere(mundo->lista, e, 4, mundo->relogio++);
}
