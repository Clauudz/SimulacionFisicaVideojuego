#include "P3_Scene.h"

void P3_Scene::init()
{
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

	//ForceGenerator* g1 = new GravedadGenerator({ 0.f,-10.f,0.f }); //gravedad
	//ForceGenerator* g2 = new GravedadGenerator({ 0.f,1.5f,0.f }); //flotabilidad

	//Generador* genLluvia = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posLluvia, dN1g, dN2g, dN3g, dN4g, {g1}); // cambias la velocidad en y para q le afecte mas o menos la
	//																									 // gravedad y sea como lluvia o niebla
	//Generador* genNiebla = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posNiebla, dN1n, dN2n, dN3n, dN4n, { g2 });
	//sistema.addGenerador(genLluvia);
	//sistema.addGenerador(genNiebla);

	// particulas con viento. Ejercicio 2
	//ForceGenerator* g3 = new GravedadGenerator({ 0.f,-10.f,0.f }); //gravedad
	//ForceGenerator* g4 = new VientoGenerator({ 5.f, 0.0f, 0.0f }, 2.f, { 0.f, 20.f, 0.f }, 15.f); //viento

	//Particula* p1 = new Particula({-2.f, 50.f, 0.f}, {0.f,0.f,0.f}, {0.f,0.f,0.f}, 0.99f, 1.f, 1000.0);
	//Particula* p2 = new Particula({2.f, 50.f, 0.f}, {0.f,0.f,0.f}, {0.f,0.f,0.f}, 0.99f, 10.f, 1000.0);

	//p1->addFuerza(g3);
	//p1->addFuerza(g4);

	//p2->addFuerza(g3);
	//p2->addFuerza(g4);

	//sistema.addParticulas({ p1, p2 });

	// tornado. Ejercicio 3
	//Distribucion* dN1n2 = new DistribucionGaussiana(5.f, 0.3f); // dist
	//Distribucion* dN2n2 = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	//Distribucion* dN3n2 = new DistribucionGaussiana(2.f, 5.f); // dPos
	//Distribucion* dN4n2 = new DistribucionGaussiana(5.f, 0.3f); // dTime

	//physx::PxTransform posNiebla2(physx::PxVec3(0.0f, 20.0f, 0.0f));

	//ForceGenerator* g5 = new TorbellinoGenerator(2.f, { 0.0f,20.f,0.0f }, 20.f, 0.5f, 10.f); //torbellino
	//ForceGenerator* g6 = new GravedadGenerator({ 0.f,-10.f,0.f }); //gravedad
	//Generador* genNiebla2 = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posNiebla2, dN1n2, dN2n2, dN3n2, dN4n2, { g5, g6 });

	//sistema.addGenerador(genNiebla2);

	//explosion. Ejercicio 4
	Distribucion* dN1n3 = new DistribucionGaussiana(3.f, 0.3f); // dist
	Distribucion* dN2n3 = new DistribucionGaussiana(0.02f, 0.03f); //dVel
	Distribucion* dN3n3 = new DistribucionGaussiana(2.f, 5.f); // dPos
	Distribucion* dN4n3 = new DistribucionGaussiana(3.f, 0.3f); // dTime

	physx::PxTransform posNiebla3(physx::PxVec3(0.0f, 20.0f, 0.0f));

	ForceGenerator* g7 = new GravedadGenerator({ 0.f,0.f,0.f }); //gravedad
	Generador* genNiebla3 = new Generador(0.99f, 1.f, Vector3D(0, 1.f, 0.01f), posNiebla3, dN1n3, dN2n3, dN3n3, dN4n3, { g7 });

	sistema.addGenerador(genNiebla3);
}

void P3_Scene::update(double dt)
{
	sistema.update(dt);
}

void P3_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	switch (key) {
	case 'e':
		sistema.dispararExplosion({ 0.0f,20.f,0.0f }, 2500.f, 25.f, 1.5f);
		break;
	}
}

void P3_Scene::cleanup()
{
}
