#include "C_ENEMY_SEARCH.h"
#include "../../C_Effekseer/CEffekseer_.h"

CEnemySearch::CEnemySearch(EnemyData _c_enemy_date) : enemy_date(_c_enemy_date)
{

}

CEnemySearch::~CEnemySearch()
{

}

void CEnemySearch::Init()
{
	enemysearchstateprocessor.c_enemy_search = this;
	enemysearchstateprocessor.ChangeState(new CEnemySearch::IDOL(&enemysearchstateprocessor));

	animation_model = GraphicsDevice.CreateAnimationModelFromFile(this->GetModelFileName(enemy_date.model_type));
	animation_model->SetPosition((this->transform.position = enemy_date.pos));

	animation_model->SetRotation(this->transform.rotation);
	animation_model->SetMaterial(SetMaterial(Color(0.5f, 0.5f, 0.5)));

	//モデルにとってスケール大きさ切り替え
	auto&& set_scale = [](int model_index)->float { return model_index == ENEMY_LARGE ? 1.2 : 1.7; };
	animation_model->SetScale(this->transform.scale * set_scale(enemy_date.model_type));

	this->ShaderInit(this->GetModelTextureFileName(enemy_date.model_type));

	SetPlayerState(ANIMATION_STATE::RUN);

	IsHitObjectsInit("enemy");
	  IsDistanceInit("enemy");


}

void CEnemySearch::Update()
{
	nav_mesh.Update(this->GetPlayerPosition(), animation_model, enemy_date.speed);
	IsDistanceUpdate(animation_model->GetPosition());

	enemysearchstateprocessor.Update();
}

void CEnemySearch::Draw3D()
{
	//アニメーションスピード
	animation_model->AdvanceTime(1.0 / enemy_date.AdvanceTime);
	IsHitObjectsDraw(animation_model->GetPosition());
}

void CEnemySearch::DrawAlpha3D()
{
	ShaderAlphaDraw();
	EFFECT shader = ShaderDrawGetEffct();

	animation_model->Draw(shader);

}


void CEnemySearch::IDOL::Update(){
	//
	return;
}

void CEnemySearch::RUN::Update(){
	//
	return;
}

