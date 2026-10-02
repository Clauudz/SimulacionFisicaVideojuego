#pragma once
#include "Particula.h"

constexpr float GRAVEDAD = -9.8f;

class Proyectil : public Particula
{
private:
	float gravedadSim;
	float masaSim;
public:
	Proyectil(Vector3D pos, Vector3D velReal, Vector3D velSim, float masa);
	void ajustaMasaYGravedad(Vector3D vReal, Vector3D vSim);

	void semiIntegrate(double d) override;
};

