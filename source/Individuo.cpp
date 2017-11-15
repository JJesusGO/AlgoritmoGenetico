#include "Individuo.h"

Individuo::Individuo(){

    Genes     = 0;
    Bits      = 0;
    BitsGen   = NULL;
    TipoGen   = NULL;
    Cromosoma = NULL;
    ValorR    = NULL;

    ValorObjetivo = 0.0f;
	Fitness = 0.0f;
	Porcentaje = -1.0f;

}
Individuo::Individuo(int *bitsGen, int *tipoGen, int genes){

	Genes = genes;
	Bits = 0;

	BitsGen = new int[Genes];
	TipoGen = new int[Genes];
	ValorR  = new float[Genes];

	for (unsigned int i = 0;i < Genes;i++){
		BitsGen[i] = bitsGen[i];
		TipoGen[i] = tipoGen[i];
		Bits += BitsGen[i];
	}

	Cromosoma = new bool[Bits];

	ValorObjetivo = 0.0f;
	Fitness = 0.0f;
	Porcentaje = -1.0f;

}
Individuo::~Individuo(){
    if(Cromosoma!=NULL)
	delete[] Cromosoma;
	if(BitsGen!=NULL)
	delete[] BitsGen;
	if(TipoGen!=NULL)
	delete[] TipoGen;
	if(ValorR!=NULL)
	delete[] ValorR;

}

void Individuo::MostrarIndividuo(int in){

	printf("\nINDIVIDUO[%i]: ", in);
	for (unsigned int i = 0;i < Genes;i++){
		const bool *codigo = GetGen(i);

		for (int j = 0;j < BitsGen[i]; j++)
			printf("%d", codigo[j]);

        if(!(i == Genes-1))
            printf(":");
	}
	printf("\nVALORES:");
	for (unsigned int i = 0;i < Genes;i++)
	{
		printf("\n  VALOR[%i]: %+0.4f", i, ValorR[i]);
	}
	printf("\nOBJETIVO:   %+0.4f", ValorObjetivo);
	printf("\nFITNESS:    %+0.4f", Fitness);
	printf("\nPORCENTAJE: %+0.4f", Porcentaje);

}


void Individuo::SetIndividuo(void){
	Fitness = 0.0f;
	ValorObjetivo = 0.0f;
	Porcentaje = -1.0;
	for (unsigned int i = 0;i < Genes;i++)
	{
		ValorR[i] = 0;
	}
}
void Individuo::SetIndividuo(int *bitsGen, int *tipoGen,int genes){

	Genes = genes;
	Bits = 0;

	if(BitsGen!=NULL)
        delete []BitsGen;
    BitsGen = new int[Genes];

    if(TipoGen!=NULL)
        delete []TipoGen;
    TipoGen = new int[Genes];

    if(ValorR!=NULL)
        delete []ValorR;
    ValorR  = new float[Genes];


	for (unsigned int i = 0;i < Genes;i++){
		BitsGen[i] = bitsGen[i];
		TipoGen[i] = tipoGen[i];
		Bits += BitsGen[i];
	}

	if(Cromosoma!=NULL)
        delete []Cromosoma;
	Cromosoma = new bool[Bits];

	ValorObjetivo = 0.0f;
	Fitness = 0.0f;
	Porcentaje = -1.0f;

	Actualizar();
}

void Individuo::SetIndividuo(Individuo &NewInndividuo){

    Genes = NewInndividuo.GetGenes();
	Bits = 0;

	if(BitsGen!=NULL)
        delete []BitsGen;
    BitsGen = new int[Genes];

    if(TipoGen!=NULL)
        delete []TipoGen;
    TipoGen = new int[Genes];

    if(ValorR!=NULL)
        delete []ValorR;
    ValorR = new float[Genes];

	for (unsigned int i = 0;i < Genes;i++){
		BitsGen[i] = NewInndividuo.GetBitsGen(i);
		TipoGen[i] = NewInndividuo.GetTipoGen(i);
		Bits += BitsGen[i];
	}
	if(Cromosoma!=NULL)
        delete []Cromosoma;
	Cromosoma = new bool[Bits];

	for (unsigned int i = 0;i < Bits;i++){
		Cromosoma[i] = NewInndividuo.GetCromosoma(i);
	}
	for (unsigned int i = 0;i < Genes;i++){
		ValorR[i] = NewInndividuo.GetValorR(i);
	}

	Fitness = NewInndividuo.GetFitness();
	ValorObjetivo = NewInndividuo.GetValorObjetivo();
	Porcentaje = NewInndividuo.GetPorcentaje();

	Actualizar();

}
void Individuo::SetValorObjetivo(float valor){
	ValorObjetivo = valor;
}
void Individuo::SetFitness(float valor){
	Fitness = valor;
}
void Individuo::SetPorcentaje(float valor){
	Porcentaje = valor;
}
void Individuo::SetCromosoma(int i, bool valor){
	Cromosoma[i] = valor;
}
void Individuo::SetCromosoma(){
    for(int i=0;i<Bits;i++)
        Cromosoma[i] = Random::NextBoolean();
    Actualizar();
}
void Individuo::InvertirCromosoma(int i){
	Cromosoma[i] != Cromosoma[i];
}
void Individuo::Actualizar(){
	for (int i = 0;i < Genes;i++){
		Binario bin(TipoGen[i]);
		ValorR[i] = bin.GetNumero(GetGen(i), BitsGen[i]);
	}
}
const bool* Individuo::GetGen(int gen){
	int suma = 0;
	for (unsigned int i = 0;i < gen;i++){
		suma += BitsGen[i];
	}
	return Cromosoma + suma;
}
