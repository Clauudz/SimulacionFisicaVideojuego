#include "P1_Scene.h"
#include <iostream>

void P1_Scene::init()
{
}

void P1_Scene::update(double dt)
{
	for (Proyectil* par : balas) {
		par->semiIntegrate(dt, 0.0);
	}
}

void P1_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	Vector3D cameraDir = GetCamera()->getDir().getNormalized();
	switch (key) {
	case 'p' :
		//dessert eagle
		balas.push_back(new Proyectil(camera.p, cameraDir * vel, cameraDir * 30.f, 0.019f, 0.99f));
		break;
	case 'o':
		//cañon
		balas.push_back(new Proyectil(camera.p, cameraDir * vel, cameraDir * 50.f, 16.3f, 0.99f));
		break;
	case 'i':
		//cañon de riel
		balas.push_back(new Proyectil(camera.p, cameraDir * vel, cameraDir * 70.f, 3.2f, 0.99f));
		break;
	case 'm':
		sumaVel();
		std::cout << "Velocidad sumada, ahora: " << vel << std::endl;
		break;
	case 'n':
		restaVel();
		std::cout << "Velocidad restada, ahora: " << vel << std::endl;
		break;
	}
}

void P1_Scene::cleanup()
{
	for (Proyectil* par : balas) {
		delete par;
	}
}
