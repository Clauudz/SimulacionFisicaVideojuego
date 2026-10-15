#include "ParticulaJerarquica.h"

ParticulaJerarquica::ParticulaJerarquica(Vector3D posi, Vector3D velo, Vector3D ac, float damp, float mass,
	double lifeTime, int nivel, Distribucion* velHijas, Distribucion* cantidadHijas) :
	Particula(posi, velo, ac, damp, mass, lifeTime), nivel(nivel), vHijas(velHijas), cantHijas(cantidadHijas)
{
}

std::vector<Particula*> ParticulaJerarquica::generarHijas()
{
	std::vector<Particula*> hijas;
	if (nivel >= NIVEL_MAXIMO) return hijas;

	int nHijas = std::max<float>(0.f, std::round(cantHijas->siguiente()));
	for (int i = 0; i < nHijas; i++) {
		Vector3D vFinal = Vector3D(vel.x + vHijas->siguiente(), vel.y + vHijas->siguiente(), vel.z + vHijas->siguiente());

		ParticulaJerarquica* parti = new ParticulaJerarquica(pos.p, vFinal, Vector3D(0.f, 0.f, 0.f), dampi, masa, 0.8f, nivel+1, vHijas, cantHijas);
		hijas.push_back(parti);
	}

	return hijas;
}
