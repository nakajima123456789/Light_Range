#include "C_ENEMY_SEARCH.h"

C_ENEMY_SEARCH::C_ENEMY_SEARCH(int _model_type, Vector3 _position, float _speed, double _animation_speed)
{
	this->transform.position = _position;
	speed = _speed;
	animation_speed = _animation_speed;
	model_type = _model_type;
}

C_ENEMY_SEARCH::~C_ENEMY_SEARCH()
{

}

void C_ENEMY_SEARCH::Init()
{
	enemysearchstateprocessor.c_enemy_search = this;
	enemysearchstateprocessor.ChangeState(new C_ENEMY_SEARCH::IDOL(&enemysearchstateprocessor));

	animation_model = GraphicsDevice.CreateAnimationModelFromFile(this->GetModelFileName(this->model_type));
	animation_model->SetMaterial(Set_Material(Color(0.5f, 0.5f, 0.5)));

	animation_model->SetPosition((this->transform.position));
	animation_model->SetRotation(this->transform.rotation);
	animation_model->SetScale(this->transform.scale * 1.5);

	this->ShaderInit(this->GetModelTextureFileName(this->model_type));

	SetPlayerState(ANIMATION_STATE::RUN);

	string tag = "enemy";

	IsHitObjectsInit(tag);
	IsDistanceInit(tag);
}

void C_ENEMY_SEARCH::Update()
{
	nav_mesh_agent.Update(this->Get_Player_position(), animation_model, speed);

	IsDistanceUpdate(animation_model->GetPosition());

	this->enemysearchstateprocessor.Update();
}

void C_ENEMY_SEARCH::Draw3D()
{
	animation_model->AdvanceTime(1.0 / animation_speed);

	IsHitObjectsDraw(animation_model->GetPosition());
}

void C_ENEMY_SEARCH::DrawAlpha3D()
{
	ShaderAlphaDraw();
	EFFECT shader = ShaderDrawGetEffct();
	animation_model->Draw(shader);
}


void C_ENEMY_SEARCH::IDOL::Update()
{
	return;
}

void C_ENEMY_SEARCH::RUN::Update()
{
	return;
}

