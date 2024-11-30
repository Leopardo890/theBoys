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
\\8 -> morre
\\9 -> fim
*/

void chega(struct mundo *mundo, struct evento0 *item){

    mundo->herois[item->h].idBase = item->b;

    int esp = 0;
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

    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ", mundo->relogio,
            item->h, item->b, cjto_card(mundo->base[item->b].presentes),
            mundo->base[item->b].lotacao);

    if (esp){
        
        printf("ESPERA\n");
        fprio_insere(mundo->lista, e, 1, mundo->relogio);

    } else {

        printf("DESISTE\n");
        fprio_insere(mundo->lista, e, 2, mundo->relogio);
    
    }
}

void espera(struct mundo *mundo, struct evento0 *item){

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", mundo->relogio, item->h,
            item->b, lista_tamanho(mundo->base[item->b].espera));

    lista_insere(mundo->base[item->b].espera, item->h, -1);

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

    printf("%6d: DESISTE HEROI %2d BASE %d\n", mundo->relogio, item->h, 
            item->b);

    fprio_insere(mundo->lista, e, 4, mundo->relogio);
}

void avisa(struct mundo *mundo, struct evento2 *item){

    int presentes, tamFila;
    presentes = cjto_card(mundo->base[item->b].presentes);
    tamFila = lista_tamanho(mundo->base[item->b].espera);

    if(tamFila > mundo->base[item->b].fimaMax)
        mundo->base[item->b].fimaMax = tamFila;

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", mundo->relogio,
            item->b, presentes, mundo->base[item->b].lotacao);
    lista_imprime(mundo->base[item->b].espera);
    printf(" ]\n");

    while(presentes < mundo->base[item->b].lotacao && tamFila > 0){

        int h;
        tamFila = lista_retira(mundo->base[item->b].espera, &h, 0);
        presentes = cjto_insere(mundo->base[item->b].presentes, h);

        struct cjto_t *aux;
        aux = cjto_uniao(mundo->herois[h].habili, mundo->base[item->b].habili);
        cjto_destroi(mundo->base[item->b].habili);
        mundo->base[item->b].habili = aux;

        struct evento0 *e;
        if (!(e = malloc(sizeof(struct evento0))))
            return;
            
        e->h = h;
        e->b = item->b;

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", mundo->relogio,
                item->b, h);

        fprio_insere(mundo->lista, e, 5, mundo->relogio);
    }


}

void entra(struct mundo *mundo, struct evento0 *item){

    int tpb;
    tpb = 15 + (mundo->herois[item->h].paci * (rand()%20 + 1));

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = item->b;

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", mundo->relogio,
            item->h, item->b, cjto_card(mundo->base[item->b].presentes),
            mundo->base[item->b].lotacao, mundo->relogio + tpb);

    fprio_insere(mundo->lista, e, 6, mundo->relogio + tpb);
}

void viaja(struct mundo *mundo, struct evento0 *item){

    int dist, x1, x2, y1, y2;
    
    x1 = mundo->base[mundo->herois[item->h].idBase].local.x;
    y1 = mundo->base[mundo->herois[item->h].idBase].local.y;

    x2 = mundo->base[item->b].local.x;
    y2 = mundo->base[item->b].local.y;

    dist = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
    dist = sqrt(dist);

    int duracao;
    duracao = dist / mundo->herois[item->h].vel;

    struct evento0 *e;
    if(!(e = malloc(sizeof(struct evento0))))
        return;

    e->h = item->h;
    e->b = item->b;

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", 
            mundo->relogio, item->h, mundo->herois[item->h].idBase, item->b,
            dist, mundo->herois[item->h].vel, mundo->relogio + duracao);

    fprio_insere(mundo->lista, e, 0, mundo->relogio + duracao);
}

void sai(struct mundo *mundo, struct evento0 *item){

    cjto_retira(mundo->base[item->b].presentes, item->h);

    struct cjto_t *aux;
    aux = cjto_dif(mundo->base[item->b].habili, mundo->herois[item->h].habili);
    cjto_destroi(mundo->base[item->b].habili);
    mundo->base[item->b].habili = aux;

    for(int i = 0; i < mundo->Nherois; ++i){

        if(cjto_pertence(mundo->base[item->b].presentes, i)){

            aux = cjto_uniao(mundo->herois[i].habili, 
                                mundo->base[item->b].habili);
            cjto_destroi(mundo->base[item->b].habili);
            mundo->base[item->b].habili = aux;
        }
    }
    
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

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", mundo->relogio,
            item->h, item->b, cjto_card(mundo->base[item->b].presentes),
            mundo->base[item->b].lotacao);

    fprio_insere(mundo->lista, e, 4, mundo->relogio);
    fprio_insere(mundo->lista, v, 3, mundo->relogio);
}

