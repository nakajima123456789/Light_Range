#include "C_ITEM_BASE.h"

void  C_ITEM_BASE::IsHitObjectsInit(std::string _tags)
{
	hitbox.reset(new HitBox);
	hitbox->Init();
	hitbox->Settags(_tags);

	hitbox->SetHitBoxScale(0.5f);
	hitbox->SetHitBoxPosition(Vector3(2, 0, -2));
}

void  C_ITEM_BASE::IsHitObjectsDraw(Vector3 _pos)
{
	hitbox->SetHitBoxPosition(_pos);
	hitbox->Draw3D();
}

bool C_ITEM_BASE::IsHitObjects(std::string tags) {
	ASSERT(hitbox->Tag_Sarch(tags) && "指定したHITBOXのタグが存在していません。");
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