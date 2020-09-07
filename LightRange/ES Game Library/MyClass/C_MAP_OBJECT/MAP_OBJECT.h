#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"
#include "../c_Hitbox/HitBox.h"
#include "../C_SHADER/C_SHADER.h"

//全てのアニメーションキャラクターを登録する
enum CHARACTER_TYPE
{
	CHARACTER_TYPE_PLAYER,
	CHARACTER_TYPE_ENEMY_E,
	CHARACTER_TYPE_ITEM,
	CHARACTER_TYPE_WOMAN,
	CHARACTER_TYPE_NAV_E,
	CHARACTER_TYPE_MAX,
};

enum MAP_TYPE //全てのマップオブジェクト登録する
{
	MAP_TYPE_WALL,
	MAP_TYPE_BOOKSHELL,
	MAP_TYPE_FROAR,
	MAP_TYPE_MAX,
};

//マップエディター上での一つしか存在しないものに対して
const unsigned int IS_CHARACTER_ONCE = 0;


class CHARACTER_MANAGER
{
public:

	CHARACTER_MANAGER();
	virtual ~CHARACTER_MANAGER() {};

	//アニメーションキャラクターそれぞれのタグを設定する。	
	void CharacterTagPreference(char _tag, ...);

	int PosSetCharacterEach(char _map_tag, Vector3 _position);

	//そのタグごとの座標を取得
    std::vector<std::vector<Vector3>> GetCharacterPos() const { return this->character_position_manager; };

	std::vector<char> GetCharacterTag() const { return character_tag_manager; };

private:

	std::vector<char> character_tag_manager;
	std::vector<std::vector<Vector3>> character_position_manager;

public:

};


class MAP_OBJECT_MANAGER
{
public:

	MAP_OBJECT_MANAGER();
	virtual ~MAP_OBJECT_MANAGER();

	void MapDistance(Vector3 _target_pos);
	void MapSetHitBox();

	void Draw();

	std::vector<std::vector<Vector3>> MAP_OBJECT_MANAGER::GetMapManagerPos() const { return this->map_manager_pos; };

	void PosSetMapEachBegin(char tag_name, Vector3 _position);
	void PosSetMapEachEnd  (char tag_name, Vector3 _position);

	std::map<int, Vector3> GetWanderingRoutePos() const { return wandering_route_coordinate; }

	float SpecifiedArgument(Vector3 pos, Vector3 _p);

	float Attenuation(float _index);

	std::vector<HitBox*> Get_Hit_Box() const { return hitbox; };

	std::vector<char> GetMapTag() const { return map_tag_manager; };

private:


	std::vector<char>  map_tag_manager;
	std::vector<MODEL> map_model_manager;

	std::vector<std::vector<float>>   all_map_with_distance;
	std::vector<std::vector<Vector3>> map_manager_pos;

	std::map<int, Vector3> wandering_route_coordinate;

	std::vector<HitBox*> hitbox;

	int  IsHitObjectsInit();
	void IsHitObjectsDraw();

	std::vector<CShaderManager*> c_shader_manager;

	void each(std::function<void(MODEL&)> action);
	void MapObjectScale(Vector3 _scale);
	void SetModelAndTag(char _tag, LPCTSTR _model_name);

	LPCTSTR GetModelFileName(int _model_index);

};

class MAP_MANAGER : public Object
{
public:

	MAP_MANAGER()
	{
		character_manager. reset(new CHARACTER_MANAGER);
		map_object_manager.reset(new MAP_OBJECT_MANAGER);
	};
	virtual ~MAP_MANAGER() {};

	virtual void Init()        override;
	virtual void Update()      override;
	virtual void Draw3D()      override;

	virtual void DrawAlpha3D() override { return; };
	virtual void Draw2D()      override { return; };

	//KeyTagそれぞれに格納された座標を取得する
	std::vector<std::vector<Vector3>> GetCharacterPos() const { return character_manager->GetCharacterPos();       };
	std::map<int, Vector3>  GetWanderingRoutePosition() const { return map_object_manager->GetWanderingRoutePos(); };

	float GetPDistance(Vector3 pos, Vector3 p) { return  map_object_manager->SpecifiedArgument(pos, p); };

	std::vector<HitBox*> Get_Hit_Box() const { return map_object_manager->Get_Hit_Box(); }

	ANIMATIONMODEL* player_animation_model;
private:

	std::vector<cstring>  mapdata;

	std::shared_ptr<CHARACTER_MANAGER>   character_manager;
	std::shared_ptr<MAP_OBJECT_MANAGER>  map_object_manager;

	char get_map_date(int _y, int _x) const { return mapdata[_y][_x]; };

	void SetBlock(int x, int y, char block) { mapdata[x][y] =  block; };
	void MapDataFileName(char* _map_name);
	void MapDataSetAllPosition();

	bool Tag_sarch(char _is_mapdate);

	std::vector<bool> test;

};