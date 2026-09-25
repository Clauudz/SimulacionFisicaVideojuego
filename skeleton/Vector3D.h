#pragma once
#include "PxPhysicsAPI.h"
#include <cmath>

class Vector3D
{
public:
	float x, y, z;

	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3D(const physx::PxVec3& v) : x(v.x), y(v.y), z(v.z) {}

	float magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	};

	Vector3D normalize() const {
		float m = magnitude();
		if (m == 0.0f) return Vector3D(0, 0, 0); //evitas dividir entre 0
		return Vector3D(x / m, y / m, z / m);
	};

	float dot(const Vector3D& v) const {		
		return x * v.x + y * v.y + z * v.z;
	};

	Vector3D cross(const Vector3D& v) const {
		return Vector3D(y * v.z - v.y * z,
			-(x * v.z - v.x * z),
			x * v.y - v.x * y);
	};

	Vector3D& operator=(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	Vector3D operator*(float n) const {
		return Vector3D(x * n, y * n, z * n);
	}

	Vector3D& operator+=(const Vector3D& v) {
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	operator physx::PxVec3() const {
		return physx::PxVec3(x, y, z);
	}
};

