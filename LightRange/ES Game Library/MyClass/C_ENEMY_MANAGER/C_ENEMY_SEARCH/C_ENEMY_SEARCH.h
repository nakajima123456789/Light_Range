#pragma once
#include "../C_ENEMY_BASE/C_ENEMY_BASE.h"
#include "../../NAVMESHAGENT/NavMeshAgent.h"

class ENEMYSEARCHSTATEPROCESSOR;
class C_ENEMY_SEARCH;

class ENEMYSEARCHSTATEPROCESSOR : public  StateProcessor {
public:
	C_ENEMY_SEARCH* c_enemy_search;
};

class C_ENEMY_SEARCH : public C_ENEMY_BASE
{
public:
	C_ENEMY_SEARCH(int _model_type, Vector3 _position, float _speed, double _animation_speed);
	virtual ~C_ENEMY_SEARCH();

	ENEMYSEARCHSTATEPROCESSOR enemysearchstateprocessor;

	virtual void C_ENEMY_SEARCH::Init()        override;
	virtual void C_ENEMY_SEARCH::Update()      override;
	virtual void C_ENEMY_SEARCH::Draw3D()      override;

	virtual void C_ENEMY_SEARCH::DrawAlpha3D() override;
	virtual void C_ENEMY_SEARCH::Draw2D()      override { return; };

	class IDOL : public State
	{
	private:
		ENEMYSEARCHSTATEPROCESSOR* _owner;

	public:
		IDOL(ENEMYSEARCHSTATEPROCESSOR* owner) : _owner(owner) { };
		virtual ~IDOL() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		ENEMYSEARCHSTATEPROCESSOR* _owner;
	public:
		RUN(ENEMYSEARCHSTATEPROCESSOR* owner) : _owner(owner) {}
		virtual ~RUN() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

private:
	NavMeshAgent nav_mesh_agent;

	float  speed; 
	double animation_speed;
};