#pragma once
#include "../../ESGLib.h"
#include <vector>;

// �{�^�� �N���b�N �ϑ� �� �C���^�[�t�F�[�X�i �ϑ� �� �� ���ۉ��j 
class ButtonClickListener
{
public:
	// ���z �f�X�g���N�^
	virtual ~ButtonClickListener() {}
	// �N���b�N �� �� ��
	virtual void onClick() = 0;
};

// �{�^�� �N���X�i �ϑ� �� �� �ʒm ���� ���j
class Button
{
public:
	// �ϑ� �� �� �o�^ 
	void addListener(ButtonClickListener* listener) { listeners_.push_back(listener); }
	// �N���b�N �� �� ��
	void click()
	{
		// �{�^�� �� ���� �� �� ���� �� �ϑ� �� �� �ʒm 
		notify();
	}

	// �V���O���g���C���X�^���X�̎擾
	static Button& GetInstance()
	{
		static Button buttom;
		return theSEManager;
	}

private:
	// �ϑ� �� �� �ʒm 
	void notify()
	{
		// �{�^�� �� ���� �� �� ���� �� �ϑ� �� �� �ʒm 
		for (auto listener : listeners_) { listener->onClick(); }
	}
	std::vector<ButtonClickListener*> listeners_;

	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;
	Button(Button&&) = delete;
	Button& operator=(Button&&) = delete;
};
#define BUTTON_MANAGER Button::GetInstance()

