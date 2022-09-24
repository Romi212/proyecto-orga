#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

typedef struct ciudad {
char * nombre;
float pos_x;
float pos_y;
} * TCiudad;

void mostrarAscendente(){
    printf("HOLAA");
}
void mostrarDescendente(){
    printf("WIUWIUWIUW");
}
void reducirHorasManejo(){
    printf("AGUANTE C DIJO NUNCA NADIE");
}


int main(int cantA, char** args){
    printf("Elija una opcion del menu (su numero): \n");
    int opcion=0;
    //while(opcion!=4){
      printf("1: Mostrar ascendente \n 2: Mostrar descendente \n 3: Reducir horas de manejo \n 4: Salir \n");
      scanf("%d",&opcion);
      switch(opcion){
        case 1: {mostrarAscendente(); break;}
        case 2: {mostrarDescendente();break;}
        case 3: {reducirHorasManejo();break;}
        case 4: {printf("\n Se cierra el programa");break;}
        default: {printf("\n Opcion invalida \n");break;}
      }
    //}

    return 0;
}
