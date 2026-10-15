#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include <array>

#include "Particula.h"
#include "SistemaParticulas.h"
#include "Distribucion.h"
#include "Generador.h"
#include "ParticulaJerarquica.h"

class P2_Scene : public Scene
{
public:
    explicit P2_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
private:
    SistemaParticulas sistema;
};

