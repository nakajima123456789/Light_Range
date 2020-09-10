#include "EnemyStaker.h"

CEnemyStaker::CEnemyStaker(Vector3 _pos)
{

}

CEnemyStaker::~CEnemyStaker()
{

}

void CEnemyStaker::Init()
{
	enemy_staker_state_processor.c_enemy_search = this;
	enemy_staker_state_processor.ChangeState(new CEnemyStaker::IDOL(&enemy_staker_state_processor));



}

void CEnemyStaker::Update()
{
	
	enemy_staker_state_processor.Update();
}

void CEnemyStaker::Draw3D()
{

}

void CEnemyStaker::DrawAlpha3D()
{


}

void CEnemyStaker::IDOL::Update() 
{
	

}

void CEnemyStaker::RUN::Update() 
{
	

}
