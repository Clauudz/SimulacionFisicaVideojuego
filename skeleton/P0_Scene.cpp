#include "P0_Scene.h"

void P0_Scene::init()
{
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.f));
    /*m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
    m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));*/

    /*// Ejemplo: Creación de una esfera usando las utilidades de render existentes
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(3.0f));
    m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

    // Se registra el RenderItem exactamente como en la plantilla original
    m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 0.0f, 1.0f, 1.0f));*/

    // reto a

    /*Vector3D u(3.0f, 1.0f, 0.0f);
    Vector3D v(0.0f, 4.0f, 0.0f);
    Vector3D w = u.cross(v);

    Vector3D X = u.normalize() * 5.f;
    Vector3D Y = v.normalize() * 5.f;
    Vector3D Z = w.normalize() * 5.f;

    m_tX = physx::PxTransform(X); //pq usa directamente el operador de pxVec3D a vec3D, por eso deja
    m_tY = physx::PxTransform(Y);
    m_tZ = physx::PxTransform(Z);

    m_itemX = new RenderItem(shape, &m_tX, Vector4(1, 0, 0, 1)); // rojo
    m_itemY = new RenderItem(shape, &m_tY, Vector4(0, 1, 0, 1)); // verde
    m_itemZ = new RenderItem(shape, &m_tZ, Vector4(0, 0, 1, 1)); // azul*/

    //reto b

    /*Vector3D enemyPos(0.0f, 0.0f, 0.0f);
    Vector3D D(0.0f, 0.0f, 1.0f);

    Vector3D targets[N_TARGETS] = {
        Vector3D(2.0f, 0.0f,  3.0f),
        Vector3D(-4.0f, 0.0f,  1.0f),
        Vector3D(0.0f, 0.0f, -5.0f),
        Vector3D(3.0f, 0.0f,  0.0f)
    };


    for (int i = 0; i < N_TARGETS; i++) {
        float d = D.dot(targets[i]);

        Vector4 color;
        if (d > 0.f) color = Vector4(0, 1, 0, 1);   // verde
        else if (d < 0.f) color = Vector4(1, 0, 0, 1);    //rojo
        else color = Vector4(1, 1, 0, 1);   //amarillo

        m_targetT[i] = physx::PxTransform(targets[i]);
        m_targetItems[i] = new RenderItem(shape, &m_targetT[i], color);
    }*/

    // reto c

    Vector3D A(-8.0f, 1.0f, -8.0f);
    Vector3D B(8.0f, 8.0f, 8.0f);
    Vector3D AB = B - A;

    m_tA = physx::PxTransform(A); //pq usa directamente el operador de pxVec3D a vec3D, por eso deja
    m_tB = physx::PxTransform(B);

    m_itemA = new RenderItem(shape, &m_tA, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    m_itemB = new RenderItem(shape, &m_tB, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

    for (int i = 0; i < N_BALLS; i++) {
        float t = (i + 1) / float(N_BALLS + 1);
        Vector3D P = A + (AB * t);

        m_lerpT[i] = physx::PxTransform(P);
        m_lerpItems[i] = new RenderItem(shape, &m_lerpT[i], Vector4(0, 1, 0, 1));
    }

}

void P0_Scene::update(double dt)
{
}

void P0_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{

}

void P0_Scene::cleanup()
{
   /* if (m_renderItem) {
        m_renderItem->release(); // Deregistra y destruye el item
        m_renderItem = nullptr;
    }*/

    /*if (m_itemX) { m_itemX->release(); m_itemX = nullptr; }
    if (m_itemY) { m_itemY->release(); m_itemY = nullptr; }
    if (m_itemZ) { m_itemZ->release(); m_itemZ = nullptr; }*/

    /*for (auto& it : m_targetItems) {
        if (it) { it->release(); it = nullptr; }
    }*/

    for (auto& it : m_lerpItems) {
        if (it) { it->release(); it = nullptr; }
    }

    if (m_itemA) { m_itemA->release(); m_itemA = nullptr; }
    if (m_itemB) { m_itemB->release(); m_itemB = nullptr; }
}
