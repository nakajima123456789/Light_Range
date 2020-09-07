#pragma once
#include "../../C_OBJECT/Object.h"
#include "../../../ESGLib.h"
#include "../../C_HITBOX/HitBox.h"

class CItemBase : public Object
{
public:
	CItemBase() {};
	virtual ~CItemBase() {};

	virtual void Init()        override  = 0;
	virtual void Update()      override  = 0;
	virtual void Draw3D()      override  = 0;

	virtual void DrawAlpha3D() override  = 0;
	virtual void Draw2D()      override  = 0;

private:

protected:
	std::shared_ptr <HitBox> hitbox;

	void   IsHitObjectsInit(std::string _tags);
	void   IsHitObjectsDraw(Vector3 _pos);
	bool   IsHitObjects(std::string tags);
};

