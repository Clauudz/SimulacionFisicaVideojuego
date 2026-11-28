#pragma once
#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Canon
{
private:
	static constexpr float IMPULSO_MIN = 1.f;
	static constexpr float IMPULSO_MAX = 100.f;
	static constexpr float MASA_MIN = 1.f;
	static constexpr float MASA_MAX = 1000.f;

	physx::PxTransform pos;
	float angulo;
	float impulso;
	float masa;

	RenderItem* m_item = nullptr;

	void actualizarOrientacion();

public:
	Canon(Vector3D position, float angle, float impulse, float mass);
	~Canon();

	void girar(float delta);
	Vector3D getDireccion() const;
	Vector3D getBoca();

	float getImpulso() const { return impulso; }
	float getMasa() { return masa; }

	void cambiarImpulso(float factor);
	void cambiarMasa(float factor);
};

