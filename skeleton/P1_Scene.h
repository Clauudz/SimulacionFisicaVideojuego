#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include <array>
#include "Particula.h"

class P1_Scene : public Scene
{
public:
    explicit P1_Scene(std::string name) : Scene(std::move(name)), par({0,0,0}, {0, 5000, 0}, 0.99f) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;

private:
    Particula par;
};

