#pragma once
#include "Particula.h"
#include "Distribucion.h"
#include "ForceGenerator.h"

class ParticulaJerarquica : public Particula
{
private: 
	static const int NIVEL_MAXIMO = 3;

	int nivel;
	Distribucion* vHijas;
	Distribucion* cantHijas;

	std::vector<ForceGenerator*> fuerzasHijas;

public:
	ParticulaJerarquica(Vector3D posi, Vector3D velo, Vector3D ac, float damp, float mass, double lifeTime,
		int nivel, Distribucion* velHijas, Distribucion* cantidadHijas, const std::vector<ForceGenerator*>& fH);
	std::vector<Particula*> generarHijas() override;
};

