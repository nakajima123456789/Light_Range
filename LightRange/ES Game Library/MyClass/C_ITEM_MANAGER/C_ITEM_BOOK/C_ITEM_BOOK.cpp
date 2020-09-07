#include "C_ITEM_BOOK.h"

#include "../../C_SE/C_SE.h"

CItemBook::CItemBook(Vector3 _position)
{
	this->transform.position = _position;
}

void CItemBook::Init()
{
	model   = GraphicsDevice.CreateModelFromFile(_T("MODEL//book_item//book_01.X"));
	ASSERT(model != nullptr && "アイテムモデルが見つかりません");

	item_get_se = SNDMANAGER.LoadSE(_T("SE//SE//キーアイテム獲得時.wav"), 5);

	IsHitObjectsInit("item");
}

void CItemBook::Update()
{
	//プレイヤーと当たったら
	if (IsHitObjects("player")) 
	{ 
		//オブザーバーUGUL クラスに報告
		obsever.ItemIsCollision();
		//自分を消す
		this->IsRemove_flag(true); 
		SNDMANAGER.PlaySE(item_get_se);
	};
}

void CItemBook::Draw3D()
{
	model->SetPosition((this->transform.position));
	model->SetRotation(this->transform.rotation);
	model->SetScale(this->transform.scale);
	model->Draw();

	IsHitObjectsDraw((this->transform.position));
}

