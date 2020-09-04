#pragma once
#include "../../C_OBJECT/Object.h"
#include "../../../ESGLib.h"
#include "../../C_STATE/C_STATE.h"
#include "../../C_SHADER/C_SHADER.h"

#include "../../C_HITBOX/HitBox.h"
#include "../../C_DISTANCE/C_DIS.h"

#include <algorithm>

enum ENEMY_MODEL
{
	ENEMY_LARGE,
	ENEMY_WAMAN,
};

class C_ENEMY_BASE : public Object
{
public:
	C_ENEMY_BASE() {};
	virtual ~C_ENEMY_BASE() {};

	virtual void C_ENEMY_BASE::Init()        override = 0;
	virtual void C_ENEMY_BASE::Update()      override = 0;
	virtual void C_ENEMY_BASE::Draw3D()      override = 0;

	virtual void C_ENEMY_BASE::DrawAlpha3D() override = 0;
	virtual void C_ENEMY_BASE::Draw2D()      override = 0;

	static void Set_Player_position(Vector3* _position) { player_pos = _position; };

private:
	int this_track_enable;
	static Vector3* player_pos;

	float alpha = 0.5f;

	std::shared_ptr <HitBox> hitbox;
	std::shared_ptr <C_DIS>  c_dis;

protected:

	float    C_ENEMY_BASE::Lock_at_Target(Vector3 _position);
	float    C_ENEMY_BASE::Distance_at_Traget(Vector3 _position);
	Vector3  C_ENEMY_BASE::skater_st_Traget(Vector3 _position);
	bool     C_ENEMY_BASE::SetPlayerState(int new_state);
	Material C_ENEMY_BASE::Set_Material(Color color);
	int      C_ENEMY_BASE::wrap(int x, int low, int high);

	void     C_ENEMY_BASE::ShaderInit(LPCTSTR _file_texcha);
	EFFECT   C_ENEMY_BASE::ShaderDrawGetEffct();

	void     C_ENEMY_BASE::ShaderAlphaDraw();

	LPCTSTR  C_ENEMY_BASE::GetModelFileName(int _enemy_model);
	LPCTSTR  C_ENEMY_BASE::GetModelTextureFileName(int _enemy_model);

	void   C_ENEMY_BASE::IsDistanceInit(std::string _tags);
	void   C_ENEMY_BASE::IsDistanceUpdate(Vector3 _pos);

	void   C_ENEMY_BASE::IsHitObjectsInit(std::string _tags);
	void   C_ENEMY_BASE::IsHitObjectsDraw(Vector3 _pos);

	bool   C_ENEMY_BASE::IsHitObjects(std::string tags);

protected:

	ANIMATIONMODEL animation_model = nullptr;

	Vector3 Get_Player_position() const { return *player_pos; };

	std::shared_ptr <CShaderManager> c_shader_manager;

	enum ANIMATION_STATE { IDOL, RUN };

	int model_type;
};

