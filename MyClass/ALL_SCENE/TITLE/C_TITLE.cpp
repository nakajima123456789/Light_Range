#include "C_TITLE.h"
#include "../SCENEMANAGER/SceneManager.h"
#include "../../C_INPUT/C_INPUT.h"

void C_TITLE::Initialize()
{
	MediaManager.Attach(GraphicsDevice);
	Add_Sprite(_T("SPRITE//gemestart_02.png"));
}

void C_TITLE::Update()
{
	if (Input.GetPadInputDown(11)){SceneManager::ChangeScene(SceneManager::RESULT);}
}

void C_TITLE::Draw2D()
{
	std::for_each(sprite_list_name.begin(), sprite_list_name.end(), [](SPRITE& _sprite) {SpriteBatch.Draw(*_sprite, Vector3(0, 0, 0)); });
}

void C_TITLE::Add_Sprite(LPCTSTR _sprite_name)
{
	sprite = GraphicsDevice.CreateSpriteFromFile(_sprite_name);
	sprite_list_name.push_back(sprite);
}