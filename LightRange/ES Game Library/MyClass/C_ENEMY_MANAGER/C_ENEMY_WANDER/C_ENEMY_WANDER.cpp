#include "C_ENEMY_WANDER.h"

CEnemyWander::CEnemyWander(std::map<int, Vector3> _get_root_position) : map_root_pos(_get_root_position)
{
	this->transform.position = map_root_pos[0];
};

void CEnemyWander::Init()
{
	enemywanderstateprocessor.c_enemy_wander = this;
	enemywanderstateprocessor.ChangeState(new CEnemyWander::IDOL(&enemywanderstateprocessor));

	animation_model = GraphicsDevice.CreateAnimationModelFromFile((_T("MODEL//enemy_motion//enemy_large.x")));
	animation_model->SetMaterial(SetMaterial(Color(0.5f, 0.5f, 0.5)));

	ShaderInit(_T("MODEL//enemy_motion/lambert1_2D_View.png"));

	IsHitObjectsInit("enemy");
};

CEnemyWander::~CEnemyWander()
{

}

void CEnemyWander::Update()
{
	SetPlayerState(ANIMATION_STATE::RUN);
	ShaderAlphaDraw();

	enemywanderstateprocessor.Update();
};

void CEnemyWander::IDOL::Update()
{
	//0‚©‚ç9‚Ü‚Å‚ÌÀ•W‚ðˆÚ“®‚·‚éB
	if (_owner->c_enemy_wander->DisAtTraget(_owner->c_enemy_wander->map_root_pos[root_number]) <= 0.1)
	{
		root_number = _owner->c_enemy_wander->wrap(root_number + 1,0,10);	
	}

	_owner->c_enemy_wander->transform.position   = _owner->c_enemy_wander->SkaterAtTraget(_owner->c_enemy_wander->map_root_pos[root_number]);
	_owner->c_enemy_wander->transform.rotation.y = -(_owner->c_enemy_wander->LockAtTarget(_owner->c_enemy_wander->map_root_pos[root_number])) + -90;
}

void CEnemyWander::RUN::Update()
{



}

void CEnemyWander::Draw3D() 
{
	animation_model->SetPosition((this->transform.position));
	animation_model->SetRotation(this->transform.rotation);
	animation_model->SetScale(this->transform.scale);
	animation_model->AdvanceTime(1.0 / 120);

	IsHitObjectsDraw(this->transform.position);
};

void CEnemyWander::DrawAlpha3D()
{
	ShaderAlphaDraw();
	EFFECT shader = ShaderDrawGetEffct();
	animation_model->Draw(shader);
}


