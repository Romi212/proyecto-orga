#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"
#include <string.h>

const int MAX_LEN = 100;
const int MAX_CIUDADES = 5;

typedef struct ciudad {
char * nombre;
float pos_x;
float pos_y;
} * TCiudad;


TCiudad leerCiudad(char* linea){
     TCiudad c1 = (TCiudad)malloc(sizeof(struct ciudad));
     if(c1 != POS_NULA) {
        char palabra[MAX_LEN];
        //Copiamos el nombre de la ciudad a una var local
        char letra = linea[0];
        int j = 0;
        while(letra != ';'){
            palabra[j] = letra;

            j++;
             letra = linea[j];
        }
        palabra[j] = '\0';

        //Reservamos espacio en heap para guardar el nombre
        char * name = (char*)malloc(strlen(palabra)*sizeof(char));
        c1->nombre = name;
        strcpy(c1->nombre,palabra);


        //LEEMOS LAS POS
        j++;
        letra = linea[j];
        int i = 0;
        //Leemos la posX

        char  posX[MAX_LEN/2];
        while(letra!= ';'){
            posX[i] = letra;
            i++;
            j++;
            letra = linea[j];
        }
        posX[i] = '\0';
        j++;
        letra = linea[j];
        //Leemos la pos y
        char posY[MAX_LEN/2];
        i = 0;
        while(letra!= '\0'){
           posY[i] = letra;
           i++;
           j++;
           letra = linea[j];
        }
        c1->pos_x = atof(posX);
        c1->pos_y = atof(posY);
        }

}

//Funcion free para las entradas
void eliminarEntrada(TEntrada e){
    free(e->valor);
    free(e->clave);
    free(e);
}

void imprimirCiudad(TCiudad c){
    char* pl = c->nombre;
    int i = 0;
    while(pl[i] != '\0'){
        printf("%c",pl[i]);
        i++;

    }
    printf(".");
    //printf(" en pos(%f, %f) \n",c->pos_x,c->pos_y);
}

//Funcion comparador para ordenar ascendentemente
int ordenarAsc(TEntrada e1, TEntrada e2){
    float c1 = *((float*)e1->clave);
    float c2 = *((float*)e2->clave);
    if(c1<c2) return -1;
    if(c1 == c2) return 0;
    else return 1;

}

//Funcion comparador para ordenar descendentemente
int ordenarDes(TEntrada e1, TEntrada e2){
    float c1 = *((float*)e1->clave);
    float c2 = *((float*)e2->clave);
    if(c1<c2) return 1;
    if(c1 == c2) return 0;
    else return -1;

}

//Funcion que computa la distancia entre ciudades
float distanciaManhattan(TCiudad c1, TCiudad c2){
    float resultado=0;
    resultado = abs((c1->pos_x)-(c2->pos_x)) + abs((c1->pos_y)-(c2->pos_y));
    return resultado;
}


//Procedimiento para mostrar ascendente o descendentemente el listado de ciudades segun el comparador que le pasen
void mostrarOrdenado(TCiudad ciudades [], int cant, int (*orden)(TEntrada, TEntrada)){


    TColaCP cola = crear_cola_cp(orden);

    for(int i = 1; i<= cant; i++){
        TCiudad c = ciudades[i];
        float distancia = distanciaManhattan(ciudades[0], c);
        TEntrada e = (TEntrada) malloc(sizeof(struct entrada));
        float* clave1 = (float*) malloc(sizeof(float));
        *clave1 = distancia;
        e->clave = clave1;
        e->valor = c;
        cp_insertar(cola,e);
    }
    int i = 1;
    while(cp_cantidad(cola)>0){
        TEntrada e = cp_eliminar(cola);
        printf("%d . ",i);
        imprimirCiudad((TCiudad)e->valor);
        printf("\n");
        i++;
    }
    cp_destruir(cola, eliminarEntrada);
}


