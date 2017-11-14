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

	Cromosoma = new bool[Bits];
	ValorObjetibvo = 0;
	Fitness = 0;
	Porcentaje = -1;

}
Individuo::~Individuo()
{
	delete[] Cromosoma;
	delete[] BitsGen;
	delete[] TipoGen;

}
void Individuo::IniciatIndividuo()
{
	bool aleatorio;
	for (unsigned int i = 0;i < Bits;i++)
	{
		aleatorio = Random::NextBoolean();
		Cromosoma[i] = aleatorio;	
	}
	Actualizar();
}
const bool* Individuo::GetGen(int gen)
{
	int suma = 0;
	for (unsigned int i = 0;i < gen;i++)
	{
		suma += BitsGen[i];
	}
	return Cromosoma + suma;
}
void Individuo::MostrarIndividuo(int in)
{

	printf("\nIndividuo[%i]: ", in);
	for (unsigned int i = 0;i < Bits;i++)
	{
		printf("%i", Cromosoma[i]);
	}
	for (unsigned int i = 0;i < Genes;i++)
	{
		const bool *codigo = GetGen(i);
		for (int j = 0;j < BitsGen[i];j++)
			printf("%d", codigo[j]);

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
void Individuo::SetIndividuo(Individuo &NewInndividuo)
{
	for (unsigned int i = 0;i < Bits;i++)
	{
		Cromosoma[i] = NewInndividuo.Cromosoma[i];
	}
	for (unsigned int i = 0;i < Genes;i++)
	{
		ValorR[i] = NewInndividuo.ValorR[i];
	}
	Fitness = NewInndividuo.Fitness;
	ValorObjetibvo = NewInndividuo.ValorObjetibvo;
	Porcentaje = NewInndividuo.Porcentaje;

	Actualizar();
}
void Individuo::SetValorObjetivo(float valor)
{
	ValorObjetibvo = valor;
}
void Individuo::SetFitness(float valor)
{
	Fitness = valor;
}
void Individuo::SetPorcentaje(float valor)
{
	Porcentaje = valor;
}
void Individuo::SetCromosoma(int i, bool valor)
{
	Cromosoma[i] = valor;
}
void Individuo::InverseCromosoma(int i)
{
	if (Cromosoma[i] == true)
	{
		Cromosoma[i]=false;
	}
	else
	{
		Cromosoma[i] = true;
	}	
}
void Individuo::Actualizar()
{
	for (int i = 0;i < Genes;i++) 
	{
		Binario bin(TipoGen[i]);
		ValorR[i] = bin.GetNumero((bool*)GetGen(i), BitsGen[i]);
	}
}