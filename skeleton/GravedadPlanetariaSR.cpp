#include "GravedadPlanetariaSR.h"

#include <iostream>

GravedadPlanetariaSR::GravedadPlanetariaSR(Vector3D center, float mass, float radius, float e) :
	centro(center), masa(mass), radio(radius), epsilon(e)
{
}

void GravedadPlanetariaSR::updateForce(SolidoRigido* solido)
{
	PxRigidDynamic* d = solido->comprobarDinamico();
	if (!d) return;

	Vector3D solidoACentro = centro - solido->getPosicion();
	float r = solidoACentro.magnitude();
	if (r > radio) return;

	float fuerza = G * ((masa * d->getMass()) / ((r * r) + (epsilon * epsilon)));
	Vector3D f = solidoACentro.normalize() * fuerza;
	d->addForce(f);
}