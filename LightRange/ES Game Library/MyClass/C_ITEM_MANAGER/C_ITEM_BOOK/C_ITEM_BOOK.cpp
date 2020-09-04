#include "C_ITEM_BOOK.h"

#include "../../C_SE/C_SE.h"

C_ITEM_BOOK::C_ITEM_BOOK(Vector3 _position)
{
	this->transform.position = _position;
}

void C_ITEM_BOOK::Init()
{
	model   = GraphicsDevice.CreateModelFromFile(_T("MODEL//book_item//book_01.X"));

	item_se = SNDMANAGER.LoadSE(_T("SE//SE//キーアイテム獲得時.wav"), 5);

	string tag = "item";

	IsHitObjectsInit(tag);
}

void C_ITEM_BOOK::Update()
{
	if (IsHitObjects("player")) { 
		obsever.ItemIsCollision();
		this->IsRemove_flag(true); 
		SNDMANAGER.PlaySE(item_se);
	};
}

void C_ITEM_BOOK::Draw3D()
{
	model->SetPosition((this->transform.position));
	model->SetRotation(this->transform.rotation);
	model->SetScale(this->transform.scale);
	model->Draw();

	IsHitObjectsDraw((this->transform.position));
}

