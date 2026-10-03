#include "P1_Scene.h"

void P1_Scene::init()
{
}

void P1_Scene::update(double dt)
{
	for (Proyectil* par : balas) {
		par->semiIntegrate(dt);
	}
}

void P1_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	Vector3D cameraDir = GetCamera()->getDir().getNormalized();
	switch (key) {
	case 'p' :
		//dessert eagle
		balas.push_back(new Proyectil(camera.p, cameraDir * 380.f, cameraDir * 50.f, 10.f, 0.77f));
		break;
	case 'o':
		//cañon
		balas.push_back(new Proyectil(camera.p, cameraDir * 400.f, cameraDir * 50.f, 10000.f, 0.89f));
		break;
	case 'i':
		//cañon de riel
		balas.push_back(new Proyectil(camera.p, cameraDir * 2000.f, cameraDir * 50.f, 320.f, 0.99f));
		break;
	}
}

void P1_Scene::cleanup()
{
	for (Proyectil* par : balas) {
		delete par;
	}
}
