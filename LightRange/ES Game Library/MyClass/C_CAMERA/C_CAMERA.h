#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

class CCamera_ : public Object
{
public:
	CCamera_() {};
	virtual ~CCamera_() {};
	
	virtual void CCamera_::Init()        override;
	virtual void CCamera_::Update()      override;
	virtual void CCamera_::Draw3D()      override { return; };

	virtual void CCamera_::DrawAlpha3D() override { return; };
	virtual void CCamera_::Draw2D()      override { return; };

	virtual void CCamera_::DrawEnd()      override;

	CAMERA  GetCamera() const { return camera; };
	Light   GetLight()  const { return light; };
	Vector3 GetPos()    const { return pos;};

	void CCamera_::GetPlayerTranceform(Transform* _player_transform);

private:
	CAMERA  camera;
	Light   light;
	Vector3 pos;

	Transform* player_transform;

};

