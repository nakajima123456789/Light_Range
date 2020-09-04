#include "C_CAMERA.h"
#include "../C_FONT/C_FONT.h"

void C_CAMERA::Init()
{
	light.Type      = Light_Directional;
	light.Direction = Vector3_Down + Vector3_Forward;
	light.Diffuse   = Color(0.5f, 0.5f, 0.5f);
	light.Ambient   = Color(0.05f, 0.05f, 0.05f);
	light.Specular  = Color(0.5f, 0.5f, 0.5f);
	light.Position  = Vector3(0, 10, 0);
	GraphicsDevice.SetLight(light);

	camera->SetLookAt(Vector3(0, 0, -50),Vector3(0,0,1), Vector3_Up);
	camera->SetPerspectiveFieldOfView(45.0, 16.0f / 9.0f, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(camera);
}

void C_CAMERA::Update()
{
	pos = player_transform->position;
    camera.SetLookAt(pos + Vector3(0, 5.5, -1.0), pos + Vector3(0, 1, 0), Vector3_Up);
	GraphicsDevice.SetCamera(camera);
}

void C_CAMERA::Get_Other_Tranceform(Transform* _player_transform)
{
	player_transform = _player_transform;
}


