#pragma once
#include "Particula.h"
#include "Generador.h"
#include "ForceGenerator.h"
#include <vector>

class ParticulaJerarquica;
class SistemaParticulas
{
private:
	std::vector<Particula*> particulas;
	std::vector<Generador*> generadores;
	std::vector<ForceGenerator*> fuerzas;

	//Vector3D gravedad;
	double tiempoTotal;
public:
	SistemaParticulas();
	~SistemaParticulas();
	void update(double dt);

	void addGenerador(Generador* g);
	void addParticulas(const std::vector<Particula*>& p);
	void addForceGenerator(ForceGenerator* f);

	void dispararExplosion(Vector3D centro, float K, float R, double tau);
};

