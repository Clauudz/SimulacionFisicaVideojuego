#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class RenderItem;
class Particula
{
public:
	Particula(Vector3D posi, Vector3D ac, float damp);
	~Particula();

	void integrate(double d);
	void semiIntegrate(double d);
	void verletIntegrate(double d);

private:

	physx::PxTransform pos;
	Vector3D vel;
	Vector3D acc;
	float dampi;
	RenderItem* m_item = nullptr;

	physx::PxTransform posAnt;
};

