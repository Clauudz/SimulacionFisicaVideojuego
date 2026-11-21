#include "VientoSR.h"

VientoSR::VientoSR(Vector3 vel)
{
	_vel = vel;
}

void VientoSR::updateForce(SolidoRigido* solido)
{
	PxRigidDynamic* d = solido->comprobarDinamico();
	if (!d) return;

	const float k1 = 0.5f;
	const float k2 = 0.0f;

	Vector3 diff = _vel - d->getLinearVelocity();// vel relativa al aire
	Vector3 fuerza = k1 * diff + k2 * diff.magnitude() * diff;
	d->addForce(fuerza);
}
