#pragma once
#include "../../ESGLib.h"
#include "../C_STATE/C_STATE.h"
#include "../C_OBJECT/Object.h"
#include "../c_Hitbox/HitBox.h"
#include "../C_INPUT/C_INPUT.h"
#include "../C_OBSERVER/OBSERVER.h"
#include "../C_DISTANCE/C_DIS.h"
#include "../C_MAP_OBJECT/MAP_OBJECT.h"
#include "../C_SHADER/C_SHADER.h"

#include "../C_SE/C_SE.h"

#include <functional>

class CPlayerStateProcessor;
class CPlayer;

class CPlayerStateProcessor : public  StateProcessor {
public:
	CPlayer* player_manager;
};

class CPlayer : public Object
{
public:
	CPlayerStateProcessor player_state_processor;
	
	CPlayer(Vector3  _pos);
	virtual ~CPlayer();

	virtual void CPlayer::Init()        override;
	virtual void CPlayer::Update()      override;
	virtual void CPlayer::Draw3D()      override;

	virtual void CPlayer::DrawAlpha3D() override { return; };
	virtual void CPlayer::Draw2D()      override { return; };

	void CPlayer::GetHitBoxPosition(Vector3 _position);

	MAP_MANAGER*    map_manager;
	ANIMATIONMODEL  player_model;
private:
	Material CPlayer::SetMaterial(Color color);

	bool  CPlayer::SetPlayerState(int new_state);
	bool  CPlayer::IsHitObjects(std::string tags);

	int   CPlayer::IsHitObjectsInit();

	void  CPlayer::IsHitObjectsDraw();
	void  CPlayer::IsPlayerMoveMent();
	void  CPlayer::CollisionDetection();

	void  CPlayer::IsDistanceInit();
	void  CPlayer::IsDistanceUpdate();

	class IDOL : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		IDOL(CPlayerStateProcessor* owner) : _owner(owner) { };
		virtual ~IDOL() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class WALK : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		WALK(CPlayerStateProcessor* owner) : _owner(owner) {}
		virtual ~WALK() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		RUN(CPlayerStateProcessor* owner) : _owner(owner) {}
		virtual ~RUN() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class DAMAGE : public State
	{
	private:
		CPlayerStateProcessor* _owner;
	public:
		DAMAGE(CPlayerStateProcessor* owner) : _owner(owner) {}
		virtual ~DAMAGE() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return 30; };

		virtual void Update() override;
	};

private:

	//‰e•`‰æ
	inline Matrix Create_Shadow_Matrix(const D3DLIGHTTYPE light_type, const Vector3& light,const Vector3& pos, const Vector3& shadow_offset,const Vector3& normal);

	std::shared_ptr <HitBox> c_hitbox;
	std::shared_ptr <CDis>   c_dis;
	std::shared_ptr <CShaderManager> c_shader_manager;

	OBSERVER observer;

	enum PLAYER_ANIMATION_TYPE { _DAMEGE,_IDOL, _WALK, _RUN, _PLAYER_ANIMATION_TYPE_MAX, };

	Vector3 speed_vectol = Vector3_Zero;

	int this_track_enable = 0;

	int se_i;
};


