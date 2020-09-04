#pragma once
#include "../C_ENEMY_BASE/C_ENEMY_BASE.h"
#include "../../C_HITBOX/HitBox.h"

class ENEMYWANDERSTATEPROCESSOR;
class C_ENEMY_WANDER;

class ENEMYWANDERSTATEPROCESSOR : public  StateProcessor {
public:
	C_ENEMY_WANDER* c_enemy_wander;
};

class C_ENEMY_WANDER : public C_ENEMY_BASE
{
public:
	C_ENEMY_WANDER(std::map<int, Vector3> _get_root_position);

	virtual ~C_ENEMY_WANDER();

	ENEMYWANDERSTATEPROCESSOR enemywanderstateprocessor;

	virtual void C_ENEMY_WANDER::Init()        override;
	virtual void C_ENEMY_WANDER::Update()      override;
	virtual void C_ENEMY_WANDER::Draw3D()      override;
													   
	virtual void C_ENEMY_WANDER::DrawAlpha3D() override;
	virtual void C_ENEMY_WANDER::Draw2D()      override { return; };

	class IDOL : public State
	{
	private:
		ENEMYWANDERSTATEPROCESSOR* _owner;

		int root_number = 0;

	public:
		IDOL(ENEMYWANDERSTATEPROCESSOR* owner) : _owner(owner) { };
		virtual ~IDOL() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		ENEMYWANDERSTATEPROCESSOR* _owner;
	public:
		RUN(ENEMYWANDERSTATEPROCESSOR* owner) : _owner(owner) {}
		virtual ~RUN() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

private:

	//ïœêîêÈåæ

	std::map<int, Vector3> map_root_pos;
	std::shared_ptr <HitBox> hitbox;

	enum {INITIALIZE_POS,};

	//ä÷êîêÈåæ
};

