#pragma once
#include "Particula.h"
#include <vector>

class SistemaParticulas
{
private:
	std::vector<Particula*> particulas;
public:
	SistemaParticulas();
	void update(double dt);
};

