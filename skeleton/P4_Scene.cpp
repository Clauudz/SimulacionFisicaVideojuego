#include "P4_Scene.h"

void P4_Scene::init()
{
	// 1
	//gravedad = new GravedadGenerator({ 0.f,-10.f,0.f }); //gravedad
	//muelle = new MuelleAncladoGenerator(k, 10.f, { 0.f,40.f,0.f });
	//impulso = new ImpulsoGenerator({ 100.f,0.f,0.f }, 0.2);

	//Particula* p1 = new Particula({ 0.f, 30.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, 1.f, 1000.0);
	//p1->addFuerza(g1);
	//p1->addFuerza(muelle);
	//p1->addFuerza(impulso);

	//sistema.addParticulas({p1});
	//sistema.addForceGenerator(g1);
	//sistema.addForceGenerator(muelle);
	//sistema.addForceGenerator(impulso);

	// 2
	//gravedad = new GravedadGenerator({ 0.f, -10.f, 0.f });
	//gravedad->setActivo(false);

	//viento = new VientoGenerator({ 0.f, 0.f, -20.f }, 0.5f, { 0.f, 20.f, 0.f }, 100.f);
	//viento->setActivo(false);

	//impulso = new ImpulsoGenerator({ 0.f, 0.f, 300.f }, 0.2);

	//// Primeras 2 particulas: muelle normal, la distancia inicial 20 > reposo 10 q es cuando esta estirado
	//Particula* a = new Particula({ -20.f, 30.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, 1.f, 1000.0);
	//Particula* b = new Particula({ -20.f, 10.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, 1.f, 1000.0);
	//muelleAB = new MuelleGenerator(k, 10.0, b);
	//muelleBA = new MuelleGenerator(k, 10.0, a);
	//a->addFuerza(muelleAB);
	//b->addFuerza(muelleBA);

	////Segundas 2 particulas: goma elástica con las mismas condiciones para comparar
	//Particula* c = new Particula({ 20.f, 30.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, 1.f, 1000.0);
	//Particula* d = new Particula({ 20.f, 10.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, 1.f, 1000.0);
	//gomaCD = new GomaElasticaGenerator(k, 10.f, d);
	//gomaDC = new GomaElasticaGenerator(k, 10.f, c);
	//c->addFuerza(gomaCD);
	//d->addFuerza(gomaDC);

	//// Fuerzas comunes a todas
	//for (Particula* p : { a, b, c, d }) {
	//	p->addFuerza(gravedad);
	//	p->addFuerza(viento);
	//}
	//// El impulso solo a las de abajo para darle a la goma/muelle
	//b->addFuerza(impulso);
	//d->addFuerza(impulso);

	//sistema.addParticulas({ a, b, c, d });
	//for (ForceGenerator* fg : std::initializer_list<ForceGenerator*>{
	//		muelleAB, muelleBA, gomaCD, gomaDC, gravedad, viento, impulso }) {
	//	sistema.addForceGenerator(fg);
	//}

	// 3
	const float lado = 2.f;

	gravedad = new GravedadGenerator({ 0.f, -9.8f, 0.f });
	flotacion = new FlotacionGenerator(nivelAgua, lado, volumen, densidad);

	//EL rozamiento es viscoso solo dentro del agua y es una esfera muy grande enla q su punto mas alto coincide con la superficie
	// Viento con velocidad 0 = resistencia al movimiento.
	rozamiento = new VientoGenerator({ 0.f, 0.f, 0.f }, 2000.f, { 0.f, nivelAgua - 100.f, 0.f }, 100.f);

	// Cubo empezando por encima del agua para que caiga y oscile
	cubo = new Particula({ 0.f, nivelAgua + 5.f, 0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, 0.99f, masa, 1000.0, true, lado);
	cubo->addFuerza(gravedad);
	cubo->addFuerza(flotacion);
	cubo->addFuerza(rozamiento);

	sistema.addParticulas({ cubo });
	sistema.addForceGenerator(gravedad);
	sistema.addForceGenerator(flotacion);
	sistema.addForceGenerator(rozamiento);

	imprimeEstado();
}

void P4_Scene::update(double dt)
{
	sistema.update(dt);
}

void P4_Scene::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	// switch 1 y 2
	/*switch (key) {
	case 'f': if (impulso) impulso->disparar(sistema.getTiempoTotal()); break;
	case '+': k *= 2.f; aplicaK(); break;
	case '-': k = fmax(1.f, k / 2.f); aplicaK(); break;
	case 'g': if (gravedad) {
		gravedad->toggle();
		std::cout << "gravedad " << (gravedad->estaActivo() ? "ON" : "OFF") << std::endl;
	} break;
	case 'v': if (viento) {
		viento->toggle();
		std::cout << "viento " << (viento->estaActivo() ? "ON" : "OFF") << std::endl;
	} break;
	case 'e': euler = !euler; sistema.setEuler(euler);
		std::cout << (euler ? "euler explicito" : "euler semi-implicito") << std::endl; break;
	}*/

	// switch 3
	switch (key) {
		// masa
	case 'm': masa += 1000.f; cubo->setMass(masa); imprimeEstado(); break;
	case 'n': masa = fmax(100.f, masa - 1000.f); cubo->setMass(masa); imprimeEstado(); break;
		// volumen
	case 'v': volumen += 1.f; flotacion->setVolumen(volumen); imprimeEstado(); break;
	case 'b': volumen = fmax(1.f, volumen - 1.f); flotacion->setVolumen(volumen); imprimeEstado(); break;
		//caso límite directo
	case 'l': masa = densidad * volumen; cubo->setMass(masa); imprimeEstado(); break;
		// rozamiento
	case 'r': rozamiento->toggle();
		std::cout << "rozamiento " << (rozamiento->estaActivo() ? "ON" : "OFF") << std::endl; break;
		//cambiar de líquido
	case 'p': {
		static const float dens[] = { 1000.f, 920.f, 13600.f }; //agua, aceite, mercurio
		static const char* nombres[] = { "agua", "aceite", "mercurio" };
		static int i = 0;
		i = (i + 1) % 3;
		densidad = dens[i];
		flotacion->setDensidad(densidad);
		std::cout << "liquido: " << nombres[i] << std::endl;
		imprimeEstado();
		break;
	}
	case 'e': euler = !euler; sistema.setEuler(euler);
		std::cout << (euler ? "euler explicito" : "euler semi-implicito") << std::endl; break;
	}
}

void P4_Scene::cleanup()
{
}

void P4_Scene::aplicaK()
{
	for (MuelleGenerator* m : std::initializer_list<MuelleGenerator*>{ muelle, muelleAB, muelleBA, gomaCD, gomaDC })
		if (m) m->setK(k);
	std::cout << "k = " << k << std::endl;
}

void P4_Scene::imprimeEstado()
{
	float peso = masa * 9.8f;
	float empujeMax = densidad * volumen * 9.8f;
	std::cout << "m = " << masa << " kg | V = " << volumen << " m3 | rho = " << densidad
		<< " | P = " << peso << " N | Emax = " << empujeMax << " N -> ";
	if (std::abs(peso - empujeMax) < 1e-3f * empujeMax) std::cout << "CASO LIMITE\n";
	else if (peso < empujeMax) std::cout << "FLOTA (" << 100.f * peso / empujeMax << "% sumergido)\n";
	else std::cout << "SE HUNDE\n";
}
