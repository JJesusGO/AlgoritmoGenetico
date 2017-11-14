#pragma once
#include<cstdlib>
#include"Random.h"
class Individuo
{
public:
	Individuo(int *bitsGen, int *tipoGen,int genes);
	~Individuo();

	void IniciatIndividuo(void);
	const bool GetGen(int gen);
	void MostrarIndividuo(int in);

	void SetIndividuo(void);
	void SetIndividuo(Individuo NewInndividuo);
	void SetFiness(float valor);
	void SetValorObjetivo(float valor);
	void SetPorcentaje(float valor);
	void SetValorR(int i,float valor);

	const inline float  GetFitness(int i) const { return ValorR[i]; }
	const inline float  GetFitness(int i) const { return ValorR[i]; }
	const inline bool  GetCromosoma(int i) const { return Cromsoma[i]; }
	const inline float  GetFitness() const { return Fitness; }
	const inline float  GetValorObjetivo() const { return ValorObjetibvo; }
	const inline float GetPorcentaje() const { return Porcentaje; }



private:
	bool *Cromsoma;
	int *BitsGen;
	int *TipoGen;
	float *ValorR;
	int Genes;
	int Bits;
	float Fitness;
	float ValorObjetibvo;
	float Porcentaje;
};

