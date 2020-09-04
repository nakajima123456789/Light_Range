#pragma once
#include "../../ESGLib.h"

// 衝突判定 観測者 インターフェース（ 観測 者 を 抽象化） 
class OBSERVERLISTENER
{
public:
	// 仮想 デストラクタ
	virtual ~OBSERVERLISTENER() {}
	// 衝突判定した
	virtual void OnCollision() = 0;

	virtual void ItemOnCollision() = 0;
};

// 衝突判定 クラス（ 観測 者 に 通知 する 役）
class OBSERVER
{
public:
	// 観測者の登録 
	void addListener(OBSERVERLISTENER* listener)    { listeners_.push_back(listener); };
	void removeListener(OBSERVERLISTENER* listener) { listeners_.remove(listener); };

	// 衝突判定した
	void IsCollision(){
		// 衝突判定したことを観測者に通知 
		OnCollisionNotify();
	}

	void ItemIsCollision()
	{
		ItemOnCollisionNotify();
	}

private:
	// 観測者に通知 
	void OnCollisionNotify()
	{
		//  衝突判定したことを観測者に通知 
		for (auto listener : listeners_) 
		{ 
			listener->OnCollision();
		}
	}

	void ItemOnCollisionNotify()
	{
		//  衝突判定したことを観測者に通知 
		for (auto listener : listeners_)
		{
			listener->ItemOnCollision();
		}
	}

	static std::list<OBSERVERLISTENER*> listeners_;
};

