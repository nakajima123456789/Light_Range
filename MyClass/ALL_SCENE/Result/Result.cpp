#include "Result.h"
#include "../SCENEMANAGER/SceneManager.h"


void C_RESULT::Initialize()
{
	sprite = GraphicsDevice.CreateSpriteFromFile(_T("SPRITE//ÉQÅ[ÉÄê‡ñæ.png"));
}

void C_RESULT::Update()
{
	if (Input.GetPadInputDown(11))
	{
		SceneManager::ChangeScene(SceneManager::MAIN);
		return;
	}
}

void C_RESULT::Draw2D()
{
	SpriteBatch.Draw(*sprite, Vector3_Zero);
}