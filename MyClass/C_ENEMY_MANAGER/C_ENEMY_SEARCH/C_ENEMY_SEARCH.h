#pragma once
#include "../C_ENEMY_BASE/C_ENEMY_BASE.h"
#include "../../NAVMESHAGENT/NavMeshAgent.h"

class EnemySearchStateProcessor;
class CEnemySearch;

class EnemyData
{
public:
	Vector3 pos;
	float   speed;
	float   AdvanceTime;
	int     model_type;
};

class EnemySearchStateProcessor : public  StateProcessor {
public:
	CEnemySearch* c_enemy_search;
};

class CEnemySearch : public CEnemyBase
{
public:
	CEnemySearch(EnemyData _c_enemy_date);
	virtual ~CEnemySearch();

	EnemySearchStateProcessor enemysearchstateprocessor;

	virtual void CEnemySearch::Init()        override;
	virtual void CEnemySearch::Update()      override;
	virtual void CEnemySearch::Draw3D()      override;

	virtual void CEnemySearch::DrawAlpha3D() override;
	virtual void CEnemySearch::Draw2D()      override { return; };

	class IDOL : public State
	{
	private:
		EnemySearchStateProcessor* _owner;

	public:
		IDOL(EnemySearchStateProcessor* owner) : _owner(owner) { };
		virtual ~IDOL() {};

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

	class RUN : public State
	{
	private:
		EnemySearchStateProcessor* _owner;
	public:
		RUN(EnemySearchStateProcessor* owner) : _owner(owner) {}
		virtual ~RUN() {}

		virtual int    CancelLv() { return INT_MAX; };
		virtual int    ExitTime() { return INT_MAX; };

		virtual void Update() override;
	};

private:
	//探索プログラム
	Astar nav_mesh;
	//初期ステータス設定
	EnemyData enemy_date;

};