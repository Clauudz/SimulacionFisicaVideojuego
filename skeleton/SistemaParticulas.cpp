#include "sistemaParticulas.h"
#include "ParticulaJerarquica.h"

SistemaParticulas::SistemaParticulas() : tiempoTotal(0.0)
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

	for (ForceGenerator* fg : fuerzas) {
		delete fg;
	}
}

void SistemaParticulas::update(double dt) {

	for (Particula* par : particulas) {
		par->semiIntegrate(dt, tiempoTotal);
	}

	std::vector<Particula*> nuevasHijas; //fuegos artificiales

	auto it = particulas.begin();
	while (it != particulas.end()) {
		Particula* par = *it;

		if (!par->estaViva()) {
			std::vector<Particula*> p = par->generarHijas();
			nuevasHijas.insert(nuevasHijas.end(), p.begin(), p.end());

			delete par;
			it = particulas.erase(it);
		}
		else {
			++it;
		}
	}

	particulas.insert(particulas.end(), nuevasHijas.begin(), nuevasHijas.end());

	for (Generador* gen : generadores) {
		std::vector<Particula*> p = gen->generar(dt);
		particulas.insert(particulas.end(), p.begin(), p.end());
	}

	tiempoTotal += dt;
}

void SistemaParticulas::addGenerador(Generador* g)
{
	generadores.push_back(g);
}

void SistemaParticulas::addParticulas(const std::vector<Particula*>& p)
{
	particulas.insert(particulas.end(), p.begin(), p.end());
}

void SistemaParticulas::addForceGenerator(ForceGenerator* f)
{
	fuerzas.push_back(f);
}

void SistemaParticulas::dispararExplosion(Vector3D centro, float K, float R, double tau)
{
	ForceGenerator* f = new ExplosionGenerator(K, centro, R, tau, tiempoTotal);

	for (Particula* par : particulas) {
		par->addFuerza(f);
	}
}
