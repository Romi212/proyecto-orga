#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"
#include <math.h>

//Dado la cantidad de elementos de un arbol devuelve la altura que tendria con un elemento mas
static int get_altura(int cant){
    int h = 0;
    int potencia_dos = 1;
    int falta = cant;

    while (falta>= potencia_dos){
        falta = falta - potencia_dos;
        potencia_dos = potencia_dos*2;
        h++;
    }
    return h;
}

//Dado una cola y el ultimo nodo insertado se encarga de ordenarlo para respetar el orden
static void bubble(TNodo nodo, TColaCP cola){
    if(nodo != cola->raiz){
            TNodo padre = (nodo->padre);
        if(cola->comparador(nodo->entrada, padre->entrada)<0){
                TEntrada aux = nodo -> entrada;
                nodo->entrada = padre-> entrada;
                padre->entrada = aux;
                bubble(padre, cola);
        }
    }
}

//Crea un nuevo nodo e inicializa sus atributos
static TNodo inicializar_nodo(){
        TNodo nuevo_nodo = (TNodo) malloc(sizeof(struct nodo));
        if(nuevo_nodo != POS_NULA){
            nuevo_nodo->padre = POS_NULA;
            nuevo_nodo->hijo_derecho = POS_NULA;
            nuevo_nodo->hijo_izquierdo = POS_NULA;
        }
        return nuevo_nodo;
}

//Dado la cantidad de nodos de la ultima fila del arbol como si estuviera completo y la posicion dentro de esta
//devuelve el padre a esa posicion
static TNodo get_padre(TColaCP cola, int cant_comp, int pos){
    TNodo nodo_act = cola->raiz;
    int cant_fila = cant_comp;
    int pos_en_fila = pos;
    while(cant_fila >2){
        if(pos_en_fila > (cant_fila/2)){
            nodo_act = nodo_act->hijo_derecho;
            pos_en_fila -= (cant_fila/2);
        }
        else nodo_act = nodo_act->hijo_izquierdo;
        cant_fila = cant_fila/2;
    }

    return nodo_act;
}

//Dado un padre se crea un nodo como su hijo derecho o izquierdo segun sea especificado
static TNodo crear_nuevo_nodo(TNodo padre, int esDer){

    TNodo nodo = inicializar_nodo();
    if(esDer) padre->hijo_derecho = nodo;
    else padre->hijo_izquierdo = nodo;
    nodo->padre = padre;
    return nodo;
}

//Devuelve el ultimo nodo del heap
static TNodo get_ultimo_nodo(TColaCP cola){
    //Se busca donde esta el ultimo nodo
    int altura = get_altura((cola->cantidad_elementos)-1);

    int fila_completa = pow(2,altura); //Cantidad que deber�a tener la ultima fila para ser un arbol completo
    //Se calcula la cantidad de nodos de la ultima fila
    int quedan = (cola->cantidad_elementos)- (fila_completa - 1 );
    int pos = quedan;
    //Se busca el padre del nodo
    TNodo padre = get_padre(cola,fila_completa,pos);

    TNodo nodo;
    if (pos % 2) {
            nodo = padre->hijo_izquierdo;
            padre->hijo_izquierdo = POS_NULA;
    }
    else {

            nodo = padre->hijo_derecho;

            padre-> hijo_derecho = POS_NULA;
    }
    return nodo;
}

//Dado una cola y la raiz se encarga de ordenarlo para respetar el orden
static void bubble_reverse(TColaCP cola, TNodo padre){
    if(padre->hijo_izquierdo != POS_NULA){

        int compareIzq = cola->comparador(padre->hijo_izquierdo->entrada,padre->entrada);
        int compareDer = 1;
        if(padre->hijo_derecho != POS_NULA){

            compareDer = cola->comparador(padre->hijo_derecho->entrada,padre->entrada);
        }
        if(compareIzq <0 || compareDer <0){

                TNodo cambiar;
            if((padre->hijo_derecho != POS_NULA) && cola->comparador(padre->hijo_derecho->entrada,padre->hijo_izquierdo->entrada)<0)
                cambiar = padre->hijo_derecho;
            else cambiar = padre->hijo_izquierdo;
            TEntrada aux = cambiar->entrada;
            cambiar->entrada = padre->entrada;
            padre->entrada = aux;
            bubble_reverse(cola,cambiar);
        }

    }
}

