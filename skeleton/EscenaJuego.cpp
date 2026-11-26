#include "EscenaJuego.h"

#include <ctype.h>

extern physx::PxScene* gScene;// esta definida en main (con extern dices q gScene existe pero no aqui)
extern physx::PxPhysics* gPhysics;

void EscenaJuego::init()
{
	gScene->setGravity(physx::PxVec3(0.0f, 0.0f, 0.0f)); //quitar gravedad por defecto para esta escena

	_sistema = new SistemaSolidoRigido(gPhysics, gScene); //sistema

	//planeta
	Vector3 centro(0.0f, 15.0f, 0.0f);

	_planeta = SistemaSolidoRigido::crearCajaEstatica(gPhysics, gScene, PxTransform(centro), Vector3(1.0f, 1.0f, 1.0f), Vector4(1.0f, 0.6f, 0.1f, 1.0f));
	_gravPlaneta = new GravedadPlanetariaSR(centro, 1000.0f, 100.0f, 0.1f);
}

void EscenaJuego::update(double dt)
{
	_sistema->update(static_cast<float>(dt));
}

void EscenaJuego::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	switch (toupper(key))
	{
	case 'O':
	{
		Vector3 centro(0.0f, 15.0f, 0.0f);

		SolidoRigido* p = SistemaSolidoRigido::crearCajaDinamica(gPhysics, gScene,
			PxTransform(centro + Vector3(20.0f, 0.0f, 0.0f)), Vector3(0.5f, 0.5f, 0.5f), 1.0f,
			Vector4(0.2f, 0.8f, 1.0f, 1.0f), 60.0f);
		p->comprobarDinamico()->setLinearVelocity(Vector3(0.0f, 0.0f, 7.07f));

		_sistema->agregar(p);
		_sistema->agregarFuerza(_gravPlaneta, p);
		break;
	}
	default:
		break;
	}
}

void EscenaJuego::cleanup()
{
	delete _sistema; _sistema = nullptr;
	delete _planeta; _planeta = nullptr;
	delete _gravPlaneta; _gravPlaneta = nullptr;
	gScene->setGravity(physx::PxVec3(0.0f, -9.8f, 0.0f)); //dejarla como estaba
}
