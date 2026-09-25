#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include <array>

class P0_Scene : public Scene
{
public:
    explicit P0_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;

private:
    physx::PxTransform m_transform;
    RenderItem* m_renderItem{ nullptr };

    // Reto A:
    physx::PxTransform m_tX, m_tY, m_tZ;
    RenderItem* m_itemX = nullptr;
    RenderItem* m_itemY = nullptr;
    RenderItem* m_itemZ = nullptr;

    // Reto B:
    static const int N_TARGETS = 4;

    std::array<physx::PxTransform, N_TARGETS> m_targetT;
    std::array<RenderItem*, N_TARGETS> m_targetItems{};

    // Reto C:
    static const int N_BALLS = 10;

    std::array<physx::PxTransform, N_BALLS> m_lerpT;
    std::array<RenderItem*, N_BALLS> m_lerpItems{};

    physx::PxTransform m_tA, m_tB;
    RenderItem* m_itemA = nullptr;
    RenderItem* m_itemB = nullptr;
};

