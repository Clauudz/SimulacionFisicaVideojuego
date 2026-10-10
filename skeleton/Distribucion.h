#pragma once
#include <random>

class Distribucion
{
protected:
	std::mt19937_64 rnd;
public:
	Distribucion() : rnd(std::random_device{}()) {}
	virtual ~Distribucion() = default;
	virtual float siguiente() = 0;
};

class DistribucionUniforme : public Distribucion
{
private:
	std::uniform_real_distribution<float> uniform;
public:
	DistribucionUniforme(float media, float var) : Distribucion(), uniform(media - var, media + var) {}
	float siguiente() override {
		return uniform(rnd);
	}
};

class DistribucionGaussiana : public Distribucion
{
private:
	std::normal_distribution<float> normal;
public:
	DistribucionGaussiana(float media, float desviacion) : Distribucion(), normal(media , desviacion) {}
	float siguiente() override {
		return normal(rnd);
	}
};