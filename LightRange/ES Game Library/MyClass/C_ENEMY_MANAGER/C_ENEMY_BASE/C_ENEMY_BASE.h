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

class CEnemyBase : public Object
{
public:
	CEnemyBase() {};
	virtual ~CEnemyBase() {};

	virtual void CEnemyBase::Init()        override = 0;
	virtual void CEnemyBase::Update()      override = 0;
	virtual void CEnemyBase::Draw3D()      override = 0;

	virtual void CEnemyBase::DrawAlpha3D() override = 0;
	virtual void CEnemyBase::Draw2D()      override = 0;

	static void Set_Player_position(Vector3* _position) { player_pos = _position; };

private:
	int this_track_enable;
	static Vector3* player_pos;

	float alpha = 0.5f;

	std::shared_ptr <HitBox> hitbox;
	std::shared_ptr <CDis>   c_dis;

protected:

	float    LockAtTarget(Vector3 _position);
	float    DisAtTraget(Vector3 _position);
	Vector3  SkaterAtTraget(Vector3 _position);
	bool     SetPlayerState(int new_state);
	Material SetMaterial(Color color);
	int      wrap(int x, int low, int high);
			 
	void     ShaderInit(LPCTSTR _file_texcha);
	EFFECT   ShaderDrawGetEffct();
			 
	void     ShaderAlphaDraw();
			
	LPCTSTR GetModelFileName(int _enemy_model);
	LPCTSTR GetModelTextureFileName(int _enemy_model);

	void   IsDistanceInit(std::string _tags);
	void   IsDistanceUpdate(Vector3 _pos);

	void   IsHitObjectsInit(std::string _tags);
	void   IsHitObjectsDraw(Vector3 _pos);

	bool   IsHitObjects(std::string tags);

protected:

	ANIMATIONMODEL animation_model = nullptr;

	Vector3 GetPlayerPosition() const { return *player_pos; };

	std::shared_ptr <CShaderManager> c_shader_manager;

	enum ANIMATION_STATE { IDOL, RUN };
};

