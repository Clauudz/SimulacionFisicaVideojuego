	#include "TorbellinoSR.h"

TorbellinoSR::TorbellinoSR(Vector3 centro, float intensidad)
{
	_centro = centro;
	_intensidad = intensidad;
}

void TorbellinoSR::updateForce(SolidoRigido* solido)
{
	PxRigidDynamic* d = solido->comprobarDinamico();
	if (!d) return;

	Vector3 diff = solido->getPosicion() - _centro;
	const float altura = 20.0f;//altura hacia la que tiende a subir
	Vector3 vel = Vector3(- diff.z, altura - diff.y, diff.x) * _intensidad;

	const float k1 = 0.5f;
	const float k2 = 0.0f;

	Vector3 rel = vel - d->getLinearVelocity();// vel relativa al aire
	Vector3 fuerza = k1 * rel + k2 * rel.magnitude() * rel;
	d->addForce(fuerza);
}
