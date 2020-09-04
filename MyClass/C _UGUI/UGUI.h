#pragma once
#include "../C_OBJECT/Object.h"
#include "../C_OBSERVER/OBSERVER.h"
#include "../../ESGLib.h"

#include "../C_Information/Information.h"

class UGUI : public  Object, OBSERVERLISTENER
{
public:

	UGUI::UGUI();
	virtual UGUI::~UGUI();

	virtual void UGUI::Init()        override;
	virtual void UGUI::Update()      override;
	virtual void UGUI::Draw3D()      override { return; };
 
	virtual void UGUI::DrawAlpha3D() override { return; };
	virtual void UGUI::Draw2D()      override;

	//オブザーバー関数
	//PLAYERとENEMYとの衝突判定
	virtual void UGUI::OnCollision()     override;
	//PLAYERとENEMYとの衝突判定
	virtual void UGUI::ItemOnCollision() override;

	void UGUI::set_item_size(const unsigned _item_size) { item_size = _item_size; };
private:
	int UGUI::add_sprite(LPCTSTR _sprite_name);
	int UGUI::clamp(int x, int low, int high);
private:

	SPRITE red_image;
	std::vector<SPRITE> sprite;

	double gage_index = 0;
	int    item_size;
	bool   red_image_flag = false;
	float  feed_out_index = 0.f; 

	int cover_image;
	int gage_pt_image;
	int gage_sp_image;
	int obsever_enemy_image;
	float obsever_enemy_image_index = 1.0f;

	double gage_sp_image_index = 407;

	OBSERVER observer;
};

