#include <iostream>
#include "raylib.h"
#include "Sphere.hpp"


#define ORIGIN Vector3(0.0f, 0.0f, 0.0f)

int main(int argc, char** argv)
{
	constexpr int screenwidth = 1280;
	constexpr int screenheight = 720;
	
	Camera camera = {0};
	camera.position = Vector3(10.0f, 5.0f, 10.0f);
	camera.target = Vector3(0.0f, 5.0f, 0.0f);
	camera.up = Vector3(0.0f, 1.0f, 0.0f);
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	InitWindow(screenwidth, screenheight, "SphereColliderXD");
	SetTargetFPS(60);
	DisableCursor();
	InitSphere();

	for (size_t i = 0; i < 40; i++)
	{
		AddNewSphere();
	}

	while(!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_P)) AddNewSphere();
		UpdateCamera(&camera, CAMERA_FREE);
		BeginDrawing();
			ClearBackground(Color(94, 172, 232, 255));
			
			BeginMode3D(camera);
				DrawGrid(20, 1.0f);
				DrawCubeWires(Vector3(0.0f, 10.0f, 0.0f), 20.0f, 20.0f, 20.0f, DARKGREEN);
				std::srand(0);
				UpdateSpheres();
				MoveCameraCollider(camera.position);
			EndMode3D();

		EndDrawing();
	}
	
	CloseWindow();
	
	return 0;
}