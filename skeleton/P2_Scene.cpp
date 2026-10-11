#include "P2_Scene.h"

void P2_Scene::init()
{
	//manguera
	Particula* pM1 = new Particula(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 0.99f, 1.f, 0.0);

	Distribucion* dM1 = new DistribucionGaussiana(1.f, 0.3f); // dist
	Distribucion* dM2 = new DistribucionGaussiana(1.f, 0.4f); //dVel
	Distribucion* dM3 = new DistribucionGaussiana(0.f, 0.05f); // dPos
	Distribucion* dM4 = new DistribucionGaussiana(2.f, 0.3f); // tVida

	physx::PxTransform posManguera(physx::PxVec3(0.0f, 0.0f, 0.0f));
	Generador* genManguera = new Generador(pM1, Vector3D(0, 4.f, 2.f), posManguera, dM1, dM2, dM3, dM4);

	sistema.addGenerador(genManguera);
}

void P2_Scene::update(double dt)
{
	sistema.update(dt);
}

void P2_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
}

void P2_Scene::cleanup()
{
}
