#include "OBSERVER.h"
std::list<OBSERVERLISTENER*> OBSERVER::listeners_ = {};

void OBSERVER::addListener(OBSERVERLISTENER* listener)
{ 
	listeners_.push_back(listener);
};

void OBSERVER::removeListener(OBSERVERLISTENER* listener) {
	listeners_.remove(listener); 
};

// 衝突判定した
void OBSERVER::IsCollision() 
{
	// 衝突判定したことを観測者に通知 
	OnCollisionNotify();
}

void OBSERVER::ItemIsCollision()
{
	ItemOnCollisionNotify();
}

// 観測者に通知 
void OBSERVER::OnCollisionNotify()
{
	//  衝突判定したことを観測者に通知 
	for (auto listener : listeners_)
	{
		listener->OnCollision();
	}
}

void OBSERVER::ItemOnCollisionNotify()
{
	//  衝突判定したことを観測者に通知 
	for (auto listener : listeners_)
	{
		listener->ItemOnCollision();
	}
}


