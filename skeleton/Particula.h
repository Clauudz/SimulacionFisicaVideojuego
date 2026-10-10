#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class RenderItem;
class Particula
{
public:
	Particula(Vector3D posi, Vector3 velo, Vector3D ac, float damp, float mass, double lifeTime);
	virtual ~Particula();

	virtual void integrate(double d);
	virtual void semiIntegrate(double d);
	virtual void verletIntegrate(double d);

	bool estaViva() const;

	physx::PxTransform getPos() const { return pos; }
	float getMasa() const { return masa; }
	float getDampi() const { return dampi; }

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

