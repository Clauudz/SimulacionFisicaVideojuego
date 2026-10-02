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
		balas.push_back(new Proyectil(camera.p, cameraDir * 380.f, cameraDir * 50.f, 10.f));
		break;
	}
}

void P1_Scene::cleanup()
{
	for (Proyectil* par : balas) {
		delete par;
	}
}
