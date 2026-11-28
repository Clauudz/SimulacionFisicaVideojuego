#include "EscenaJuego.h"
#include <PxPhysicsAPI.h>
#include <ctype.h>
#include <iostream>

extern physx::PxScene* gScene;// esta definida en main (con extern dices q gScene existe pero no aqui)
extern physx::PxPhysics* gPhysics;

void EscenaJuego::init()
{
	gScene->setGravity(physx::PxVec3(0.0f, 0.0f, 0.0f)); //quitar gravedad por defecto para esta escena

	_sistema = new SistemaSolidoRigido(gPhysics, gScene); //sistema

	//planeta
	Vector3D centro(0.0f, 15.0f, 0.0f);

	_planeta = SistemaSolidoRigido::crearEsferaEstatica(gPhysics, gScene, PxTransform(centro), 2.f, Vector4(1.0f, 0.6f, 0.1f, 1.0f));
	_gravPlaneta = new GravedadPlanetariaSR(centro, 1000.0f, 100.0f, 0.1f);

	//cañon
	Vector3D pos(-30.f, 15.f, 0.f);

	_canon = new Canon(pos, PxPi/36.f, 10.f, 1.f);
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
		Vector3D centro(0.0f, 15.0f, 0.0f);

		SolidoRigido* p = SistemaSolidoRigido::crearCajaDinamica(gPhysics, gScene,
			PxTransform(centro + Vector3D(20.0f, 0.0f, 0.0f)), Vector3D(0.5f, 0.5f, 0.5f), 1.0f,
			Vector4(0.2f, 0.8f, 1.0f, 1.0f), 60.0f);
		p->comprobarDinamico()->setLinearVelocity(Vector3D(0.0f, 0.0f, 7.07f));

		_sistema->agregar(p);
		_sistema->agregarFuerza(_gravPlaneta, p);
		break;
	}
	case 'J': //girar
		_canon->girar(PxPi / 36.f);
		break;
	case 'L': //girar
		_canon->girar(-(PxPi / 36.f));
		break;
	case 'I': //mas impulso
		_canon->cambiarImpulso(1.2f);
		mostrarEstado();
		break;
	case 'K': //menos impulso
		_canon->cambiarImpulso(1.f/1.2f);
		mostrarEstado();
		break;
	case 'M': // mas masa
		_canon->cambiarMasa(1.2f);
		mostrarEstado();
		break;
	case 'N': //menos masa
		_canon->cambiarMasa(1.f/1.2f);
		mostrarEstado();
		break;
	case ' ':
	{
		SolidoRigido* p = SistemaSolidoRigido::crearEsferaDinamica(gPhysics, gScene, PxTransform(_canon->getBoca()), 0.5f, _canon->getMasa(), Vector4(0.7f, 0.1f, 0.34f, 1.0f), 30.f);
		p->comprobarDinamico()->addForce(_canon->getDireccion() * _canon->getImpulso(), PxForceMode::eIMPULSE);

		_sistema->agregar(p);
		_sistema->agregarFuerza(_gravPlaneta, p);
	}
		break;
	default:
		break;
	}
}

void EscenaJuego::cleanup()
{
	delete _sistema; _sistema = nullptr;
	delete _planeta; _planeta = nullptr;
	delete _gravPlaneta; _gravPlaneta = nullptr;
	delete _canon; _canon = nullptr;
	gScene->setGravity(physx::PxVec3(0.0f, -9.8f, 0.0f)); //dejarla como estaba
}

void EscenaJuego::mostrarEstado()
{
	std::cout << "Impulso: " << _canon->getImpulso() << "   Masa: " << _canon->getMasa() << std::endl;
}
