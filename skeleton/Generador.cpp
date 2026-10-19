#include "Generador.h"
#include <cmath>
#include <algorithm>

Generador::Generador(float masa, float damp, Vector3D velocidad, physx::PxTransform posicion,
	Distribucion* d, Distribucion* v, Distribucion* p, Distribucion* tiempoVida, const std::vector<ForceGenerator*>& f) :
	pos(posicion), vel(velocidad), dVel(v), dPos(p), tVida(tiempoVida), masaModelo(masa), dampModelo(damp), dist(d), fuerzas(f)
{
}

Generador::~Generador()
{
	delete dVel;
	delete dPos;
	delete tVida;
	delete dist;
}

std::vector<Particula*> Generador::generar(double dt)
{
	std::vector<Particula*> particulasGeneredas;

	int nParticulas = std::max<float>(0.f, std::round(dist->siguiente()));

	for (int i = 0; i < nParticulas; i++) {
		Vector3D vFinal = Vector3D(vel.x + dVel->siguiente(), vel.y + dVel->siguiente(), vel.z + dVel->siguiente());
		Vector3D pFinal = Vector3D(pos.p.x + dPos->siguiente(), pos.p.y + dPos->siguiente(), pos.p.z + dPos->siguiente());

		Particula* parti = new Particula(pFinal, vFinal, Vector3D(0.f, 0.f, 0.f), dampModelo, masaModelo, tVida->siguiente());
		particulasGeneredas.push_back(parti);

		for (ForceGenerator* fg : fuerzas) {
			parti->addFuerza(fg);
		}
	}

	return particulasGeneredas;
}
