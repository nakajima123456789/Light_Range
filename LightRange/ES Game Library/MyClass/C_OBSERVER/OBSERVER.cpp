#include "OBSERVER.h"
std::list<OBSERVERLISTENER*> OBSERVER::listeners_ = {};

void OBSERVER::addListener(OBSERVERLISTENER* listener)
{ 
	listeners_.push_back(listener);
};

void OBSERVER::removeListener(OBSERVERLISTENER* listener) {
	listeners_.remove(listener); 
};

// �Փ˔��肵��
void OBSERVER::IsCollision() 
{
	// �Փ˔��肵�����Ƃ��ϑ��҂ɒʒm 
	OnCollisionNotify();
}

void OBSERVER::ItemIsCollision()
{
	ItemOnCollisionNotify();
}

// �ϑ��҂ɒʒm 
void OBSERVER::OnCollisionNotify()
{
	//  �Փ˔��肵�����Ƃ��ϑ��҂ɒʒm 
	for (auto listener : listeners_)
	{
		listener->OnCollision();
	}
}

void OBSERVER::ItemOnCollisionNotify()
{
	//  �Փ˔��肵�����Ƃ��ϑ��҂ɒʒm 
	for (auto listener : listeners_)
	{
		listener->ItemOnCollision();
	}
}


