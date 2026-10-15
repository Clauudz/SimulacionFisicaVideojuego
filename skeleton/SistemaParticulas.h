#pragma once
#include "Particula.h"
#include "Generador.h"
#include <vector>

class ParticulaJerarquica;
class SistemaParticulas
{
private:
	std::vector<Particula*> particulas;
	std::vector<Generador*> generadores;

	Vector3D gravedad;
public:
	SistemaParticulas();
	~SistemaParticulas();
	void update(double dt);

	void addGenerador(Generador* g);
	void addParticulas(const std::vector<Particula*>& p);
};

