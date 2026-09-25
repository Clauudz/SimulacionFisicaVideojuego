#include "P1_Scene.h"

void P1_Scene::init()
{
}

void P1_Scene::update(double dt)
{
	par.verletIntegrate(dt);
}

void P1_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
}

void P1_Scene::cleanup()
{
}
