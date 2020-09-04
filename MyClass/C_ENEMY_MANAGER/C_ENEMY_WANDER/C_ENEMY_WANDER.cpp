#include "C_ENEMY_WANDER.h"
#include "../../C_FONT/C_FONT.h"

C_ENEMY_WANDER::C_ENEMY_WANDER(std::map<int, Vector3> _get_root_position) : map_root_pos(_get_root_position)
{
	this->transform.position = map_root_pos[INITIALIZE_POS];
};

void C_ENEMY_WANDER::Init()
{
	enemywanderstateprocessor.c_enemy_wander = this;
	enemywanderstateprocessor.ChangeState(new C_ENEMY_WANDER::IDOL(&enemywanderstateprocessor));

	animation_model = GraphicsDevice.CreateAnimationModelFromFile((_T("MODEL//enemy_motion//enemy_large.x")));
	animation_model->SetMaterial(Set_Material(Color(0.5f, 0.5f, 0.5)));

	ShaderInit(_T("MODEL//enemy_motion/lambert1_2D_View.png"));

	string tag = "enemy";

	IsHitObjectsInit(tag);
};

C_ENEMY_WANDER::~C_ENEMY_WANDER()
{

}

void C_ENEMY_WANDER::Update()
{
	this->SetPlayerState(ANIMATION_STATE::RUN);

	this->ShaderAlphaDraw();

	this->enemywanderstateprocessor.Update();
};

void C_ENEMY_WANDER::IDOL::Update()
{
	if (_owner->c_enemy_wander->Distance_at_Traget(_owner->c_enemy_wander->map_root_pos[root_number]) <= 0.1)
	{
		root_number = _owner->c_enemy_wander->wrap(root_number + 1,0,10);	
	}

	_owner->c_enemy_wander->transform.position = _owner->c_enemy_wander->skater_st_Traget(_owner->c_enemy_wander->map_root_pos[root_number]);

	_owner->c_enemy_wander->transform.rotation.y = -(_owner->c_enemy_wander->Lock_at_Target(_owner->c_enemy_wander->map_root_pos[root_number])) + -90;
}

void C_ENEMY_WANDER::RUN::Update()
{



}

void C_ENEMY_WANDER::Draw3D() 
{
	animation_model->SetPosition((this->transform.position));
	animation_model->SetRotation(this->transform.rotation);
	animation_model->SetScale(this->transform.scale);
	animation_model->AdvanceTime(1.0 / 120);

	IsHitObjectsDraw(this->transform.position);
};

void C_ENEMY_WANDER::DrawAlpha3D()
{
	ShaderAlphaDraw();

	EFFECT shader = ShaderDrawGetEffct();
	animation_model->Draw(shader);
}


