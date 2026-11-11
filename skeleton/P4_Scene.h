#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include <array>
#include <algorithm>

#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "Distribucion.h"
#include "Generador.h"

class P4_Scene : public Scene
{
public:
    explicit P4_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
private:
    SistemaParticulas sistema;

    // actividad 1
    MuelleAncladoGenerator* muelle = nullptr;

    //actividad 2
    MuelleGenerator* muelleAB = nullptr;//fuerza sobre A, hacia B
    MuelleGenerator* muelleBA = nullptr; //fuerza sobre B, hacia A
    GomaElasticaGenerator* gomaCD = nullptr;//fuerza sobre C, hacia D
    GomaElasticaGenerator* gomaDC = nullptr; //fuerza sobre D, hacia C

    GravedadGenerator* gravedad = nullptr;
    VientoGenerator* viento = nullptr;
    ImpulsoGenerator* impulso = nullptr;

    float k = 10.f;
    bool euler = false;

    void aplicaK();

    // Actividad 3
    FlotacionGenerator* flotacion = nullptr;
    VientoGenerator* rozamiento = nullptr;   // opcional: rozamiento del líquido
    Particula* cubo = nullptr;
    float masa = 4000.f;
    float volumen = 8.f;
    float densidad = 1000.f;
    float nivelAgua = 20.f;

    void imprimeEstado();
};
