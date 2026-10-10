#include "sistemaParticulas.h"

SistemaParticulas::SistemaParticulas()
{
}

void SistemaParticulas::update(double dt) {
	for (Particula* par : particulas) {
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
}