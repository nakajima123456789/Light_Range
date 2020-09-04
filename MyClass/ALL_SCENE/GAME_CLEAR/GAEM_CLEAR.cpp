#include "GAEM_CLEAR.h"
#include "../SCENEMANAGER/SceneManager.h"

void GAEM_CLEAR::Initialize()
{
	sprite = GraphicsDevice.CreateSpriteFromFile(_T("SPRITE//GAMECLEAR.png"));
}

void GAEM_CLEAR::Update()
{
	if (Input.GetPadInputDown(0))
	{
		SceneManager::ChangeScene(SceneManager::TITLE);
		return;
	}
}

void GAEM_CLEAR::Draw2D()
{
	SpriteBatch.Draw(*sprite, Vector3_Zero);
}
