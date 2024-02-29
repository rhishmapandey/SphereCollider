#include "SphereCollider.h"

vec3d::vec3d(float x, float y, float z): x(x), y(y), z(z){

}

vec3d::vec3d(Vector3 pos)
{
	x = pos.x;
	y = pos.y;
	z = pos.z;
}

Vector3 vec3d::getPos()
{
	return Vector3(x, y, z);
}

float vec3d::GetMagnitude()
{
	return std::sqrtf(x*x + y*y + z*z);
}

void vec3d::makeunit()
{
	float mag = GetMagnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}

vec3d operator+(vec3d const& vec1, vec3d const& vec2)
{
	return vec3d(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

vec3d operator-(vec3d const& vec1, vec3d const& vec2)
{
	return vec3d(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

vec3d operator*(float const& scaler, vec3d const& vec)
{
	return vec3d(scaler*vec.x, scaler * vec.y, scaler * vec.z);
}

vec3d operator/(vec3d const& vec, float scaler)
{
	return vec3d(vec.x/scaler, vec.y/scaler, vec.z/scaler);
}

SphereCollider::SphereCollider(vec3d position, float radius) : position(position), radius(radius), velocity(vec3d(0.0f, 0.0f, 0.0f)){
	if (radius <= 0.0f){
		throw std::runtime_error("value for sphere collider should be greater then zero.\n");
	}
}

bool SphereCollider::CheckCollison(SphereCollider & other)
{
	Vector3 pos = position.getPos();
	Vector3 poso = other.position.getPos();
	float rad = radius;
	float rado = other.radius;
	float cdis = (pos.x - poso.x)*(pos.x - poso.x) + (pos.y - poso.y)*(pos.y - poso.y) + (pos.z - poso.z)*(pos.z - poso.z);
	return (((rado + rad)* (rado + rad)) > cdis);
}

vec3d SphereCollider::GetContactUV(SphereCollider& other)
{
	vec3d contact = (other.position-position);
	contact.makeunit();
	return contact;
}