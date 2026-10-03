#include "Proyectil.h"

Proyectil::Proyectil(Vector3D pos, Vector3D velReal, Vector3D velSim, float masa, float damp) : Particula(pos, {0,0,0}, damp, masa),
masaSim(0.f), gravedadSim(0.f)
{
	ajustaMasaYGravedad(velReal, velSim);

	vel = velSim;
}

void Proyectil::ajustaMasaYGravedad(Vector3D vReal, Vector3D vSim)
{
	float vR = vReal.magnitude();
	float vS = vSim.magnitude();

	masaSim = (masa * (vR * vR)) / (vS * vS);
	gravedadSim = ((vS * vS) * GRAVEDAD) / (vR * vR);
}

void Proyectil::semiIntegrate(double d)
{
	acc += Vector3D(0.f, gravedadSim, 0.f);
	Particula::semiIntegrate(d);
}
