#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class RenderItem;
class Particula
{
public:
	Particula(Vector3D posi, Vector3D velo, Vector3D ac, float damp, float mass, double lifeTime);
	virtual ~Particula();

	virtual void integrate(double d);
	virtual void semiIntegrate(double d);
	virtual void verletIntegrate(double d);

	virtual std::vector<Particula*> generarHijas() { return {}; }

	bool estaViva() const;

	physx::PxTransform getPos() const { return pos; }
	Vector3D getVel() const { return vel; }
	void aplicarFuerza(Vector3D fuerza);

protected:

	physx::PxTransform pos;
	Vector3D vel;
	Vector3D acc;
	float masa;
	float dampi;
	RenderItem* m_item = nullptr;

	physx::PxTransform posAnt;

	double tiempoVida;
};

