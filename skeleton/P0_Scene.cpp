#include "P0_Scene.h"

void P0_Scene::init()
{
    // Ejemplo: Creación de una esfera usando las utilidades de render existentes
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(3.0f));
    m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

    // Se registra el RenderItem exactamente como en la plantilla original
    m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 0.0f, 1.0f, 1.0f));
}

void P0_Scene::update(double dt)
{
}

void P0_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{

}

void P0_Scene::cleanup()
{
    if (m_renderItem) {
        m_renderItem->release(); // Deregistra y destruye el item
        m_renderItem = nullptr;
    }
}
