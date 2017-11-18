#include "Laberinto.h"

/*CONTRUCTOR DEL LABERINTO*/
Laberinto::Laberinto(){

    this->celdas = NULL;
    this->n      = n;
    this->m      = m;
    this->ix     = 0;
    this->iy     = 0;
    this->fx     = 0;
    this->fy     = 0;


}
/*CONTRUCTOR DEL LABERINTO USANDO UN ARCHIVO COMO REFERENCIA*/
Laberinto::Laberinto(std::string archivo){

    this->celdas = NULL;
    this->ix = 0;
    this->iy = 0;
    this->fx = 0;
    this->fy = 0;

    if(!LeerLaberinto(archivo))
        printf("ERROR AR LEER EL ARCHIVO: %s",archivo.c_str());

}
/*DESTRUCTOR DL LABERINTO*/
Laberinto::~Laberinto(){
    BorrarMemoria();
}

/*LEER EL LABERINTO Y RELLENAR LA MEMORIA DEL LAS CELDAS*/
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

	fclose(file);
    Actualizar();

    return true;
}

/*CREAR LA MEMORIA DE LAS CELDAS*/
void Laberinto::CrearMemoria(){

    BorrarMemoria();
    celdas = new Celda*[n];
    for(unsigned int i=0;i<n;i++)
        celdas[i] = new Celda[m];

}
/*BORRAR LA MEMORIA DE LAS CELDAS*/
void Laberinto::BorrarMemoria(){

    if(celdas==NULL)
        return;
    for(unsigned int i=0;i<n;i++)
        delete [] celdas[i];
    delete []celdas;

}

/*ACTUALIZAR LAS POSICIONES DE LAS CELDA INICIO Y FIN*/
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

/*MOSTRAR EL LABERINTO */
void Laberinto::MostrarLaberinto(){

    for(unsigned int i=0;i<n;i++){
        for(unsigned int j=0;j<m;j++)
            printf("%c",celdas[i][j].GetEsquema());
        printf("\n");
    }

}
/*MOSTRAR EL LABERINTO CON UN CARACTER ESPECIAL EN ALGUNA POSICION*/
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
