#pragma once
#include "Particula.h"

#include <iostream>
#include <cmath>
#include <float.h>

class ForceGenerator {
public:
	virtual ~ForceGenerator() = default;
	virtual void aplicaFuerzaAhora(Particula* par, double tTotal) = 0;
};

class GravedadGenerator : public ForceGenerator
{
private:
	Vector3D gravedad;
public:
	GravedadGenerator(Vector3D g) : gravedad(g) {}
	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		Vector3D fuerza = gravedad * par->getMass();
		par->aplicarFuerza(fuerza);
	}
};

class VientoGenerator : public ForceGenerator
{
private:
	Vector3D velViento;
	float k1;
	float k2;
protected:
	Vector3D centro;
	float radio;
public:
	VientoGenerator(Vector3D vViento, float k1, Vector3D c, float r, float k2 = 0.f) : velViento(vViento), k1(k1), centro(c), radio(r), k2(k2) {}
	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		Vector3D dist = par->getPos().p - centro;

		if (dist.magnitude() < radio) {
			Vector3D velResultante = velocidadEfectiva(par->getPos().p) - par->getVel();
			Vector3D fuerza = (velResultante * k1) + (velResultante * velResultante.magnitude() * k2);
			par->aplicarFuerza(fuerza);
		}
	}

	virtual Vector3D velocidadEfectiva(Vector3D posParticula) {
		return velViento;
	}
};

class TorbellinoGenerator : public VientoGenerator
{
private:
	float K;
	float fuerzaVertical;
public:
	TorbellinoGenerator(float k1, Vector3D c, float r, float intensidad, float fVertical) : VientoGenerator({0,0,0}, k1, c, r),
		K(intensidad), fuerzaVertical(fVertical) {}
	Vector3D velocidadEfectiva(Vector3D posParticula) override {
		Vector3D diff = posParticula - centro;
		return Vector3D(-diff.z, fuerzaVertical - diff.y, diff.x) * K;
	}
};

class ExplosionGenerator : public ForceGenerator
{
private:
	float K;
	Vector3D centro;
	float R;
	double tau;
	double tInicio;

public:
	ExplosionGenerator(float intensidad, Vector3D c, float r, double tConst, double tIni) :
		K(intensidad), centro(c), R(r), tau(tConst), tInicio(tIni) {}
	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		Vector3D diff = par->getPos().p - centro;
		float r = diff.magnitude();
		if (r < R) {
			double t = tTotal - tInicio;
			Vector3D fuerza = diff.normalize() * K / (r * r) * std::exp( - (t / tau));
			par->aplicarFuerza(fuerza);
		}
	}
};