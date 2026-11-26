#pragma once
#include "Practica5/GeneradorFuerzaSR.h"
#include "Vector3D.h"

class GravedadPlanetariaSR : public GeneradorFuerzaSR
{
private:
	Vector3D centro; //centro del planeta
	float masa; //masa del planeta
	float radio; //radio de influencia (mas lejos de eso no atrae)
	float epsilon; //suavizado

	static constexpr float G = 1.f; //se usa 1 en unidades del juego, y la intensidad de cada planeta se ajusta mediante su masa
public:
	GravedadPlanetariaSR(Vector3D center, float mass, float radius, float e);
	void updateForce(SolidoRigido* solido) override;
};

