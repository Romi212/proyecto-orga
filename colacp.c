#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"


TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    cola->comparador=f;
    cola->cantidad_elementos=0;
    cola->raiz = ELE_NULO;
    return cola;
}

int cp_insertar(TColaCP cola, TEntrada entr);

TEntrada cp_eliminar(TColaCP cola);

int cp_cantidad(TColaCP cola){
    return cola->cantidad_elementos;
}


static void eliminarRec(struct nodo* n,void (*fEliminar)(TEntrada)){
    if((n->hijo_izquierdo)!= POS_NULA) eliminarRec(n->hijo_derecho,fEliminar);
    if((n->hijo_derecho)!= POS_NULA) eliminarRec(n->hijo_derecho,fEliminar);
   fEliminar(n->entrada);
   free(n);
}


void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)){
    if(cola->cantidad_elementos == 0) exit(CCP_NO_INI);
    TNodo nodo = cola-> raiz;
    eliminarRec(nodo,fEliminar);
    free(cola);

}