void morre(struct mundo *mundo, struct evento4 *item){

    cjto_retira(mundo->base[item->b].presentes, item->h);
    mundo->herois[item->h].vivo = 0;

    struct cjto_t *aux;
    aux = cjto_dif(mundo->base[item->b].habili, mundo->herois[item->h].habili);
    cjto_destroi(mundo->base[item->b].habili);
    mundo->base[item->b].habili = aux;

    for(int i = 0; i < mundo->Nherois; ++i){

        if(cjto_pertence(mundo->base[item->b].presentes, i)){

            aux = cjto_uniao(mundo->herois[i].habili, 
                                mundo->base[item->b].habili);
            cjto_destroi(mundo->base[item->b].habili);
            mundo->base[item->b].habili = aux;
        }
    }

    struct evento2 *e;
    if (!(e = malloc(sizeof(struct evento2))))
        return;

    e->b = item->b;

    printf("%6d: MORRE  HEROI %2d MISSAO %d\n", mundo->relogio, item->h,
        item->m);

    fprio_insere(mundo->lista, e, 3, mundo->relogio);
}

void missao(struct mundo *mundo, struct evento3 *item){

    mundo->missao[item->m].tent++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", mundo->relogio,
            item->m, mundo->missao[item->m].tent);
    cjto_imprime(mundo->missao[item->m].habili);
    printf(" ]\n");

    int x1, x2, y1, y2;
    int dist;

    x1 = mundo->missao[item->m].local.x;
    y1 = mundo->missao[item->m].local.y;

    int menorDist, id;
    int tentativa = 0;

    for(int i = 0; i < mundo->Nbase; ++i){

        x2 = mundo->base[i].local.x;
        y2 = mundo->base[i].local.y;

        dist = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
        dist = sqrt(dist);

        /*
        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", mundo->relogio,
                item->m, i, dist);
        cjto_imprime(mundo->base[i].presentes);
        printf(" ]\n");

        for (int j = 0; j < mundo->Nherois; ++j){

            if(cjto_pertence(mundo->base[i].presentes, j)){
            
                printf("%6d: MISSAO %d HAB HEROI %2d: [ ", mundo->relogio,
                        item->m, j);
                cjto_imprime(mundo->herois[j].habili);
                printf(" ]\n");
            
            }
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", mundo->relogio,
                item->m, i);
        cjto_imprime(mundo->base[i].habili);
        printf(" ]\n");
        */

        if(cjto_contem(mundo->base[i].habili, mundo->missao[item->m].habili)){

            if(tentativa == 0 || dist < menorDist){
                menorDist = dist;
                id = i;
            }
            tentativa++;
        }
        

    }

    int risco;

    if(tentativa){

        mundo->missao[item->m].cumprida = 1;
        mundo->base[id].missaos++;

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", mundo->relogio,
                item->m, id);
        cjto_imprime(mundo->base[id].habili);
        printf(" ]\n");

        for(int i = 0; i < mundo->Nherois; ++i){

            if(cjto_pertence(mundo->base[id].presentes, i)){

                risco = mundo->missao[item->m].perigo / (mundo->herois[i].paci
                        + mundo->herois[i].xp + 1.0);

                if(risco > rand()%31){

                    struct evento4 *e;
                    if(!(e = malloc(sizeof(struct evento4))))
                        return;
                    
                    e->h = i;
                    e->b = id;
                    e->m = item->m;

                    fprio_insere(mundo->lista, e, 8, mundo->relogio);
                
                } else {
                    mundo->herois[i].xp++;
                }
            }
        }

    } else {

        printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->relogio, item->m);

        struct evento3 *e;
        if(!(e = malloc(sizeof(struct evento3))))
            return;

        e->m = item->m;

        fprio_insere(mundo->lista, e, 7, mundo->relogio + (24*60));
    }

}

void fim(struct mundo *mundo){

    printf("%6d: FIM\n", mundo->relogio);

    int morto = 0; 
    int vivo = 0;

    for(int i = 0; i < mundo->Nherois; ++i){

        printf("HEROI %2d ", i);

        if(mundo->herois[i].vivo){
            printf("VIVO ");
            vivo++;
        } else { 
            printf("MORTO "); 
            morto++;
        }
        printf("PAC %3d VEL %4d EXP %4d HABS [ ", mundo->herois[i].paci, 
                mundo->herois[i].vel, mundo->herois[i].xp);
        cjto_imprime(mundo->herois[i].habili);
        printf(" ]\n");
    }

    for(int i = 0; i < mundo->Nbase; ++i){

        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", i, 
                mundo->base[i].lotacao, mundo->base[i].fimaMax,
                mundo->base[i].missaos);
    }

    printf("EVENTOS TRATADOS: %d\n", mundo->eventos);

    int cumprida = 0;
    int min, max;

    for(int i = 0; i < mundo->Nmissao; ++i){

        if (mundo->missao[i].cumprida)
            cumprida++;

        if(i == 0 || min > mundo->missao[i].tent)
            min = mundo->missao[i].tent;
        
        if(i == 0 || max < mundo->missao[i].tent)
            max = mundo->missao[i].tent;
    }

    double divi;
    
    divi = (double)cumprida/mundo->Nmissao;
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", cumprida, mundo->Nmissao,
            divi*100);

    divi = (min + max)/2.;
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min, max,
            divi);

    divi = (double)morto/mundo->Nherois;
    printf("TAXA MORTALIDADE: %.1f%%\n", divi*100);
}