//Procedimiento que muestra el listado de ciudades segun la reduccion de horas de manejo
void reducirHorasManejo(TCiudad ciudades[], int cant, int (*orden)(TEntrada, TEntrada)){
    float distancia = 0;
    int c = 1;
    int num = 1;

    TColaCP cola = crear_cola_cp(orden);
    for(int i = 1; i<= cant; i++){
        TCiudad c = ciudades[i];
        float distancia = distanciaManhattan(ciudades[0], c);
        TEntrada e = (TEntrada) malloc(sizeof(struct entrada));
        float* clave1 = (float*) malloc(sizeof(float));
        *clave1 = distancia;
        e->clave = clave1;
        e->valor = c;
        cp_insertar(cola,e);
    }

    TColaCP colaNueva = crear_cola_cp(orden);
    TColaCP aux = crear_cola_cp(orden);

    while(c<cant-1){
        TEntrada e = cp_eliminar(cola);
        distancia+=*(float*)(e->clave);
        TCiudad nOrigen = (TCiudad)(e->valor);

        printf("%d . ",num);
        imprimirCiudad(nOrigen);
        printf("\n");
        num++;


        while(cp_cantidad(cola)>0){

            TEntrada eliminada = cp_eliminar(cola);

            TCiudad nuevaC = (TCiudad)(eliminada->valor);

            float dis = distanciaManhattan(nOrigen,nuevaC);

            TEntrada agregar = (TEntrada) malloc(sizeof(struct entrada));

            float* clav = (float*)malloc(sizeof(float));

            *clav = dis;

            agregar->clave=clav;

            agregar->valor = nuevaC;

            cp_insertar(colaNueva,agregar);

        }
        aux = cola;
        cola = colaNueva;
        colaNueva = aux;

        c++;


    }


    while(cp_cantidad(cola)>0){
        TEntrada e = cp_eliminar(cola);
        TCiudad anteU;
       if(cp_cantidad(cola)!=0){
            distancia+=*(float*)(e->clave);
            anteU = (TCiudad)(e->valor);
       }
       else{
            distancia+=distanciaManhattan((TCiudad)(e->valor),anteU);
       }
        printf("%d . ",num);
        imprimirCiudad((TCiudad)(e->valor));
        printf("\n");
        num++;
    }

    printf("Total recorrido: %.2f",distancia);
    printf("\n");

   cp_destruir(cola,eliminarEntrada);
    //cp_destruir(colaNueva,eliminarEntrada);
    //cp_destruir(aux,eliminarEntrada);*/


}



int main(int cantA, char** args){


    TCiudad ciudades [MAX_CIUDADES];
    FILE * archivo = fopen(args[1],"r");

    //LEEMOS EL ARCHIVO POR LINEA
    char linea[MAX_LEN];
    char palabra[50];
    fgets(linea, MAX_LEN,archivo);

    //la primer linea corresponde a la posicion del origen
    TCiudad origen = (TCiudad)malloc(sizeof(struct ciudad));
    if(origen != POS_NULA) { //si se pudo crear espacio en memoria

        char or[10]= "origen";
        origen->nombre = or;

        //Leemos la posicion en X
        int i = 0;
        char posX[MAX_LEN/2];
        while(linea[i]!= ';'){
            posX[i] = linea[i];
            i++;
        }
        posX[i] = '\0';
        i++;

        //Leemos la posicion en Y
        char posY[MAX_LEN/2];
        int j = 0;
        while(linea[i]!= '\0'){
           posY[j] = linea[i];
           i++;
           j++;
        }

        origen->pos_x = atof(posX);
        origen->pos_y = atof(posY);
    }

    ciudades[0] = origen;

    //Empezamos a leer las ciudades
    int cantCiudades = 0;
    while (fgets(linea, 100,archivo)){

     cantCiudades++;
     TCiudad c1 = leerCiudad(linea);

        ciudades[cantCiudades] = c1;
     }





   int cant = cantCiudades;

    int opcion=0;
    while(opcion!=4){
       // TCola ciudades = leerArchivo();
      printf("\n Elija una opcion del menu (su numero): \n");
      printf("\n 1: Mostrar ascendente \n 2: Mostrar descendente \n 3: Reducir horas de manejo \n 4: Salir \n");
      scanf("%d",&opcion);
      switch(opcion){
        case 1: {printf("\n Mostrar ascendente \n"); mostrarOrdenado(ciudades, cant, ordenarAsc); break;}
        case 2: {printf("\n Mostrar descendente \n");mostrarOrdenado(ciudades, cant, ordenarDes);break;}
        case 3: {printf("\n Reducir horas de manejo \n");reducirHorasManejo(ciudades, cant, ordenarAsc);break;}
        case 4: {printf("\n Se cierra el programa");break;}
        default: {printf("\n Opcion invalida \n");break;}
      }
    }

    for(int i = 0; i<cant+1; i++){
        TCiudad c = ciudades[i];
        if(i!=0)free(c->nombre);
        free(c);

    }
    return 0;
}
