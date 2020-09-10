#pragma once
#include "../C_ENEMY_BASE/C_ENEMY_BASE.h"

class EnemyWanderStateProcessor;
class CEnemyWander;

class EnemyWanderStateProcessor : public  StateProcessor {
public:
	CEnemyWander* c_enemy_wander;
};

class CEnemyWander : public CEnemyBase
{
public:
	CEnemyWander(std::map<int, Vector3> _get_root_position);

	virtual ~CEnemyWander();

	EnemyWanderStateProcessor enemywanderstateprocessor;

	virtual void CEnemyWander::Init()        override;
	virtual void CEnemyWander::Update()      override;
	virtual void CEnemyWander::Draw3D()      override;
													   
	virtual void CEnemyWander::DrawAlpha3D() override;
	virtual void CEnemyWander::Draw2D()      override { return; };

	class IDOL : public State
	{
	private:
		EnemyWanderStateProcessor* _owner;

		int root_number = 0;

	public:
		IDOL(EnemyWanderStateProcessor* owner) : _owner(owner) { };
		virtual ~IDOL() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		EnemyWanderStateProcessor* _owner;
	public:
		RUN(EnemyWanderStateProcessor* owner) : _owner(owner) {}
		virtual ~RUN() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

private:

	//ïœêîêÈåæ
	std::map<int, Vector3> map_root_pos;
	std::shared_ptr <HitBox> hitbox;

	//ä÷êîêÈåæ
};

