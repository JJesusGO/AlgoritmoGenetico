#include "Celda.h"

char Celda::esquema[] = {219,' ','I','F'};

Celda::Celda(){
    this->x = 0;
    this->y = 0;
    tipo = CELDA_ESPACIO;
}
void Celda::SetPosicion(int x,int y){
    this->x = x;
    this->y = y;
}
void Celda::SetTipo(int tipo){
    this->tipo = tipo;
}
void Celda::SetEsquema(int index,char caracter){
    esquema[index] =  caracter;
}

