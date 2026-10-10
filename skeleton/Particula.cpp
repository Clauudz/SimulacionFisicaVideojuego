#include "Particula.h"

Particula::Particula(Vector3D posi, Vector3 velo, Vector3D ac, float damp, float mass, double lifeTime) : pos(posi), acc(ac), dampi(damp), posAnt(posi), masa(mass), vel(velo),
	tiempoVida(lifeTime)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.f));
	m_item = new RenderItem(shape, &pos, Vector4(0.3f, 1.f, 0.63f, 1.f));

	m_item->addReference();
}

Particula::~Particula()
{
	m_item->release();
	m_item = nullptr;
}

void Particula::integrate(double d)
{
	pos.p = pos.p + vel * d; // pos.p es la pos en la matriz
	vel = vel + acc * d;

	vel = vel * std::pow(dampi, d);
	acc = Vector3D(0, 0, 0);
	tiempoVida -= d;
}

void Particula::semiIntegrate(double d)
{
	vel = vel + acc * d;
	vel = vel * std::pow(dampi, d);

	pos.p = pos.p + vel * d;	
	acc = Vector3D(0, 0, 0);
	tiempoVida -= d;
}

void Particula::verletIntegrate(double d)
{
	physx::PxTransform prev = pos;

	pos.p = (2.f * pos.p) - posAnt.p + acc * (d * d);
	vel = (pos.p - posAnt.p) * (1.f / (d * 2.f));

	acc = Vector3D(0, 0, 0);

	posAnt = prev;
	tiempoVida -= d;
}

bool Particula::estaViva() const
{
	return tiempoVida > 0;
}
