#pragma once
#include "../../C_ITEM_MANAGER/C_ITEM_BASE/C_ITEM_BASE.h"
#include "../../c_Hitbox/HitBox.h"
#include "../../C_OBSERVER/OBSERVER.h"

class C_ITEM_BOOK : public C_ITEM_BASE
{
public:
	C_ITEM_BOOK(Vector3 _position);
	virtual ~C_ITEM_BOOK() { };

	virtual void C_ITEM_BOOK::Init()        override;
	virtual void C_ITEM_BOOK::Update()      override;
	virtual void C_ITEM_BOOK::Draw3D()      override;

	virtual void C_ITEM_BOOK::DrawAlpha3D() override { return; };
	virtual void C_ITEM_BOOK::Draw2D()      override { return; };

private:

	MODEL model;

	OBSERVER obsever;
};

