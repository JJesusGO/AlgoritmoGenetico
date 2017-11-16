#pragma once

#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <cstdio>
#include <cstdlib>
#include "Random.h"
#include "Binario.h"

class Individuo{

public:

    Individuo();
	Individuo(int *bitsGen, int *tipoGen,int genes);
	~Individuo();

	const void MostrarIndividuo(int in) const;

	void InvertirCromosoma(int i);

	void SetIndividuo(void);
	void SetIndividuo(int *bitsGen, int *tipoGen,int genes);
	void SetIndividuo(Individuo &NewInndividuo);

	void SetFitness(float valor);
	void SetSeed(Seed seed);
	void SetValorObjetivo(float valor);
	void SetPorcentaje(float valor);
	void SetCromosoma(int i,bool valor);
	void SetCromosoma();

    const bool          *GetGen(int gen) const ;
    const inline Seed   GetSeed() const {return seed;}
    const inline int    GetGenes() const {return Genes;}
    const inline int    GetBits() const {return Bits;}
    const inline int    GetTipoGen(int i) const {return TipoGen[i];}
    const inline int    GetBitsGen(int i) const {return BitsGen[i];}
	const inline float  GetValorR(int i) const { return ValorR[i]; }
	const inline bool   GetCromosoma(int i) const { return Cromosoma[i]; }
	const inline float  GetFitness() const { return Fitness; }
	const inline float  GetValorObjetivo() const { return ValorObjetivo; }
	const inline float  GetPorcentaje() const { return Porcentaje; }

    void Actualizar();

private:

    Seed  seed;
	bool  *Cromosoma;
	int   *BitsGen;
	int   *TipoGen;
	float *ValorR;
	int   Genes;
	int   Bits;
	float Fitness;
	float ValorObjetivo;
	float Porcentaje;

};

#endif // INDIVIDUO_H
