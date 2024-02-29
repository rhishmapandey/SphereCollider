#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "SphereCollider.h"

Color colorArray[26] = {
	LIGHTGRAY,
	GRAY,
	DARKGRAY,
	YELLOW,
	GOLD,
	ORANGE,
	PINK,
	RED,
	MAROON,
	GREEN,
	LIME,
	DARKGREEN,
	SKYBLUE,
	BLUE,
	DARKBLUE,
	PURPLE,
	VIOLET,
	DARKPURPLE,
	BEIGE,
	BROWN,
	DARKBROWN,
	WHITE,
	BLACK,
	BLANK,
	MAGENTA,
	RAYWHITE
};

constexpr float deltatime = 1.0f / 60.0f;
constexpr float gravity = 9.81f;

constexpr float damping = 0.6f;

std::vector<SphereCollider> colliders;

void DrawSphere(SphereCollider sphere) {
	Vector3 center = sphere.position.getPos();
	float radius = sphere.radius;
	DrawSphere(center, radius, colorArray[std::rand()%26]);
	DrawSphereWires(center, radius*1.05f, 12, 12, BLACK);
}

float getRandomFloatInRange(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);

	return dis(gen);
}

void InitSphere() {};

void AddNewSphere() {
	float radius = 1.0f;
	SphereCollider sphere(vec3d(getRandomFloatInRange(-8.0f, 8.0f), getRandomFloatInRange(5.0f, 15.0f), getRandomFloatInRange(-8.0f, 8.0f)), radius);
	sphere.velocity.x = getRandomFloatInRange(-50.0f, 50.0f);
	sphere.velocity.y = getRandomFloatInRange(-50.0f, 50.0f);
	sphere.velocity.z = getRandomFloatInRange(-50.0f, 50.0f);
	colliders.push_back(sphere);
}

void DrawSpheres() {
	for (size_t i = 0; i < colliders.size(); i++)
	{
		DrawSphere(colliders[i]);
	}
}

void UpdateGravityTick(SphereCollider& sphere) {
	sphere.velocity.y -= deltatime*gravity;
}

void UpdatePositionTick(SphereCollider& sphere) {
	sphere.position = sphere.position + deltatime*sphere.velocity;
}

void UpdateBoundryCollisonTick(SphereCollider& sphere) {
	if (sphere.position.y < 1.0f) {
		if (sphere.velocity.y < 0.0f) {
			sphere.velocity = damping*sphere.velocity;
			sphere.velocity.y = -1.0f*sphere.velocity.y;
		}
	}
	else if (sphere.position.y > 20.0f) {
		if (sphere.velocity.y > 0.0f) {
			sphere.velocity = damping * sphere.velocity;
			sphere.velocity.y = -1.0f * sphere.velocity.y;
		}
	}
	if (sphere.position.x > 9.5f) {
		if (sphere.velocity.x > 0.0f) {
			sphere.velocity = damping * sphere.velocity;
			sphere.velocity.x = -1.0f * sphere.velocity.x;
		}
	}
	else if (sphere.position.x < -9.5f) {
		if (sphere.velocity.x < 0.0f) {
			sphere.velocity = damping * sphere.velocity;
			sphere.velocity.x = -1.0f * sphere.velocity.x;
		}
	}
	if (sphere.position.z > 9.5f) {
		if (sphere.velocity.z > 0.0f) {
			sphere.velocity = damping * sphere.velocity;
			sphere.velocity.z = -1.0f * sphere.velocity.z;
		}
	}
	else if (sphere.position.z < -9.5f) {
		if (sphere.velocity.z < 0.0f) {
			sphere.velocity = damping * sphere.velocity;
			sphere.velocity.z = -1.0f * sphere.velocity.z;
		}
	}
}

void UpdateSphereCollisonTick(size_t index) {
	for (size_t i = index; i < colliders.size(); i++)
	{
		if (index != i) {
			if (colliders[index].CheckCollison(colliders[i])) {
				//std::cout << "Collison " << index << " " << i << std::endl;
				vec3d coltan = colliders[index].GetContactUV(colliders[i]);
				coltan.makeunit();
				vec3d sharedvelocity = damping*0.5f*(colliders[i].velocity.GetMagnitude() + colliders[index].velocity.GetMagnitude())*coltan;
				colliders[index].velocity = -1.0f*sharedvelocity;
				colliders[i].velocity = sharedvelocity;
			}
		}
	}
}

void PhysicsTick(){
	for (size_t i = 0; i < colliders.size(); i++)
	{
		UpdateGravityTick(colliders[i]);
		UpdateBoundryCollisonTick(colliders[i]);
		UpdateSphereCollisonTick(i);
		UpdatePositionTick(colliders[i]);
	}
}


int UpdateSpheres() 
{
	DrawSpheres();
	PhysicsTick();
	return 0;
}

SphereCollider CameraCollider(vec3d(1.0f, 1.0f, 1.0f), 3.0f);

void MoveCameraCollider(Vector3 positon)
{
	CameraCollider.position.x = positon.x;
	CameraCollider.position.y = positon.y;
	CameraCollider.position.z = positon.z;
	DrawSphereWires(CameraCollider.position.getPos(), 3.0f, 20, 20, GREEN);

	for (size_t i = 0; i < colliders.size(); i++)
	{
		if (CameraCollider.CheckCollison(colliders[i])) {
			//std::cout << "Collison " << index << " " << i << std::endl;
			vec3d coltan = CameraCollider.GetContactUV(colliders[i]);
			coltan.makeunit();
			vec3d sharedvelocity = damping * 0.5f * (colliders[i].velocity.GetMagnitude() + 30.0f) * coltan;
			colliders[i].velocity = sharedvelocity;
		}
	}
}