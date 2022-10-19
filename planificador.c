#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"
#include <string.h>

const int MAX_LEN = 100;



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
    return c1;
}

void eliminarCiudad(TCiudad c){
    free(c->nombre);
    free(c);
}

//Funcion free para las entradas
void eliminarEntrada(TEntrada e){

    eliminarCiudad((TCiudad) e->valor);
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
void mostrarOrdenado( char* file_p, int (*orden)(TEntrada, TEntrada)){


    TColaCP cola = crear_cola_cp(orden);

    FILE * archivo = fopen(file_p,"r");

    //LEEMOS EL ARCHIVO POR LINEA
    char linea[MAX_LEN];
    char palabra[50];
    fgets(linea, MAX_LEN,archivo);

    float origen_x;
    float origen_y;

    char letra = linea[0];
    int i = 0;
    while(letra != ';'){
        palabra[i] = letra;
        letra = linea[++i];
    }
    palabra[i] = '\0';
    origen_x = atof(palabra);
    int j = 0;
    i++;
    letra = linea[i];
    while(letra!= '\0'){
        palabra[j++] = letra;
        letra = linea[++i];
    }
    palabra[j] = '\0';
    origen_y = atof(palabra);

    TCiudad origen = (TCiudad)malloc(sizeof(struct ciudad));
    if(origen != POS_NULA){
        origen->nombre = NULL;
        origen->pos_x = origen_x;
        origen->pos_y = origen_y;
    }


    while(fgets(linea, MAX_LEN,archivo)){
        TCiudad c = leerCiudad(linea);
        float distancia = distanciaManhattan(origen, c);
        TEntrada e = (TEntrada) malloc(sizeof(struct entrada));
        float* clave1 = (float*) malloc(sizeof(float));
        *clave1 = distancia;
        e->clave = clave1;
        e->valor = c;
        cp_insertar(cola,e);
    }
     i = 1;
    while(cp_cantidad(cola)>0){
        TEntrada e = cp_eliminar(cola);
        printf("%d . ",i);
        TCiudad ciudad = (TCiudad)e->valor;
        imprimirCiudad(ciudad);
        eliminarEntrada(e);
        printf("\n");
        i++;
    }
    cp_destruir(cola, eliminarEntrada);
}


//Procedimiento que muestra el listado de ciudades segun la reduccion de horas de manejo
void reducirHorasManejo(char* file_p){
    float distancia = 0;
    int c = 1;
    int num = 1;

    TColaCP cola = crear_cola_cp(ordenarAsc);

    FILE * archivo = fopen(file_p,"r");

    //LEEMOS EL ARCHIVO POR LINEA
    char linea[MAX_LEN];
    char palabra[50];
    fgets(linea, MAX_LEN,archivo);

    float origen_x;
    float origen_y;

    char letra = linea[0];
    int i = 0;
    while(letra != ';'){
        palabra[i] = letra;
        letra = linea[++i];
    }
    palabra[i] = '\0';
    origen_x = atof(palabra);
    int j = 0;
    i++;
    letra = linea[i];
    while(letra!= '\0'){
        palabra[j++] = letra;
        letra = linea[++i];
    }
    palabra[j] = '\0';
    origen_y = atof(palabra);

    //guardamos origen como una ciudad
    TCiudad origen = (TCiudad)malloc(sizeof(struct ciudad));
    if(origen != POS_NULA){
        origen->nombre = NULL;
        origen->pos_x = origen_x;
        origen->pos_y = origen_y;
    }

    //Leemos todas las ciudades y las guardamos en una cola de forma desc
    while(fgets(linea, MAX_LEN,archivo)){
        TCiudad c = leerCiudad(linea);
        float distancia = distanciaManhattan(origen, c);
        TEntrada e = (TEntrada) malloc(sizeof(struct entrada));
        float* clave1 = (float*) malloc(sizeof(float));
        *clave1 = distancia;
        e->clave = clave1;
        e->valor = c;
        cp_insertar(cola,e);
    }
    //cerramos el archivo
    fclose(archivo);

    TColaCP colaNueva = crear_cola_cp(ordenarAsc);
    TColaCP aux ;
    int cant = (cola->cantidad_elementos);
    while(c<cant-1){
        //Agarra la ciudad mas cercana
        TEntrada e = cp_eliminar(cola);
        //Suma la distancia desde origen a esta ciudad
        distancia+=*(float*)(e->clave);
        //Cambia el origen a esta
        TCiudad nOrigen = (TCiudad)(e->valor);
        //Libera la entrada (manteniendo la ciudad)
        free(e->clave);
        free(e);

        //Imprime la ciudad que  visito
        printf("%d . ",num);
        imprimirCiudad(nOrigen);
        printf("\n");
        num++;

        //Guarda el resto en otra cola calculando las distancias desde pos actual
        while(cp_cantidad(cola)>0){

            TEntrada eliminada = cp_eliminar(cola);

            TCiudad nuevaC = (TCiudad)(eliminada->valor);

            float dis = distanciaManhattan(nOrigen,nuevaC);

            *((float*)eliminada->clave) = dis;

            cp_insertar(colaNueva,eliminada);

        }
        aux = cola;
        cola = colaNueva;
        colaNueva = aux;

        c++;

        eliminarCiudad(nOrigen);


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
        eliminarEntrada(e);
    }

    printf("Total recorrido: %.2f",distancia);
    printf("\n");

   cp_destruir(cola,eliminarEntrada);
    cp_destruir(colaNueva,eliminarEntrada);



}



int main(int cantA, char** args){




    int opcion=0;
    while(opcion!=4){

      printf("\n Elija una opcion del menu (su numero): \n");
      printf("\n 1: Mostrar ascendente \n 2: Mostrar descendente \n 3: Reducir horas de manejo \n 4: Salir \n");
      scanf("%d",&opcion);
      switch(opcion){
        case 1: {printf("\n Mostrar ascendente \n"); mostrarOrdenado(args[1], ordenarAsc); break;}
        case 2: {printf("\n Mostrar descendente \n");mostrarOrdenado(args[1], ordenarDes);break;}
        case 3: {printf("\n Reducir horas de manejo \n");reducirHorasManejo(args[1] );break;}
        case 4: {printf("\n Se cierra el programa");break;}
        default: {printf("\n Opcion invalida \n");break;}
      }
    }


    return 0;
}
