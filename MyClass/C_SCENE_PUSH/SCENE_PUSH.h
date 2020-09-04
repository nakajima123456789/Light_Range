#pragma once
#include "../../ESGLib.h"
#include <vector>;

// ボタン クリック 観測 者 インターフェース（ 観測 者 を 抽象化） 
class ButtonClickListener
{
public:
	// 仮想 デストラクタ
	virtual ~ButtonClickListener() {}
	// クリック さ れ た
	virtual void onClick() = 0;
};

// ボタン クラス（ 観測 者 に 通知 する 役）
class Button
{
public:
	// 観測 者 の 登録 
	void addListener(ButtonClickListener* listener) { listeners_.push_back(listener); }
	// クリック さ れ た
	void click()
	{
		// ボタン が 押さ れ た こと を 観測 者 に 通知 
		notify();
	}

	// シングルトンインスタンスの取得
	static Button& GetInstance()
	{
		static Button buttom;
		return theSEManager;
	}

private:
	// 観測 者 に 通知 
	void notify()
	{
		// ボタン が 押さ れ た こと を 観測 者 に 通知 
		for (auto listener : listeners_) { listener->onClick(); }
	}
	std::vector<ButtonClickListener*> listeners_;

	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;
	Button(Button&&) = delete;
	Button& operator=(Button&&) = delete;
};
#define BUTTON_MANAGER Button::GetInstance()

