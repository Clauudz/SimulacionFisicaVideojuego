#pragma once
#include "PxPhysicsAPI.h"

class Vector3D
{
public:
	float x, y, z;

	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const physx::PxVec3& v);

	float magnitude() const;
	Vector3D normalize() const;

	float dot(const Vector3D& v) const {
		
	};

	Vector3D cross(const Vector3D& v) const {

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

	Vector3D operator*(int n) const {
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

