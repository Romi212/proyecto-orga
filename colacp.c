#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"


TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    if( cola == POS_NULA) exit(MEMO_ERR);
    cola->comparador=f;
    cola->cantidad_elementos=0;
    cola->raiz = ELE_NULO;
    return cola;
}

int cp_insertar(TColaCP cola, TEntrada entr){
 //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);
   // int altura = getAltura(cola->cantidad_elementos);
    return 0;
    }

TEntrada cp_eliminar(TColaCP cola){
 //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);
    return NULL;
}

int cp_cantidad(TColaCP cola){
     //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);
    return cola->cantidad_elementos;
}

//Método auxiliar para eliminar todos los nodos descendientes del nodo recivido
static void eliminarRec(struct nodo* n,void (*fEliminar)(TEntrada)){
    if((n->hijo_izquierdo)!= POS_NULA) eliminarRec(n->hijo_derecho,fEliminar);
    if((n->hijo_derecho)!= POS_NULA) eliminarRec(n->hijo_derecho,fEliminar);
   fEliminar(n->entrada);
   free(n);
}


void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)){
    //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);

    //Si la cola tiene elementos se elimina cada uno de forma recursiva
    if(cola->raiz != ELE_NULO){
        TNodo nodo = cola-> raiz;
        eliminarRec(nodo,fEliminar);
    }

    free(cola);

}
