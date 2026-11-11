#pragma once
#include "Particula.h"

#include <iostream>
#include <cmath>
#include <float.h>

class ForceGenerator {
protected:
	bool activo = true;
public:
	virtual ~ForceGenerator() = default;
	virtual void aplicaFuerzaAhora(Particula* par, double tTotal) = 0;

	void setActivo(bool a) { activo = a; }
	void toggle() { activo = !activo; }
	bool estaActivo() const { return activo; }
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

class MuelleGenerator : public ForceGenerator {
protected:
	double k;
	double reposo;
	Particula* other;

	void aplicaMuelle(Particula* par, const Vector3D& destino) {
		Vector3D d = destino - Vector3D(par->getPos().p);
		float longitud = d.magnitude();
		if (longitud < 1e-6f) return;
		par->aplicarFuerza(d.normalize() * ((longitud - reposo) * k));
	}
public:
	MuelleGenerator(double _k, double repo, Particula* otra) : k(_k), reposo(repo), other(otra) {}
	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		aplicaMuelle(par, other->getPos().p);
	}
	inline void setK(double nuevaK) { k = nuevaK; }
	float getK() const { return k; }
};

class MuelleAncladoGenerator : public MuelleGenerator {
private:
	Vector3D ancla;
	physx::PxTransform anclaT;
	RenderItem* anclaItem;
public:
	MuelleAncladoGenerator(float k, float longReposo, Vector3D posAncla) : MuelleGenerator(k, longReposo, nullptr), ancla(posAncla),
		anclaT(physx::PxVec3(posAncla.x, posAncla.y, posAncla.z))
	{
		anclaItem = new RenderItem(CreateShape(physx::PxBoxGeometry(0.5f, 0.5f, 0.5f)), &anclaT, Vector4(1.f, 0.f, 0.f, 1.f));
	}
	~MuelleAncladoGenerator() { anclaItem->release(); }

	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		aplicaMuelle(par, ancla);
	}
};

// solo tira al estirarse
class GomaElasticaGenerator : public MuelleGenerator
{
public:
	GomaElasticaGenerator(float k, float longReposo, Particula* otra)
		: MuelleGenerator(k, longReposo, otra) {
	}

	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		Vector3D d = other->getPos().p - par->getPos().p;
		if (d.magnitude() > reposo)
			aplicaMuelle(par, other->getPos().p);
	}
};

//fuerza al pulsar una tecla
class ImpulsoGenerator : public ForceGenerator
{
private:
	Vector3D fuerza;
	double duracion;
	double tInicio;
public:
	ImpulsoGenerator(Vector3D f, double dur) : fuerza(f), duracion(dur), tInicio(-1e9) {}

	void disparar(double tActual) { tInicio = tActual; }

	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		if (tTotal - tInicio < duracion)
			par->aplicarFuerza(fuerza);
	}
};

class FlotacionGenerator : public ForceGenerator {
private:
	float h0; //nivel del agua
	float altura;// lado del cubo
	float volumen;
	float densidad;
	physx::PxTransform aguaT;
	RenderItem* aguaItem;
public:
	FlotacionGenerator(float nivelAgua, float alturaObj, float vol, float densidadL = 1000.f) : h0(nivelAgua), altura(alturaObj), volumen(vol), densidad(densidadL),
		aguaT(physx::PxVec3(0.f, nivelAgua, 0.f)) {
		aguaItem = new RenderItem(CreateShape(physx::PxBoxGeometry(30.f, 0.05f, 30.f)), &aguaT, Vector4(0.f, 0.3f, 1.f, 1.f));
	}
	~FlotacionGenerator() { aguaItem->release(); }

	void setVolumen(float vol) { volumen = vol; }
	float getVolumen() const { return volumen; }
	void setDensidad(float d) { densidad = d; }

	void aplicaFuerzaAhora(Particula* par, double tTotal) override {
		float h = par->getPos().p.y;
		float inmerso;

		if (h - h0 > altura * 0.5) inmerso = 0.f;
		else if (h0 - h > altura * 0.5) inmerso = 1.f;
		else inmerso = (h0 - h) / altura + 0.5;
		par->aplicarFuerza({ 0.f, densidad * volumen * inmerso * 9.8f, 0.f });
	}
};