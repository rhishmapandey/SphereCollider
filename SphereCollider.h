#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "raylib.h"

class vec3d {
public:
	vec3d(float x, float y, float z);
	vec3d(Vector3 pos);
	Vector3 getPos();
	friend vec3d operator+(vec3d const& vec1, vec3d const& vec2);
	friend vec3d operator-(vec3d const& vec1, vec3d const& vec2);
	friend vec3d operator*(float const& scaler, vec3d const& vec);
	friend vec3d operator/(vec3d const& vec, float scaler);
	float GetMagnitude();
	void makeunit();
	float x, y, z;
private:
};

class SphereCollider
{
public:
	vec3d position;
	vec3d velocity;
	float radius;
	SphereCollider(vec3d position, float radius);
	bool CheckCollison(SphereCollider& other);
	vec3d GetContactUV(SphereCollider& other);;
};
