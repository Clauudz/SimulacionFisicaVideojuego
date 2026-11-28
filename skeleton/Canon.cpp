#include "Canon.h"

#include <algorithm>
#include <cmath>

Canon::Canon(Vector3D position, float angle, float impulse, float mass) : pos(position), angulo(angle), impulso(impulse), masa(mass)
{
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(2.f, 0.4f, 0.4f)); // cañon
	m_item = new RenderItem(shape, &pos, Vector4(0.7f, 0.7f, 0.75f, 1.f));

	actualizarOrientacion();
}

Canon::~Canon()
{
	m_item->release();
	m_item = nullptr;
}

void Canon::actualizarOrientacion()
{
	pos.q = physx::PxQuat(0.f, 0.f, sin(angulo/2.f), cos(angulo / 2.f));
}

void Canon::girar(float delta)
{
	angulo += delta;
	actualizarOrientacion();
}

Vector3D Canon::getDireccion() const
{
	Vector3D P(1.f, 0.f, 0.f);
	return pos.q.rotate(P);
}

Vector3D Canon::getBoca()
{
	return getDireccion() * 2.5f + pos.p;
}

void Canon::cambiarImpulso(float factor)
{
	impulso *= factor;
	impulso = std::clamp(impulso, IMPULSO_MIN, IMPULSO_MAX);
}

void Canon::cambiarMasa(float factor)
{
	masa *= factor;
	masa = std::clamp(masa, MASA_MIN, MASA_MAX);
}
