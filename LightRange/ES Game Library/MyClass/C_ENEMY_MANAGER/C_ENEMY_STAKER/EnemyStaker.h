#pragma once
#include "../C_ENEMY_BASE/C_ENEMY_BASE.h"

class EnemyStakerStateProcessor;
class CEnemyStaker;

class EnemyStakerStateProcessor : public  StateProcessor {
public:
	CEnemyStaker* c_enemy_search;
};

class CEnemyStaker : public CEnemyBase
{
public:
	CEnemyStaker(Vector3  _pos);
	virtual ~CEnemyStaker();

	EnemyStakerStateProcessor enemy_staker_state_processor;

	virtual void Init()        override;
	virtual void Update()      override;
	virtual void Draw3D()      override;
				 
	virtual void DrawAlpha3D() override;
	virtual void Draw2D()      override { return; };

	class IDOL : public State
	{
	private:
		EnemyStakerStateProcessor* _owner;

	public:
		IDOL(EnemyStakerStateProcessor* owner) : _owner(owner) { };
		virtual ~IDOL() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		EnemyStakerStateProcessor* _owner;
	public:
		RUN(EnemyStakerStateProcessor* owner) : _owner(owner) {}
		virtual ~RUN() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

private:



};

