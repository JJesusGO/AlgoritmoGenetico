#ifndef CELDA_H
#define CELDA_H

#define CELDA_FINAL     3
#define CELDA_INICIO    2
#define CELDA_ESPACIO   1
#define CELDA_OBSTACULO 0

class Celda{

    int tipo;
    int x,y;
    static char esquema[4];

    public:
        Celda();

    void SetPosicion(int x,int y);
    void SetTipo(int tipo);
    static void SetEsquema(int index,char caracter);

    public:
        inline const int  GetX() const {return x;}
        inline const int  GetY() const {return y;}
        inline const int  GetTipo() const {return tipo;}
        inline const char GetEsquema() const {return esquema[tipo];}
        inline const bool IsTipo(int tipo) const {return tipo==this->tipo;}

};


#endif
