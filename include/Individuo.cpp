#include "Individuo.h"

Individuo::Individuo(int *bitsGen, int *tipoGen, int genes)
{
	Genes = genes;
	Bits = 0;

	BitsGen = new int[Genes];
	TipoGen = new int[Genes];

	for (unsigned int i = 0;i < Genes;i++)
	{
		BitsGen[i] = bitsGen[i];
		TipoGen[i] = tipoGen[i];

		Bits += BitsGen[i];
	}

	Cromsoma = new bool[Bits];
	ValorObjetibvo = 0;
	Fitness = 0;
	Porcentaje = -1;

}
Individuo::~Individuo()
{
	delete[] Cromsoma;
	delete[] BitsGen;
	delete[] TipoGen;

}
void Individuo::IniciatIndividuo()
{
	bool aleatorio;
	for (unsigned int i = 0;i < Bits;i++)
	{
		aleatorio = Random::NextBoolean;
		Cromsoma[i] = aleatorio;	
	}
}
const bool Individuo::GetGen(int gen)
{
	int suma = 0;
	for (unsigned int i = 0;i < gen;i++)
	{
		suma += BitsGen[i];
	}
	return Cromsoma + suma;
}
void Individuo::MostrarIndividuo(int in)
{

	printf("\nIndividuo[%i]: ", in);
	for (unsigned int i = 0;i < Bits;i++)
	{
		printf("%i", Cromsoma[i]);
	}
	for (unsigned int i = 0;i < Genes;i++)
	{
		printf("\nGen[%i]: ", i + 1);
		for (unsigned int j = GetGen(i);j < BitsGen[i];j++)

		{
			printf("%i", Cromsoma[j]);
		}
	}
	printf("\nValor Decodificado:");
	for (unsigned int i = 0;i < Genes;i++)
	{
		printf("\nGen[%i]: %f", i, ValorR[i]);
	}
	printf("\nValor Objetivo:", ValorObjetibvo);
	printf("\nFitness:", Fitness);
	printf("\nPorcentaje:", Porcentaje);

}
void Individuo::SetIndividuo(void)
{
	Fitness = 0;
	ValorObjetibvo = 0;
	Porcentaje = 0;
	for (unsigned int i = 0;i < Genes;i++)
	{
		ValorR[i] = 0;
	}
}
void Individuo::SetIndividuo(Individuo NewInndividuo)
{
	for (unsigned int i = 0;i < Bits;i++)
	{
		Cromsoma[i] = NewInndividuo.Cromsoma[i];
	}
	for (unsigned int i = 0;i < Genes;i++)
	{
		ValorR[i] = NewInndividuo.ValorR[i];
	}
	Fitness = NewInndividuo.Fitness;
	ValorObjetibvo = NewInndividuo.ValorObjetibvo;
	Porcentaje = NewInndividuo.Porcentaje;
}
void Individuo::SetValorObjetivo(float valor)
{
	ValorObjetibvo = valor;
}
void Individuo::SetFiness(float valor)
{
	Fitness = valor;
}
void Individuo::SetPorcentaje(float valor)
{
	Porcentaje = valor;
}
void Individuo::SetValorR(int i,float valor)
{
	ValorR[i] = valor;
}