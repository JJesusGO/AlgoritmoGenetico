#include "Entidad.h"

Entidad::Entidad(Laberinto *laberinto){
    this->laberinto = laberinto;
    Reiniciar();
}
void Entidad::Reiniciar(){
    this->x = laberinto->GetInicio().GetX();
    this->y = laberinto->GetInicio().GetY();
}
void Entidad::MostrarLaberinto(){
    this->laberinto->MostrarLaberinto(x,y,'X');
}
void Entidad::NextMovimiento(){
    float probabilidades[] = {0.25f,0.25f,0.25f,0.25f};
    Probabilidad p(probabilidades,4);

    int movimiento = p.Next();
    if(movimiento == 0)
        y--;
    else if(movimiento == 1)
        x++;
    else if(movimiento == 2)
        y++;
    else
        x--;

}




