#pragma once
#include<cstdlib>
#include"Random.h"
#include "Binario.h"

class Individuo
{
public:
	Individuo(int *bitsGen, int *tipoGen,int genes);
	~Individuo();

	void IniciatIndividuo(void);
	const bool *GetGen(int gen);
	void MostrarIndividuo(int in);

	void SetIndividuo(void);
	void SetIndividuo(Individuo &NewInndividuo);
	void SetFitness(float valor);
	void SetValorObjetivo(float valor);
	void SetPorcentaje(float valor);
	void SetCromosoma(int i,bool valor);
	void InverseCromosoma(int i);

	const inline float  GetFitness(int i) const { return ValorR[i]; }
	const inline float  GetFitness(int i) const { return ValorR[i]; }
	const inline bool  GetCromosoma(int i) const { return Cromosoma[i]; }
	const inline float  GetFitness() const { return Fitness; }
	const inline float  GetValorObjetivo() const { return ValorObjetibvo; }
	const inline float GetPorcentaje() const { return Porcentaje; }

	private:

		void Actualizar();

private:
	bool *Cromosoma;
	int *BitsGen;
	int *TipoGen;
	float *ValorR;
	int Genes;
	int Bits;
	float Fitness;
	float ValorObjetibvo;
	float Porcentaje;
};

