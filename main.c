#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

void imprimirCola(TNodo n){

    if(n->hijo_izquierdo != POS_NULA) imprimirCola(n->hijo_izquierdo);
    else printf("[NULO-");
    printf("(%d,%s)",*((int*)n->entrada->clave),(char*)n->entrada->valor);
    if(n->hijo_derecho != POS_NULA) imprimirCola(n->hijo_derecho);
    else printf("-NULO]");

}

int comp_de_enteros(TEntrada e1, TEntrada e2){

    int c1 = *((int*) e1->clave);
    int c2 = *((int*) e2->clave);

    if(c1 < c2) return -1;
    if(c1 > c2) return 1;
    else return 0;

}

void liberar(TEntrada e){
   // printf("Entrada clave: %d valor: %s \n",*((int*)e -> clave),(char*)e-> valor );
    free(e);
}

int main(int nro, char** argc)
{
    printf("Creamos una entrada 3 'neko' \n");
    TEntrada entrada3 = (TEntrada) malloc(sizeof(struct entrada));
    int* clave1 = (int*) malloc(sizeof(int));
    *clave1 = 3;

    entrada3 -> clave = clave1;
    char pal1[5] = "neko";
    entrada3 -> valor = &pal1;

    printf("Entrada clave: %d valor: %s \n",*((int*)entrada3 -> clave),(char*)entrada3 -> valor );

    printf("Creamos una entrada 1 'hola' \n");
    TEntrada entrada1 = (TEntrada) malloc(sizeof(struct entrada));
    int clave2 = 1;
    entrada1 -> clave = &clave2;
    char pal2[5] = "hola";
    entrada1 -> valor = &pal2;

    printf("Entrada clave: %d valor: %s \n",*((int*)entrada1 -> clave),(char*)entrada1 -> valor );
//printf("Entrada clave: %d valor: %s \n",*((int*)entrada3 -> clave),(char*)entrada3 -> valor );

    printf("Creamos una entrada 2 'soy' \n");
    TEntrada entrada2 = (TEntrada) malloc(sizeof(struct entrada));
    int clave3 = 2;
    entrada2 -> clave = &clave3;
    char pal3[5] = "soy";
    entrada2 -> valor = &pal3;

    printf("Entrada clave: %d valor: %s \n",*((int*)entrada2 -> clave),(char*)entrada2 -> valor );


    printf("Comparamos entrada 3 con 2 y nos da %d \n",comp_de_enteros(entrada3,entrada2));

    printf("Creamos la cola\n");

    TColaCP cola = crear_cola_cp(comp_de_enteros);

    printf("la cola tiene %d elementos \n", cola->cantidad_elementos);

    printf("LE agregamos la entrada 3");

    int se_pudo = cp_insertar( cola, entrada3);

    if(se_pudo) printf("Se pudo insertar entrada, ahora %d elementos", cola->cantidad_elementos);

    printf("\n La cola: ");
    imprimirCola(cola->raiz);
    printf("\n");

    se_pudo = cp_insertar( cola, entrada1);


//    TEntrada entradahijoI = cola->raiz->hijo_izquierdo->entrada;
//    //TEntrada entradahijoD = cola->raiz->hijo_derecho->entrada;
//    printf("ENTRADA HIJO I (%d , %s ) ",*((int*)entradahijoI -> clave),(char*)entradahijoI -> valor);
//   // printf("ENTRADA HIJO D (%d , %s ) ",*((int*)entradahijoD -> clave),(char*)entradahijoD -> valor);

    if(se_pudo) printf("Se pudo insertar entrada, ahora %d elementos", cola->cantidad_elementos);



    printf("\n La cola: ");
    imprimirCola(cola->raiz);
    printf("\n");

    se_pudo = cp_insertar( cola, entrada2);




    if(se_pudo) printf("Se pudo insertar entrada, ahora %d elementos", cola->cantidad_elementos);

    printf("\n La cola: ");
    imprimirCola(cola->raiz);
    printf("\n");

/*    TEntrada entradahijoI = cola->raiz->hijo_izquierdo->entrada;
    TEntrada entradahijoD = cola->raiz->hijo_derecho->entrada;
    printf("ENTRADA HIJO I (%d , %s ) ",*((int*)entradahijoI -> clave),(char*)entradahijoI -> valor);
    printf("ENTRADA HIJO D (%d , %s ) ",*((int*)entradahijoD -> clave),(char*)entradahijoD -> valor);
   */
    TEntrada e1 = cp_eliminar(cola);

    printf("Se saca de la cola (%d , %s ) y queda con %d elementos ",*((int*)e1 -> clave),(char*)e1 -> valor,cola->cantidad_elementos);
printf("\n La cola: ");
    imprimirCola(cola->raiz);
    printf("\n");
   cp_destruir(cola, liberar);



    return 0;
}
