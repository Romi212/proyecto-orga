#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"
#include <string.h>

typedef struct ciudad {
char * nombre;
float pos_x;
float pos_y;
} * TCiudad;

//Funcion free para las entradas
void eliminarEntrada(TEntrada e){
    free(e->valor);
    free(e->clave);
    free(e);
}

void imprimirCiudad(TCiudad c){
    char* pl = c->nombre;
    int i = 0;

    printf("\n \n Nombre: ");
    while(pl[i] != '\0'){
        printf("%c",pl[i]);
        i++;

    }
    printf(" en pos(%f, %f) \n",c->pos_x,c->pos_y);
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

        printf("\n %d ",num);
        imprimirCiudad(nOrigen);
        num++;

         printf("\n %d",c);
        while(cp_cantidad(cola)>0){
             printf("\n ADENTROOO %d",c);
            TEntrada eliminada = cp_eliminar(cola);

            TCiudad nuevaC = (TCiudad)(eliminada->valor);
            printf("%d",cp_cantidad(cola));
            float dis = distanciaManhattan(nOrigen,nuevaC);

            TEntrada agregar = (TEntrada) malloc(sizeof(struct entrada));

            float* clav = (float*)malloc(sizeof(float));

            *clav = dis;

            agregar->clave=clav;

            agregar->valor = nuevaC;

            cp_insertar(colaNueva,agregar);
           printf("\n HOLA ESTA ES LA ITERACION NUM: %d",c);
        }
        aux = cola;
        cola = colaNueva;
        colaNueva = aux;

         printf("\n CANTIDAD ELEMENTOS EN COLA %d",cp_cantidad(cola));
         printf(" \n CANTIDAD ELEMENTOS EN COLANUEVA %d",cp_cantidad(colaNueva));
         printf(" \n CANTIDAD ELEMENTOS EN AUX %d",cp_cantidad(aux));

        c++;


    }
   // printf("ELEMENTOSSS: %d",cp_cantidad(cola));

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

        printf("\n %d ",num);
        imprimirCiudad((TCiudad)(e->valor));
        num++;
    }

    printf("Total recorrido: %f",distancia);

   cp_destruir(cola,eliminarEntrada);
    //cp_destruir(colaNueva,eliminarEntrada);
    //cp_destruir(aux,eliminarEntrada);*/


}



int main(int cantA, char** args){

    printf("Leemos el archivo:");
    TCiudad ciudades [5];
    FILE * archivo = fopen("viajes.txt","r");
    //TCiudad[100] ciudades;
    char linea[100];
    char palabra[50];
    fgets(linea, 100,archivo);

    TCiudad origen = (TCiudad)malloc(sizeof(struct ciudad));
    if(origen != POS_NULA) {
        char or[10]= "origen";
        origen->nombre = or;
        origen->pos_x = linea[0]-'0';
        origen-> pos_y =  linea[2]-'0' ;
    }
    printf("Leemos origen en %d %d", linea[0],linea[2]);
    ciudades[0] = origen;


    int i = 0;
    while (fgets(linea, 100,archivo)){
            printf("Leemos c1 en %d %d", linea[0],linea[2]);
        i++;
        TCiudad c1 = (TCiudad)malloc(sizeof(struct ciudad));
    if(c1 != POS_NULA) {
         char letra = linea[0];
         int j = 0;
          //palabra="pru";
        while(letra != ';'){
            palabra[j] = letra;
            printf("%c",letra);
            j++;
             letra = linea[j];
        }
        palabra[j] = '\0';
        printf("\n");

        char * name = (char*)malloc(sizeof(palabra));
        c1->nombre = name;
        strcpy(c1->nombre,palabra);
       //  c1->nombre = prueba;
         printf("%s",palabra);
        c1->pos_x = linea[j+1]- '0';
        c1-> pos_y = linea[j+3] -'0';
        ciudades[i] = c1;
    }
    }



    //int cant = leerArchivo(ciudades, args[1]);
    int cant = i;
    for(int i = 0; i<cant+1; i++){
        TCiudad c = ciudades[i];
        imprimirCiudad(c);

    }


    printf("Elija una opcion del menu (su numero): \n");
    int opcion=0;
    //while(opcion!=4){



      printf("1: Mostrar ascendente \n 2: Mostrar descendente \n 3: Reducir horas de manejo \n 4: Salir \n");
      scanf("%d",&opcion);
      switch(opcion){
        case 1: {mostrarOrdenado(ciudades, cant, ordenarAsc); break;}
        case 2: {mostrarOrdenado(ciudades, cant, ordenarDes);break;}
        case 3: {reducirHorasManejo(ciudades, cant, ordenarAsc);break;}
        case 4: {printf("\n Se cierra el programa");break;}
        default: {printf("\n Opcion invalida \n");break;}
      }
    //}

    printf(" \n CANTIDAD %d",cant);
    /*for(int i = 0; i<cant+1; i++){
        TCiudad c = ciudades[i];
        if(i!=0)free(c->nombre);
        free(c);

    }*/
    return 0;
}
