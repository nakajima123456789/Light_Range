#include "UGUI.h"
#include "../C_INPUT/C_INPUT.h"
#include "../C_FONT/C_FONT.h"
#include "../ALL_SCENE/SCENEMANAGER/SceneManager.h"
#include "../C_SE/C_SE.h"

UGUI::UGUI() 
{
	//���������X�g�ɓo�^
	observer.addListener(this);
};

UGUI::~UGUI() 
{
	//���������X�g����폜
	observer.removeListener(this);
};

void UGUI::Init()
{
	red_image = GraphicsDevice.CreateSprite(1280, 720, PixelFormat_RGBX8888);
	red_image->ColorFill(nullptr, Color(0, 0, 0));

	cover_image   = add_sprite(_T("SPRITE//�Œ�J�o�[.png"));
	gage_pt_image = add_sprite(_T("SPRITE//PH.png"));
	gage_sp_image = add_sprite(_T("SPRITE//SP.png"));
}

//�摜�ǉ��֐�
int UGUI::add_sprite(LPCTSTR _sprite_name)
{
	SPRITE new_sprite = GraphicsDevice.CreateSpriteFromFile(_sprite_name);
	IDirect3DTexture9* texture = *new_sprite;
	ASSERT(texture != nullptr && "�摜��������Ȃ�!");
	sprite.push_back(new_sprite);
	return (sprite.size() - 1);
}

void UGUI::Update()
{
	if (Input.GetPadInput(0) && Information::Player_Information::player_state != 1){ gage_sp_image_index -= 1;}
	else { gage_sp_image_index++; };

	gage_sp_image_index = clamp(gage_sp_image_index, 0, 407);

	Information::Ui_Information::point_sutamina = gage_sp_image_index;
}

//PLAYER��ENEMY�Ƃ��Փ˂�����Ă΂��֐�
void UGUI::OnCollision()
{
	red_image_flag = TRUE;
}

//PLAYER��ITEM�Ƃ��Փ˂�����Ă΂��֐�
void UGUI::ItemOnCollision()
{
	//�����v�Z
	auto&& point_calculation = [](double a, double b) { return a / b; };

	double item_point = point_calculation(427.f, item_size);

	gage_index = gage_index + item_point;
}

void UGUI::Draw2D()
{
	SpriteBatch.Draw(*sprite[gage_pt_image], Vector3(127, 80, -SpriteBatch_BottomMost), RectWH(0, 0, gage_index, 20));
	SpriteBatch.Draw(*sprite[gage_sp_image], Vector3(127, 97, -SpriteBatch_BottomMost), RectWH(0, 0, gage_sp_image_index, 20));
	SpriteBatch.Draw(*sprite[cover_image],   Vector3(0.0f, 0, -SpriteBatch_BottomMost));

	//�N���A�����Ƃ��܂���Q�[���I�[�o�[�̎��t�F�[�h�A�E�g����B
	if (red_image_flag == TRUE || gage_index >= 427.f)
	{
		feed_out_index += 0.05;
		SpriteBatch.Draw(*red_image, Vector3(0, 0, -SpriteBatch_BottomMost), feed_out_index);
		if (feed_out_index >= 1.0) 
		{
			feed_out_index = 0.f;
			red_image_flag == TRUE ? Information::Ui_Information::game_over_flag = true : Information::Ui_Information::game_clear_flag = true;
		}
	}
}

int UGUI::clamp(int x, int low, int high)
{ 
	ASSERT(low <= high && "�ŏ��l <= �ő�l"); 
	return min(max(x, low), high); 
}