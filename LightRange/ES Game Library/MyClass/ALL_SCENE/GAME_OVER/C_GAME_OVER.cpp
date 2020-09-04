#include "C_GAME_OVER.h"
#include "../SCENEMANAGER/SceneManager.h"


void C_GAME_OVER::Initialize()
{
	
	sprite = GraphicsDevice.CreateSpriteFromFile(_T("SPRITE//gemeover_02.png"));

}

void C_GAME_OVER::Update()
{
	if (Input.GetPadInputDown(0))
	{
		SceneManager::ChangeScene(SceneManager::TITLE);
		return;
	}
}

void C_GAME_OVER::Draw2D()
{
	SpriteBatch.Draw(*sprite, Vector3_Zero);
}