//M�todo auxiliar para eliminar todos los nodos descendientes del nodo recibido
static void eliminarRec(TNodo n,void (*fEliminar)(TEntrada)){

    if((n->hijo_izquierdo)!= POS_NULA) eliminarRec(n->hijo_izquierdo,fEliminar);
    if((n->hijo_derecho)!= POS_NULA) eliminarRec(n->hijo_derecho,fEliminar);
   fEliminar(n->entrada);
   free(n);
}


//-----TDA COLA CON PRIORIDAD-----

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    if( cola == POS_NULA) exit(MEMO_ERR);
    cola->comparador=f;
    cola->cantidad_elementos=0;
    cola->raiz = POS_NULA;
    return cola;
}

int cp_insertar(TColaCP cola, TEntrada entr){

 //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);
    int opExitosa = 1;
    //Si la cola no tiene elementos, se crea la raiz
    if(cola->raiz == POS_NULA){
        TNodo nuevo_nodo = inicializar_nodo();
        if(nuevo_nodo == POS_NULA) opExitosa = 0;
        cola->raiz = nuevo_nodo;

        nuevo_nodo->entrada = entr;


    }
    else{
        //Se busca la pos donde debe insertarse el nodo
        int altura = get_altura(cola->cantidad_elementos);
        int fila_completa = pow(2,altura); //Cantidad que deber�a tener la ultima fila para ser un arbol completo
        //Se calcula la cantidad de nodos de la ultima fila
        int quedan = (cola->cantidad_elementos)- (fila_completa - 1 );
        int pos = quedan+1;
        //Se busca el padre del nodo

        TNodo padre  = get_padre(cola,fila_completa, pos);
        //Se crea el nodo en su lugar
        TNodo nuevoNodo = crear_nuevo_nodo(padre, quedan %2);


        if (nuevoNodo == POS_NULA) opExitosa = 0;
        else {
            nuevoNodo->entrada = entr;
            //Se acomoda para respetar el orden
            bubble(nuevoNodo, cola);
        }
    }
    if(opExitosa) cola->cantidad_elementos++;
    return opExitosa;
    }

TEntrada cp_eliminar(TColaCP cola){
 //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);

    if(cola->raiz == POS_NULA) return ELE_NULO;

    //Sacar la raiz y guardar la entrada
    TEntrada entrada_min = (cola->raiz)->entrada;

    if(cola->cantidad_elementos>1){

    // Poner la ultima entrada en la raiz
    TNodo ultimo_nodo = get_ultimo_nodo(cola);

    cola->raiz->entrada = ultimo_nodo->entrada;

    free(ultimo_nodo);
    cola->cantidad_elementos--;


    //Bubble hacia abajo

    bubble_reverse(cola, cola->raiz);


    }
    else{

        cola->cantidad_elementos = 0;
        free(cola->raiz);
        cola ->raiz = POS_NULA;


    }
    return entrada_min;
}

int cp_cantidad(TColaCP cola){
     //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);
    return cola->cantidad_elementos;
}

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)){
    //Si se recibe un puntero a nulo no se puede realizar la operacion
    if(cola == POS_NULA) exit(CCP_NO_INI);

    //Si la cola tiene elementos se elimina cada uno de forma recursiva
    if(cola->raiz != POS_NULA){
        TNodo nodo = cola-> raiz;
        eliminarRec(nodo,fEliminar);
    }

    free(cola);

}
