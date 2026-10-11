#pragma once
#include "Vector3D.h"
#include "Particula.h"
#include "Distribucion.h"

class Generador
{
private:
	physx::PxTransform pos;
	Vector3D vel;

	Distribucion* dVel;
	Distribucion* dPos;
	Distribucion* tVida;

	Particula* m;
	Distribucion* dist;
public:
	Generador(Particula* modelo, Vector3D velocidad, physx::PxTransform posicion, Distribucion* d, Distribucion* v, Distribucion* p, Distribucion* tiempoVida);
	~Generador();
	std::vector<Particula*> generar(double dt);
};

