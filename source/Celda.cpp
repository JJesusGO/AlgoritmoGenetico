#include "Celda.h"

/*ESQUEMAS DISPONIBLES PARA DIBUJAR CADA CELDA*/
char Celda::esquema[] = {219,' ','I','F'};

/*CONTRUCTOR DE LA CELDA*/
Celda::Celda(){
    this->x = 0;
    this->y = 0;
    tipo = CELDA_ESPACIO;
}
/*INCIAR LA POSICION DE LA CELDA EN EL LABERINTO*/
void Celda::SetPosicion(int x,int y){
    this->x = x;
    this->y = y;
}
/*COLOCAR EL TIPO DE CELDA*/
void Celda::SetTipo(int tipo){
    this->tipo = tipo;
}
/*COLOCAR EL ESQUEMA CON EL QUE SE REPRESENATARA CADA CELDA EN CONSOLA*/
void Celda::SetEsquema(int index,char caracter){
    esquema[index] =  caracter;
}

