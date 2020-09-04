#pragma once
#include "../../C_OBJECT/Object.h"
#include "../../../ESGLib.h"
#include "../../C_HITBOX/HitBox.h"

class C_ITEM_BASE : public Object
{
public:
	C_ITEM_BASE() {};
	virtual ~C_ITEM_BASE() {};

	virtual void C_ITEM_BASE::Init()        override  = 0;
	virtual void C_ITEM_BASE::Update()      override  = 0;
	virtual void C_ITEM_BASE::Draw3D()      override  = 0;

	virtual void C_ITEM_BASE::DrawAlpha3D() override  = 0;
	virtual void C_ITEM_BASE::Draw2D()      override  = 0;

private:

protected:

	int item_se;

	std::shared_ptr <HitBox> hitbox;

protected:
	void   C_ITEM_BASE::IsHitObjectsInit(std::string _tags);
	void   C_ITEM_BASE::IsHitObjectsDraw(Vector3 _pos);

	bool   C_ITEM_BASE::IsHitObjects(std::string tags);

};

