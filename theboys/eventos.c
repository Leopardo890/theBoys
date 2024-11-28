#include <math.h>

#include "mundo.c"

/*
\\evento0 -> h e b
\\evento1 -> h
\\evento2 -> b

\\0 -> chega
\\1 -> espera
\\2 -> desiste
\\3 -> avisa
\\4 -> viaja
\\5 -> entra
\\6 -> sai
\\7 -> missao
*/

void chega(struct mundo *mundo, struct evento0 *item){

    mundo->herois[item->h].idBase = item->b;

    int esp;
    int presentes;
    presentes = cjto_card(mundo->base[item->b].presentes);
    int fila;
    fila = lista_tamanho(mundo->base[item->b].espera);
  
    if (presentes < mundo->base[item->b].lotacao && fila == 0)
        esp = 1;
    else if ((mundo->herois[item->h].paci) > (10 * fila))
        esp = 1;

    struct evento0 *e;
    if (!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = item->b;  

    if (esp)
        fprio_insere(mundo->lista, e, 1, mundo->relogio);
    else
        fprio_insere(mundo->lista, e, 2, mundo->relogio);
}

void espera(struct mundo *mundo, struct evento0 *item){

    lista_insere(mundo->base[item->b].espera, item->h, -1);

    lista_imprime(mundo->base[item->b].espera);

    printf("\n");

    struct evento2 *e;
    if (!(e = malloc(sizeof(struct evento2))))
        return;

    e->b = item->b;

    fprio_insere(mundo->lista, e, 3, mundo->relogio);
}

void desiste(struct mundo *mundo, struct evento0 *item){

    unsigned int d;
    d = rand()%mundo->Nbase;

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;
    
    e->h = item->h;
    e->b = d;

    fprio_insere(mundo->lista, e, 4, mundo->relogio);
}

void avisa(struct mundo *mundo, struct evento2 *item){

    int presentes, tamFila;
    presentes = cjto_card(mundo->base[item->b].presentes);
    tamFila = lista_tamanho(mundo->base[item->b].espera);

    lista_imprime(mundo->base[item->b].espera);
    printf("\n");
    printf("lotacao=%d\n", mundo->base[item->b].lotacao);

    while(presentes < mundo->base[item->b].lotacao && tamFila > 0){

        int h;
        tamFila = lista_retira(mundo->base[item->b].espera, &h, 0);
        presentes = cjto_insere(mundo->base[item->b].presentes, h);
        
        printf("tamFila=%d\npresentes=%d\n", tamFila, presentes);

        struct evento0 *e;
        if (!(e = malloc(sizeof(struct evento0))))
            return;
            
        e->h = h;
        e->b = item->b;

        fprio_insere(mundo->lista, e, 5, mundo->relogio);
    }

    cjto_imprime(mundo->base[item->b].presentes);
    printf("\n");
    lista_imprime(mundo->base[item->b].espera);
    printf("\n");

}

void entra(struct mundo *mundo, struct evento0 *item){

    int tpb;
    tpb = 15 + (mundo->herois[item->h].paci * (rand()%20 + 1));

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = item->b;

    fprio_insere(mundo->lista, e, 6, mundo->relogio + tpb);
}

void viaja(struct mundo *mundo, struct evento0 *item){

    int dist, x1, x2, y1, y2;
    
    x1 = mundo->base[mundo->herois[item->h].idBase].local.x;
    y1 = mundo->base[mundo->herois[item->h].idBase].local.y;

    x2 = mundo->base[item->b].local.x;
    y2 = mundo->base[item->b].local.y;

    dist = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);

    int duracao;
    duracao = dist / mundo->herois[item->h].vel;

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = item->b;

    printf("duracao = %d/%d = %d\n", dist, mundo->herois[item->h].vel, duracao);

    fprio_insere(mundo->lista, e, 0, mundo->relogio + duracao);
}

void sai(struct mundo *mundo, struct evento0 *item){

    cjto_imprime(mundo->base[item->b].presentes);
    printf("\n");

    cjto_retira(mundo->base[item->b].presentes, item->h);

    printf("saiu=%d\n", item->h);
    
    int d;
    d = rand()%mundo->Nbase;

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = d;

    struct evento2 *v;
    if(!(v = malloc(sizeof(struct evento2))))
        return;

    v->b = item->b;

    fprio_insere(mundo->lista, e, 4, mundo->relogio);
    fprio_insere(mundo->lista, v, 3, mundo->relogio);
}

void morre(struct mundo *mundo, struct evento0 *item){

    cjto_retira(mundo->base[item->b].presentes, item->h);
    mundo->herois[item->h].id = -1;

    struct evento2 *e;
    if (!(e = malloc(sizeof(struct evento2))))
        return;

    e->b = item->b;

    fprio_insere(mundo->lista, e, 3, mundo->relogio);
}

void missao(struct mundo *mundo, struct evento3 *item){

    int x1, x2, y1, y2, dist;
    int basePerto;
    int bmp = -1;

    for(int i = 0; i < mundo->Nbase; ++i){

        struct cjto_t *habTotal, *aux;
        habTotal = cjto_cria(30);

        printf("base=%d\n", i);
        cjto_imprime(mundo->base[i].presentes);

        printf("\n");

        for(int j = 0; j < mundo->Nherois; ++j){

            if(cjto_pertence(mundo->base[i].presentes, j)){

                printf("heroi=%d\n", j);
                cjto_imprime(mundo->herois[j].habili);
                printf("\n");

                aux = habTotal;
                habTotal = cjto_uniao(habTotal, mundo->herois[j].habili);
                aux = cjto_destroi(aux);

                cjto_imprime(habTotal);
                printf("\n");

            }
        }

        printf("comparacao:\n");
        cjto_imprime(habTotal);
        printf("\n");
        cjto_imprime(mundo->missao[item->m].habili);
        printf("\n");

        if(cjto_iguais(habTotal, mundo->missao[item->m].habili)){

            x1 = mundo->base[i].local.x;
            y1 = mundo->base[i].local.y;

            x2 = mundo->missao[item->m].local.x;
            y2 = mundo->missao[item->m].local.y;

            dist = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);

            if (i == 0 || dist < bmp){
                bmp = dist;
                basePerto = i;
            }

            printf("dist=%d\n", dist);

        }
        
        habTotal = cjto_destroi(habTotal);
    }

    printf("bmp=%d\n", bmp);
    printf("basePerto=%d\n", basePerto);

    
}