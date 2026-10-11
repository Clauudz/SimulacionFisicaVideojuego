#include "sistemaParticulas.h"

SistemaParticulas::SistemaParticulas() : gravedad(Vector3D(0,-10,0))
{
}

SistemaParticulas::~SistemaParticulas()
{
	for (Particula* par : particulas) {
		delete par;
	}

	for (Generador* gen : generadores) {
		delete gen;
	}
}

void SistemaParticulas::update(double dt) {

	for (Particula* par : particulas) {
		par->aplicarFuerza(gravedad); // separar (en otro for) si en el fururo hay una fuerza q depende d otras particulas
		par->semiIntegrate(dt);
	}

	auto it = particulas.begin();

	while (it != particulas.end()) {
		Particula* par = *it;

		if (!par->estaViva()) {
			delete par;
			it = particulas.erase(it);
		}
		else {
			++it;
		}
	}

	for (Generador* gen : generadores) {
		std::vector<Particula*> p = gen->generar(dt);
		particulas.insert(particulas.end(), p.begin(), p.end());
	}
}

void SistemaParticulas::addGenerador(Generador* g)
{
	generadores.push_back(g);
}

void SistemaParticulas::addParticulas(const std::vector<Particula*>& p)
{
	particulas.insert(particulas.end(), p.begin(), p.end());
}
