#pragma once
#include "../../ESGLib.h"

// 衝突判定 観測者 インターフェース（ 観測 者 を 抽象化） 
class OBSERVERLISTENER
{
public:
	// 仮想 デストラクタ
	virtual ~OBSERVERLISTENER() {}
	// 衝突判定した
	virtual void OnCollision()     = 0;
	virtual void ItemOnCollision() = 0;
};

// 衝突判定 クラス（ 観測 者 に 通知 する 役）
class OBSERVER
{
public:
	// 観測者の登録 
	void addListener(OBSERVERLISTENER* listener);
	void removeListener(OBSERVERLISTENER* listener);

	// 衝突判定した
	void IsCollision();
	void ItemIsCollision();

private:
	// 観測者に通知 
	void OnCollisionNotify();
	void ItemOnCollisionNotify();

	static std::list<OBSERVERLISTENER*> listeners_;
};