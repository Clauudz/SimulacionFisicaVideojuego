#include "P4_Scene.h"

void P4_Scene::init()
{
	//// 1
	//ForceGenerator* g1 = new GravedadGenerator({ 0.f,-10.f,0.f }); //gravedad
	//muelle = new MuelleAncladoGenerator(k, 10.f, { 0.f,40.f,0.f });
	//impulso = new ImpulsoGenerator({ 100.f,0.f,0.f }, 0.2);

	//Particula* p1 = new Particula({ 0.f, 30.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, 1.f, 1000.0);
	//p1->addFuerza(g1);
	//p1->addFuerza(muelle);
	//p1->addFuerza(impulso);

	//sistema.addParticulas({p1});
	//sistema.addForceGenerator(g1);
	//sistema.addForceGenerator(muelle);
	//sistema.addForceGenerator(impulso);
}

void P4_Scene::update(double dt)
{
	sistema.update(dt);
}

void P4_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	/*switch (key) {
	case 'f': impulso->disparar(sistema.getTiempoTotal()); break;
	case '+': k *= 2.f; muelle->setK(k); std::cout << "k = " << k << std::endl; break;
	case '-': k = fmax(1.f, k / 2.f); muelle->setK(k); std::cout << "k = " << k << std::endl; break;
	case 'e': euler = !euler; sistema.setEuler(euler);
		std::cout << (euler ? "Euler explicito" : "Euler semi-implicito") << std::endl; break;
	}*/
}

void P4_Scene::cleanup()
{
}
