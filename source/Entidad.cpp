#include "Entidad.h"

const int Entidad::plantillas[ENTIDAD_PLANTILLAS][4] = {
                                       {-1,-1,-1,-1},
                                       {1,0,0,0},
                                       {1,1,0,0},
                                       {1,0,0,1},
                                       {0,1,0,0},
                                       {0,0,0,1},
                                       {0,1,0,1},
                                       {1,1,0,1},
                                       {0,0,0,0}
                                    };

Entidad::Entidad(Laberinto *laberinto){
    this->laberinto = laberinto;
    Reiniciar();
}
void Entidad::Reiniciar(){
    this->x = laberinto->GetInicio().GetX();
    this->y = laberinto->GetInicio().GetY();
    direccion = ENTIDAD_INICIO;
    plantilla = 0;
    colision = false;
}
void Entidad::MostrarLaberinto(){
    printf("PLANTILLA: %d\nDIRECCION: %d\n\n",plantilla,direccion);
    if(colision)
        this->laberinto->MostrarLaberinto(x,y,'X');
    else
        this->laberinto->MostrarLaberinto(x,y,'O');
}
bool Entidad::NextMovimiento(){

    int px = x,
        py = y;
    plantilla  = 0;

    Celda celdas[4];
    switch(direccion){
        case ENTIDAD_INICIO:
            celdas[0] = laberinto->GetCelda(px,py-1);
            celdas[1] = laberinto->GetCelda(px+1,py);
            celdas[2] = laberinto->GetCelda(px,py+1);
            celdas[3] = laberinto->GetCelda(px-1,py);
        break;
        case ENTIDAD_ARRIBA:
            celdas[0] = laberinto->GetCelda(px,py-1);
            celdas[1] = laberinto->GetCelda(px+1,py);
            celdas[2] = laberinto->GetCelda(px,py+1);
            celdas[3] = laberinto->GetCelda(px-1,py);
        break;
        case ENTIDAD_DERECHA:
            celdas[0] = laberinto->GetCelda(px+1,py);
            celdas[1] = laberinto->GetCelda(px,py+1);
            celdas[2] = laberinto->GetCelda(px-1,py);
            celdas[3] = laberinto->GetCelda(px,py-1);
        break;
        case ENTIDAD_ABAJO:
            celdas[0] = laberinto->GetCelda(px,py+1);
            celdas[1] = laberinto->GetCelda(px-1,py);
            celdas[2] = laberinto->GetCelda(px,py-1);
            celdas[3] = laberinto->GetCelda(px+1,py);
        break;
        case ENTIDAD_IZQUIERDA:
            celdas[0] = laberinto->GetCelda(px-1,py);
            celdas[1] = laberinto->GetCelda(px,py-1);
            celdas[2] = laberinto->GetCelda(px+1,py);
            celdas[3] = laberinto->GetCelda(px,py+1);
        break;
    }

    if(!(direccion == ENTIDAD_INICIO)){
        int p[4] = {(int)celdas[0].IsColisionable(),
                    (int)celdas[1].IsColisionable(),
                    (int)celdas[2].IsColisionable(),
                    (int)celdas[3].IsColisionable()};
        for(int i=0;i<ENTIDAD_PLANTILLAS;i++){
            int condicion = 0;
            for(int j=0;j<4;j++)
                condicion += p[j] == plantillas[i][j];
            if(condicion == 4){
                plantilla = i;
                break;
            }
        }
    }

    float probabilidades[] = {0.25f,0.25f,0.25f,0.25f};
    Probabilidad p(probabilidades,4);

    int celda      = p.Next();
    int movimiento = ENTIDAD_INICIO;
    int dx = celdas[celda].GetX() - px,
        dy = celdas[celda].GetY() - py;

    if(dx > 0)
        movimiento = ENTIDAD_DERECHA;
    else if(dx < 0)
        movimiento = ENTIDAD_IZQUIERDA;
    else if(dy < 0)
        movimiento = ENTIDAD_ARRIBA;
    else if(dy > 0)
        movimiento = ENTIDAD_ABAJO;

    direccion = movimiento;

    if(movimiento      == ENTIDAD_ARRIBA)
        py--;
    else if(movimiento == ENTIDAD_DERECHA)
        px++;
    else if(movimiento == ENTIDAD_ABAJO)
        py++;
    else if(movimiento == ENTIDAD_IZQUIERDA)
        px--;

    if(laberinto->GetCelda(px,py).IsColisionable()){
        colision = true;
        return true;
    }

    x = px;
    y = py;

    colision = false;
    return false;

}




