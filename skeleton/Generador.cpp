#include "Generador.h"
#include <cmath>
#include <algorithm>

Generador::Generador(Particula* modelo, Vector3D velocidad, physx::PxTransform posicion, Distribucion* d, Distribucion* v, Distribucion* tiempoVida) :
	pos(posicion), vel(velocidad), dVel(v), tVida(tiempoVida), m(modelo), dist(d)
{
}

std::vector<Particula*> Generador::generar(double dt)
{
	std::vector<Particula*> particulasGeneredas;

	int nParticulas = std::max<float>(0.f, std::round(dist->siguiente()));

	for (int i = 0; i < nParticulas; i++) {
		Vector3D vFinal = Vector3D(vel.x + dVel->siguiente(), vel.y + dVel->siguiente(), vel.z + dVel->siguiente());
		Particula* parti = new Particula(Vector3D(pos.p), vFinal, Vector3D(0.f, 0.f, 0.f), m->getDampi(), m->getMasa(), tVida->siguiente());
		particulasGeneredas.push_back(parti);
	}

	return particulasGeneredas;
}
