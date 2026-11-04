#include "P3_Scene.h"
#include <iostream>

void P3_Scene::init()
{
	gravedad = new GravedadGenerator({ 0.f, -10.f, 0.f }); // g
	flotabilidad = new GravedadGenerator({ 0.f, 1.5f, 0.f }); // b
	viento = new VientoGenerator({ 5.f, 0.f, 0.f }, 2.f, { 0.f, 20.f, 0.f }, 15.f); // v
	torbellino = new TorbellinoGenerator(2.f, { 0.f, 20.f, 0.f }, 20.f, 0.5f, 10.f); // t

	// niebla o lluvia. Actividad 1
	//Distribucion* dN1g = new DistribucionGaussiana(1.f, 0.3f); // dist
	//Distribucion* dN2g = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	//Distribucion* dN3g = new DistribucionGaussiana(0.f, 5.f); // dPos
	//Distribucion* dN4g = new DistribucionGaussiana(5.f, 0.3f); // tVida // cambias la duracion (+lluvia y -niebla)

	//Distribucion* dN1n = new DistribucionGaussiana(10.f, 0.3f); // dist
	//Distribucion* dN2n = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	//Distribucion* dN3n = new DistribucionGaussiana(0.f, 5.f); // dPos
	//Distribucion* dN4n = new DistribucionGaussiana(0.1f, 0.3f);

	//physx::PxTransform posLluvia(physx::PxVec3(0.0f, 20.0f, 0.0f));
	//physx::PxTransform posNiebla(physx::PxVec3(50.0f, 20.0f, 0.0f));

	//Generador* genLluvia = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posLluvia, dN1g, dN2g, dN3g, dN4g, { gravedad }); // cambias la velocidad en y para q le afecte mas o menos la
	//																									 // gravedad y sea como lluvia o niebla
	//Generador* genNiebla = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posNiebla, dN1n, dN2n, dN3n, dN4n, { flotabilidad });
	//sistema.addGenerador(genLluvia);
	//sistema.addGenerador(genNiebla);

	// particulas con viento. Ejercicio 2
	//Particula* p1 = new Particula({-2.f, 50.f, 0.f}, {0.f,0.f,0.f}, {0.f,0.f,0.f}, 0.99f, 1.f, 1000.0);
	//Particula* p2 = new Particula({2.f, 50.f, 0.f}, {0.f,0.f,0.f}, {0.f,0.f,0.f}, 0.99f, 10.f, 1000.0);

	//p1->addFuerza(gravedad);
	//p1->addFuerza(viento);

	//p2->addFuerza(gravedad);
	//p2->addFuerza(viento);

	//sistema.addParticulas({ p1, p2 });

	// tornado. Ejercicio 3
	Distribucion* dN1n2 = new DistribucionGaussiana(5.f, 0.3f); // dist
	Distribucion* dN2n2 = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	Distribucion* dN3n2 = new DistribucionGaussiana(2.f, 5.f); // dPos
	Distribucion* dN4n2 = new DistribucionGaussiana(5.f, 0.3f); // dTime

	physx::PxTransform posNiebla2(physx::PxVec3(0.0f, 20.0f, 0.0f));
	Generador* genNiebla2 = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posNiebla2, dN1n2, dN2n2, dN3n2, dN4n2, { torbellino, gravedad });

	sistema.addGenerador(genNiebla2);

	//explosion. Ejercicio 4
	//Distribucion* dN1n3 = new DistribucionGaussiana(3.f, 0.3f); // dist
	//Distribucion* dN2n3 = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	//Distribucion* dN3n3 = new DistribucionGaussiana(2.f, 5.f); // dPos
	//Distribucion* dN4n3 = new DistribucionGaussiana(3.f, 0.3f); // dTime

	//physx::PxTransform posNiebla3(physx::PxVec3(0.0f, 20.0f, 0.0f));
	//Generador* genNiebla3 = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posNiebla3, dN1n3, dN2n3, dN3n3, dN4n3, { gravedad });

	//sistema.addGenerador(genNiebla3);
}

void P3_Scene::update(double dt)
{
	sistema.update(dt);
}

void P3_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	switch (key) {
	case 'g': gravedad->toggle(); break;
	case 'b': flotabilidad->toggle(); break;
	case 'v': viento->toggle(); break;
	case 't': torbellino->toggle(); break;
	case 'e': sistema.dispararExplosion({ 0.0f,20.f,0.0f }, 2500.f, 25.f, 1.5f); break;
	}
}

void P3_Scene::cleanup()
{
}
