#include "C_ITEM_BASE.h"

//ヒットボックス生成
void  CItemBase::IsHitObjectsInit(std::string _tags)
{
	hitbox.reset(new HitBox);
	hitbox->Init();
	hitbox->Settags(_tags);

	hitbox->SetHitBoxScale(0.5f);
	hitbox->SetHitBoxPosition(Vector3(2, 0, -2));
}

//ヒットボックス描画
void  CItemBase::IsHitObjectsDraw(Vector3 _pos)
{
	hitbox->SetHitBoxPosition(_pos);
	hitbox->Draw3D();
}

//引数に渡されたタグのヒットボックスが当たって入れTRUEを返す。
bool CItemBase::IsHitObjects(std::string tags) {
	bool result = false;
	std::list<HitBox*> HitList = hitbox->HitHitBoxlist();

	for (auto&& other : HitList) {
		if (other->tag == tags)
		{
			result = true;
		}
	}
	return result;
}