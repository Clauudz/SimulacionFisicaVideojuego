#pragma once
#include "Scene.h"
#include "Practica5/SolidoRigido.h"
#include "Practica5/SistemaSolidoRigido.h"
#include "GravedadPlanetariaSR.h"
#include "Canon.h"

using namespace physx;

class EscenaJuego : public Scene
{
public:
    explicit EscenaJuego(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;

private:
    GravedadPlanetariaSR* _gravPlaneta = nullptr;
    SolidoRigido* _planeta = nullptr;
    SistemaSolidoRigido* _sistema = nullptr;
    Canon* _canon;

    void mostrarEstado();
};

