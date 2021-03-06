#ifndef __MENUPLANNING_H__
#define __MENUPLANNING_H__


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>


#include "Individual.h"
#include "constants.cpp"
#include <unistd.h>
char *getcwd(char *buf, size_t size);

#define CROSSOVER_UNIFORM 0
#define CROSSOVER_HUX 1

struct infoPlatos                       //Struct que almacena informacion de los platos utilizada en el proceso de creacion del plan
{
	string nombre;						//Nombre del plato
	int diasRep;                        //Numero de dias desde que se eligio el plato en el plan por ultima vez
	float precio;                       //Precio del plato
	float cantidad;						//Cantidad en gramos
	vector<int> gruposAl;          		//Grupos alimenticios correspondientes a los ingredientes principales del plato
	vector<float> infoN;           		//Informacion nutricional del plato
	vector<string> alg;         		//Alergenos del plato
	vector<string> inc;        			//Incompatibilidades alimenticias del plato
};


class MenuPlanning : public Individual {
	
private:
	
	// Numero de dias, platos y objetivos
	static int nDias;
	static int nParam;
	static int nObj;
	
	//Vectores de platos
	static vector<infoPlatos> v_primerosPlatos;
	static vector<infoPlatos> v_segundosPlatos;
	static vector<infoPlatos> v_postres;
	
	//Ingesta recomendada al dia, grados de penalizaciones, grupos alimenticios existentes, vector de compatibilidad de platos
	static vector< pair<double, double> > ingRecomendada;
	static vector<double> penalizaciones;
	static vector< pair<int, int> > gruposAl;
	static vector< vector< vector<double> > > v3_compatibilidadPlatos;
	
	
	//Del plan alimenticio total: alergenos, incompatibilidades alimenticias, grupos alimenticios, informacion nutricional
	static vector<string> alergenosPlan;
	static vector<string> incompatibilidadesPlan;
	static vector<int> gruposAlPlan;
	static vector<double> infoNPlan;
	
	static int i_max;
	
	// Operadores geneticos
	void dependentCrossover(Individual* ind);
	void dependentMutation(double pm);
	
public:
	

	// Inicializacion
	bool init(const vector<string> &params);
	
	//Evaluacion de individuo
	void evaluate(void);								
	
	//Clonacion de individuo
	Individual* clone(void) const;
	
	//Generacion aleatoria de individuo
	void restart(void);									
	
	//Metodo de reparacion de individuo
	void repair(void);									
	
	//Setters principales
	void set_ingestaRecomedada(void);
	void set_penalizaciones(void);
	void set_gruposAl(void);
	
	//Lectura de ficheros de platos
	void set_Platos(void) 
	{ 
		set_VectoresPlatos("", v_primerosPlatos); 
		set_VectoresPlatos("", v_segundosPlatos); 
		set_VectoresPlatos("", v_postres); 
	}
	void set_VectoresPlatos(const char* c_filename, vector<infoPlatos> &v_vecP);
	
	//Calculo del vector de compatibilidad de platos
	void set_vectorCompatibilidad(void);
	void set_GAElegidos(vector<int> gal, vector<bool> &galE);
	double set_penalizacionVC(vector<int> &gal, vector<bool> galE);
	
	//Comprobar las restricciones del problema
	bool checkInfoN(const int i);
	bool checkInfoN2(void);
	
	
	//Metodos para el calculo del objetivo de grado de repeticion
	bool gaElegidosPorIteracion(vector<int> vec, int valor);
	int setValorPP(int id);
	int setValorSP(int id);
	int setValorP(int id);
	void sumValorPP(void);
	void sumValorSP(void);
	void sumValorP(void);
	void sumValorGA(void);
	void set_ultimos5GA(vector<vector<int> > &ultimos5GA, vector<int> vec);
	double set_ValorGAFirstAlternativa(vector<vector<int> > &ultimos5GA, vector<int> vec);
	
	unsigned int inline getOptDirection(const int i) const { return MINIMIZE; }
	double inline getMinimum(const int i) const { return 1; }
	double inline getMaximum(const int i) const 
	{ 
		if(i % 3 == 0) return v_primerosPlatos.size();
		else if(i % 3 == 1) return v_segundosPlatos.size();
		else if(i % 3 == 2) return v_postres.size();
	}
	
};

#endif
