#pragma once
#include "../../C_ITEM_MANAGER/C_ITEM_BASE/C_ITEM_BASE.h"
#include "../../c_Hitbox/HitBox.h"
#include "../../C_OBSERVER/OBSERVER.h"

class CItemBook : public CItemBase
{
public:
	CItemBook(Vector3 _position);
	virtual ~CItemBook() { };

	virtual void CItemBook::Init()        override;
	virtual void CItemBook::Update()      override;
	virtual void CItemBook::Draw3D()      override;

	virtual void CItemBook::DrawAlpha3D() override { return; };
	virtual void CItemBook::Draw2D()      override { return; };

private:

	MODEL model;
	OBSERVER obsever;

	int item_get_se;

};

