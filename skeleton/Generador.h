#pragma once
#include "Vector3D.h"
#include "Particula.h"
#include "Distribucion.h"
#include "ForceGenerator.h"

class Generador
{
private:
	physx::PxTransform pos;
	Vector3D vel;

	Distribucion* dVel;
	Distribucion* dPos;
	Distribucion* tVida;

	float masaModelo;
	float dampModelo;

	Distribucion* dist;

	std::vector<ForceGenerator*> fuerzas;
public:
	Generador(float masa, float damp, Vector3D velocidad, physx::PxTransform posicion,
		Distribucion* d, Distribucion* v, Distribucion* p, Distribucion* tiempoVida, const std::vector<ForceGenerator*>& f);
	~Generador();
	std::vector<Particula*> generar(double dt);
};

