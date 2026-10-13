#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include <array>
#include "Particula.h"
#include "Proyectil.h"

class P1_Scene : public Scene
{
public:
    explicit P1_Scene(std::string name) : Scene(std::move(name)), vel(400.f) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;

private:
    std::vector<Proyectil*> balas;
    int vel;

    void sumaVel() { vel += 50.f; }
    void restaVel() { vel -= 50.f; }
};

