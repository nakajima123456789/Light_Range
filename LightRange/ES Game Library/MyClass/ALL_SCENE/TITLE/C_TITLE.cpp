#include "C_TITLE.h"
#include "../SCENEMANAGER/SceneManager.h"
#include "../../C_INPUT/C_INPUT.h"

void C_TITLE::Initialize()
{
	MediaManager.Attach(GraphicsDevice);

	Add_Sprite(_T("SPRITE//gemestart_02.png"));
	Add_Sprite_Pos(Vector3_Zero);

	media = MediaManager.CreateMediaFromFile(_T("movie//playmovie.wmv"));
	
}

void C_TITLE::Update()
{
	if (Input.GetPadInputDown(0)){SceneManager::ChangeScene(SceneManager::RESULT);}
	
	if (ƒ¢time % (60 * 30) == 0)
	{
		media->Replay();
		scene_flag = true;
	}ƒ¢time++;

	if (scene_flag)
	{
		end_time++;
		if (end_time >= (60 * 20))
		{
			scene_flag = false;
			end_time = 0;
		}
	}
}

void C_TITLE::Draw2D()
{
	if(scene_flag)
	SpriteBatch.Draw(*media, Vector3(0.0f, 0.0f, 1000.0f), 1.0f);
	else 
	std::for_each(sprite_list_name.begin(), sprite_list_name.end(), [](SPRITE& _sprite) {SpriteBatch.Draw(*_sprite, Vector3(0, 0, 0)); });
}

void C_TITLE::Add_Sprite(LPCTSTR _sprite_name)
{
	sprite = GraphicsDevice.CreateSpriteFromFile(_sprite_name);
	sprite_list_name.push_back(sprite);
}

void C_TITLE::Add_Sprite_Pos(Vector3 _sprite_pos)
{
	Vector3 sprite_pos = _sprite_pos;
	sprite_list_pos.push_back(sprite_pos);
}
