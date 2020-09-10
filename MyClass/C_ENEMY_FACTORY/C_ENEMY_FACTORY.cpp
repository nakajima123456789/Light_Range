#include "C_ENEMY_FACTORY.h"

Object* EnemyFactory::Create(std::string _type, Vector3 _position)
{
	Object* object = CreateProduct(_type, _position);
	return object;
}

Object* EnemyFactory::Create(std::string _type, std::map<int, Vector3> _position)
{
	Object* object = CreateProduct(_type, _position);
	return object;
}

Object* EnemyStationeryFactory::CreateProduct(std::string _type, Vector3 _position)
{
	if (_type == "’Tõ“G‘") {
		set_enemy_serch_data.AdvanceTime = 30;
		set_enemy_serch_data.speed = 0.030f;
		set_enemy_serch_data.pos = _position;
		set_enemy_serch_data.model_type = 1;
		return new CEnemySearch(set_enemy_serch_data);
	}

	if (_type == "’Tõ“G’x") {
		set_enemy_serch_data.AdvanceTime = 120;
		set_enemy_serch_data.speed = 0.015f;
		set_enemy_serch_data.pos = _position;
		set_enemy_serch_data.model_type = 0;
		return new CEnemySearch(set_enemy_serch_data);
	}
	ASSERT(FALSE && !"“G‚Ì–¼‘O‚ªˆá‚¤!");
}

Object* EnemyStationeryFactory::CreateProduct(std::string _type, std::map<int, Vector3> _position)
{
	if (_type == "œpœj“G") { return new CEnemyWander(_position); }

	ASSERT(FALSE && !"“G‚Ì–¼‘O‚ªˆá‚¤!");
}