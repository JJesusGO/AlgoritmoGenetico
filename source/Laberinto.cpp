#include "Laberinto.h"

Laberinto::Laberinto(std::string archivo){

    this->celdas = NULL;
    this->ix = 0;
    this->iy = 0;
    this->fx = 0;
    this->fy = 0;

    if(!LeerLaberinto(archivo))
        printf("ERROR AR LEER EL ARCHIVO: %s",archivo.c_str());

    Actualizar();
}
Laberinto::Laberinto(Celda celdas[][100],int n,int m){

    this->celdas = NULL;
    this->n = n;
    this->m = m;
    this->ix = 0;
    this->iy = 0;
    this->fx = 0;
    this->fy = 0;

    Actualizar();

}
Laberinto::~Laberinto(){
    BorrarMemoria();
}
bool Laberinto::LeerLaberinto(std::string archivo){

    FILE *file = fopen(archivo.c_str(),"r");
    if(file==NULL)
        return false;

    fscanf(file,"%d",&n);
    fscanf(file,"%d",&m);

    CrearMemoria();

    for(unsigned int i=0;i<n;i++){
        char *renglon = new char[m];
        fscanf(file,"%s",renglon);
        for(unsigned int j=0;j<m;j++){
            celdas[i][j].SetPosicion(j,i);
            celdas[i][j].SetTipo(static_cast<int>(renglon[j] - '0'));
        }
        delete [] renglon;
    }

    return true;
}
void Laberinto::CrearMemoria(){

    BorrarMemoria();
    celdas = new Celda*[n];
    for(unsigned int i=0;i<n;i++)
        celdas[i] = new Celda[m];

}
void Laberinto::BorrarMemoria(){

    if(celdas==NULL)
        return;
    for(unsigned int i=0;i<n;i++)
        delete [] celdas[i];
    delete []celdas;

}
void Laberinto::Actualizar(){

    for(unsigned int i=0;i<n;i++)
        for(unsigned int j=0;j<m;j++){
            if(celdas[i][j].IsTipo(CELDA_INICIO)){
                ix = j;
                iy = i;
            }
            if(celdas[i][j].IsTipo(CELDA_FINAL)){
                fx = j;
                fy = i;
            }
        }

}

void Laberinto::MostrarLaberinto(){

    for(unsigned int i=0;i<n;i++){
        for(unsigned int j=0;j<m;j++)
            printf("%c",celdas[i][j].GetEsquema());
        printf("\n");
    }

}
void Laberinto::MostrarLaberinto(int x,int y,char c){


    for(unsigned int i=0;i<n;i++){
        for(unsigned int j=0;j<m;j++)
            if(i==y && j==x)
                printf("%c",c);
            else
                printf("%c",celdas[i][j].GetEsquema());
        printf("\n");
    }

}
