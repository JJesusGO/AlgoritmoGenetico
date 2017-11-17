#include "Individuo.h"
//CONSTRUCTOR DE LA CLSE QUE INICIALIZA TODAS LA VARIABLES MIENBRO EN NULO
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
//CONSTRUCTOR DONDE SE RESERVA LA MEMORIO NECESARIA PARA CADA VARIABLE
Individuo::Individuo(int *bitsGen, int *tipoGen, int genes){

	Genes = genes;
	Bits = 0;
	//RESERVA DE MEMORIA
	BitsGen = new int[Genes];
	TipoGen = new int[Genes];
	ValorR  = new float[Genes];
	//SE ASIGNA EL VALOR DEL PUNTERO A CADA VARIABLE
	for (unsigned int i = 0;i < Genes;i++){
		BitsGen[i] = bitsGen[i];
		TipoGen[i] = tipoGen[i];
		Bits += BitsGen[i];
	}

	//RESERVA DE MEMORIA DEL CROMODOMA
	Cromosoma = new bool[Bits];


	ValorObjetivo = 0.0f;
	Fitness = 0.0f;
	Porcentaje = -1.0f;

}
//DESTRUCTOR
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
//MUESTRA EL INDIVIDUO
const void Individuo::MostrarIndividuo(int in) const {

	//MUESTRA CROMOSOMAS Y SUS RESPECTIVOS GENES
	printf("\nINDIVIDUO[%i]: ", in);
	for (unsigned int i = 0;i < Genes;i++){
		const bool *codigo = GetGen(i);

		for (int j = 0;j < BitsGen[i]; j++)
			printf("%d", codigo[j]);

        if(!(i == Genes-1))
            printf(":");
	}
	//VALOR DECODIFICADO DE CADA GEN
	printf("\nVALORES:");
	for (unsigned int i = 0;i < Genes;i++)
	{
		printf("\n  VALOR[%i]: %+0.4f", i, ValorR[i]);
	}
	//VALORRES DE LAS DEMAS VARIABLES
	printf("\nOBJETIVO:   %+0.4f", ValorObjetivo);
	printf("\nFITNESS:    %+0.4f", Fitness);
	printf("\nPORCENTAJE: %+0.4f", Porcentaje);
	printf("\nSEED:       %s", seed.GetSeedString().c_str());

}

//FUNCION QUE RESETEA LOS PARAMETROS DEL INDIVIDUO SELECCIONADO
void Individuo::SetIndividuo(void){
	Fitness = 0.0f;
	ValorObjetivo = 0.0f;
	Porcentaje = -1.0;
	for (unsigned int i = 0;i < Genes;i++)
	{
		ValorR[i] = 0;
	}
}
//ASIGNA Y CREA MEMORIA CON LOS VALORES QUE SE INGRESAN A LA FUNCION
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
//SE ASIGNAN LOS VALORES DEL NUEVO INDIVIDUO AL INDIVIDUO ACTUAL 
void Individuo::SetIndividuo(Individuo &NewInndividuo){

    Genes = NewInndividuo.GetGenes();
	Bits = 0;
    seed = NewInndividuo.GetSeed();

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
//REGRESA EL VALOR DE LA SEMILLA
void Individuo::SetSeed(Seed seed){
    this->seed = seed;
}
//REGRESA EL VALOR OBJETIVO
void Individuo::SetValorObjetivo(float valor){
	ValorObjetivo = valor;
}
//REGRESA EL VALOR FITNESS
void Individuo::SetFitness(float valor){
	Fitness = valor;
}
//REGRESA EL VALOR DEL PORCENTAJE
void Individuo::SetPorcentaje(float valor){
	Porcentaje = valor;
}
//REGRESA EL VALOR DEL BIT DEL CROMOSOMA 
void Individuo::SetCromosoma(int i, bool valor){
	Cromosoma[i] = valor;
}
//ASIGNA VALORES DE TRUE Y FALSE ALEATORIAMENTE PARA RELLENAR EL CROMOSOMA
void Individuo::SetCromosoma(){
    for(int i=0;i<Bits;i++)
        Cromosoma[i] = Random::NextBoolean();
    Actualizar();
}
//INVIERTE EL BIT DE UN CROMOSMA 
void Individuo::InvertirCromosoma(int i){
	Cromosoma[i] != Cromosoma[i];
}
//ACTUALIZA EL VALOR DECODIFICADO DE CADA GEN
void Individuo::Actualizar(){
	for (int i = 0;i < Genes;i++){
		Binario bin(TipoGen[i]);
		//DEPENDIENDO DEL TIPO D EGEN SU DECODIFICACION SE CAMBIA POR ENTERO,REAL O NEGATIVO
		ValorR[i] = bin.GetNumero(GetGen(i), BitsGen[i]);
	}
}
//REGRESA EL TAMAÑO DEL GEN 
const bool* Individuo::GetGen(int gen) const {
	int suma = 0;
	for (unsigned int i = 0;i < gen;i++){
		suma += BitsGen[i];
	}
	return Cromosoma + suma;
}
