#include "SolidoRigido.h"

SolidoRigido::SolidoRigido(PxRigidActor* actor, RenderItem* renderItem, const std::string& nombre, float vidaMax)
{
	_actor = actor;
	_renderItem = renderItem;
	_nombre = nombre;
	_vida = 0.0f;
	_vidaMax = vidaMax;
}

SolidoRigido::~SolidoRigido()
{
	_renderItem->release();
	_actor->release();
}

void SolidoRigido::aplicarParPuro(Vector3 par)
{
	PxRigidDynamic* d = comprobarDinamico();
	if (d) d->addTorque(par);
}

void SolidoRigido::bloquearTraslacion()
{
	PxRigidDynamic* d = comprobarDinamico();
	if (d) d->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_X | PxRigidDynamicLockFlag::eLOCK_LINEAR_Y | PxRigidDynamicLockFlag::eLOCK_LINEAR_Z);
}

Vector3 SolidoRigido::calcularInerciaCaja(float masa, Vector3 mitades)
{
	float ladoX = 2.f * mitades.x;
	float ladoY = 2.f * mitades.y;
	float ladoZ = 2.f * mitades.z;

	float Ix = masa / 12.f * (ladoY * ladoY + ladoZ * ladoZ);
	float Iy = masa / 12.f * (ladoX * ladoX + ladoZ * ladoZ);
	float Iz = masa / 12.f * (ladoX * ladoX + ladoY * ladoY);

	return Vector3(Ix, Iy, Iz);
}
