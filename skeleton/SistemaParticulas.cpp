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

	auto it = std::remove_if(particulas.begin(), particulas.end(),
		[](Particula* par) {
			return !par->estaViva();
		});

	for (auto i = it; i != particulas.end(); i++) {
		delete *i;
	}

	particulas.erase(it, particulas.end());

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
