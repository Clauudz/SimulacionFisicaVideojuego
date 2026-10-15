#include "P2_Scene.h"

void P2_Scene::init()
{
	////manguera
	//Distribucion* dM1 = new DistribucionGaussiana(1.f, 0.3f); // dist
	//Distribucion* dM2 = new DistribucionGaussiana(5.f, 0.4f); //dVel
	//Distribucion* dM3 = new DistribucionGaussiana(0.f, 0.05f); // dPos
	//Distribucion* dM4 = new DistribucionGaussiana(2.f, 0.3f); // tVida

	//physx::PxTransform posManguera(physx::PxVec3(0.0f, 0.0f, 0.0f));
	//Generador* genManguera = new Generador(0.99f, 1.f, Vector3D(0, 4.f, 2.f), posManguera, dM1, dM2, dM3, dM4);

	//sistema.addGenerador(genManguera);

	//niebla
	//Distribucion* dN1 = new DistribucionGaussiana(1.f, 0.3f); // dist
	//Distribucion* dN2 = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	//Distribucion* dN3 = new DistribucionGaussiana(0.f, 5.f); // dPos
	//Distribucion* dN4 = new DistribucionGaussiana(1.f, 0.3f); // tVida // cambias la duracion (+lluvia y -niebla)

	//physx::PxTransform posNiebla(physx::PxVec3(0.0f, 20.0f, 0.0f));
	//Generador* genNiebla = new Generador(0.99f, 1.f, Vector3D(0, 6.f, 0.01f), posNiebla, dN1, dN2, dN3, dN4); // cambias la velocidad en y para q le afecte mas o menos la
	//																									 // gravedad y sea como lluvia o niebla
	//sistema.addGenerador(genNiebla);

	//explosion
	//Distribucion* dE1 = new DistribucionGaussiana(100.f, 0.3f); // dist
	//Distribucion* dE2 = new DistribucionGaussiana(0.f, 7.f); //dVel
	//Distribucion* dE3 = new DistribucionGaussiana(0.f, 0.1f); // dPos
	//Distribucion* dE4 = new DistribucionGaussiana(0.8f, 0.2f); // tVida

	//physx::PxTransform posExplosion(physx::PxVec3(0.0f, 50.0f, 0.0f));
	//Generador* genExplosion = new Generador(0.99f, 1.f, Vector3D(0, 0.02f, 0.01f), posExplosion, dE1, dE2, dE3, dE4);
	//
	//std::vector<Particula*> par = genExplosion->generar(0.0);
	//sistema.addParticulas(par);

	//fuegos artificiales
	Distribucion* dF1 = new DistribucionGaussiana(0.f, 7.f); //dVel
	Distribucion* dF2 = new DistribucionGaussiana(25.f, 0.3f); // cantidad

	ParticulaJerarquica* p = new ParticulaJerarquica(Vector3D(0.0f, 10.0f, 0.0f), Vector3D(0, 25.f, 0.01f), Vector3D(0.f,0.f,0.f), 0.99f, 1.f, 1.5, 1, dF1, dF2);

	sistema.addParticulas({p});
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
