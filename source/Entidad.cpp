#include "Entidad.h"

/*PLANTILLAS PARA EL FUNCIONAMIENTO DE LA ENTIDAD*/
const int Entidad::plantillas[ENTIDAD_PLANTILLAS][ENTIDAD_CELDAS] = {
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

/*CONTRUCTOR DE LA ENTIDAD*/
Entidad::Entidad(Laberinto *laberinto,Individuo *individuo){
    this->laberinto = laberinto;
    this->individuo = individuo;
    this->celdas = new bool*[laberinto->GetN()];
    for(int i=0;i<laberinto->GetN();i++)
        this->celdas[i] = new bool[laberinto->GetM()];
    Reiniciar();
}
/*DESSSTRUCTOR DE LA ENTIDAD*/
Entidad::~Entidad(){
    for(int i=0;i<laberinto->GetN();i++)
        delete[] celdas[i];
    delete[] celdas;
}

/*REINICIAR A VALORES PREESTABLECIDOS LA ENTIDAD EN BASE AL LABERINTO*/
void Entidad::Reiniciar(){
    x = laberinto->GetInicio().GetX();
    y = laberinto->GetInicio().GetY();
    direccion = ENTIDAD_INICIO;
    plantilla = 0;
    colision = false;
    termino  = false;
    pasos = 0;
    puntuacion = 0;

    for(int i=0;i<laberinto->GetN();i++)
        for(int j=0;j<laberinto->GetM();j++)
            celdas[i][j] = false;
    celdas[y][x] = true;

}
/*MOTRAR EL LABERINTO CON LA ENTIDAD EN SU POSICION, ADEMAS DE LA PLANTILLA DETECTADA Y EL ULTIMO MOVIMIENTO*/
void Entidad::MostrarLaberinto(){
    printf("PLANTILLA: %d\nDIRECCION: %d\n\n",plantilla,direccion);
    if(colision)
        this->laberinto->MostrarLaberinto(x,y,'X');
    else
        this->laberinto->MostrarLaberinto(x,y,'O');
    printf("\n");
}

/*CALCULO DE EL SIGUIENTE MOVIMIENTO EN EL LABERINTO*/
bool Entidad::NextMovimiento(){

    int px = x,
        py = y;
    plantilla  = 0;

    Celda celdas[ENTIDAD_CELDAS];
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
        int p[ENTIDAD_CELDAS] = {(int)celdas[0].IsColisionable(),
                                 (int)celdas[1].IsColisionable(),
                                 (int)celdas[2].IsColisionable(),
                                 (int)celdas[3].IsColisionable()};
        for(int i=0;i<ENTIDAD_PLANTILLAS;i++){
            int condicion = 0;
            for(int j=0;j<ENTIDAD_CELDAS;j++)
                condicion += p[j] == plantillas[i][j];
            if(condicion == ENTIDAD_CELDAS){
                plantilla = i;
                break;
            }
        }
    }

    int index              = plantilla*ENTIDAD_CELDAS;
    float probabilidades[] = {
                individuo->GetValorR(index),
                individuo->GetValorR(index+1),
                individuo->GetValorR(index+2),
                individuo->GetValorR(index+3)
    };
    Probabilidad p(probabilidades,ENTIDAD_CELDAS);

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

        pasos++;
        puntuacion++;

        return false;
    }
    else if(laberinto->GetCelda(px,py).IsTipo(CELDA_FINAL)){
        termino = true;

        x = px;
        y = py;

        pasos++;
        puntuacion++;

        return false;
    }

    x = px;
    y = py;

    if(!this->celdas[y][x])
        puntuacion++;
    else
        puntuacion--;
    pasos++;
    this->celdas[y][x] = true;

    colision = false;
    termino = false;

    return true;

}




