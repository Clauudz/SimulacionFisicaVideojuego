#pragma once
#include "Particula.h"

class ForceGenerator {
public:
	ForceGenerator();
	virtual void aplicaFuerzaAhora() = 0;
};