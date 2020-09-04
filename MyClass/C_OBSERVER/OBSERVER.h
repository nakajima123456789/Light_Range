#pragma once
#include "../../ESGLib.h"

// �Փ˔��� �ϑ��� �C���^�[�t�F�[�X�i �ϑ� �� �� ���ۉ��j 
class OBSERVERLISTENER
{
public:
	// ���z �f�X�g���N�^
	virtual ~OBSERVERLISTENER() {}
	// �Փ˔��肵��
	virtual void OnCollision() = 0;

	virtual void ItemOnCollision() = 0;
};

// �Փ˔��� �N���X�i �ϑ� �� �� �ʒm ���� ���j
class OBSERVER
{
public:
	// �ϑ��҂̓o�^ 
	void addListener(OBSERVERLISTENER* listener)    { listeners_.push_back(listener); };
	void removeListener(OBSERVERLISTENER* listener) { listeners_.remove(listener); };

	// �Փ˔��肵��
	void IsCollision(){
		// �Փ˔��肵�����Ƃ��ϑ��҂ɒʒm 
		OnCollisionNotify();
	}

	void ItemIsCollision()
	{
		ItemOnCollisionNotify();
	}

private:
	// �ϑ��҂ɒʒm 
	void OnCollisionNotify()
	{
		//  �Փ˔��肵�����Ƃ��ϑ��҂ɒʒm 
		for (auto listener : listeners_) 
		{ 
			listener->OnCollision();
		}
	}

	void ItemOnCollisionNotify()
	{
		//  �Փ˔��肵�����Ƃ��ϑ��҂ɒʒm 
		for (auto listener : listeners_)
		{
			listener->ItemOnCollision();
		}
	}

	static std::list<OBSERVERLISTENER*> listeners_;
};

