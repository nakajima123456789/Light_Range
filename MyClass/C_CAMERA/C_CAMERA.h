#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

class C_CAMERA : public Object
{
public:
	C_CAMERA() {};
	virtual ~C_CAMERA() {};
	
	virtual void C_CAMERA::Init()        override;
	virtual void C_CAMERA::Update()      override;
	virtual void C_CAMERA::Draw3D()      override { return; };

	virtual void C_CAMERA::DrawAlpha3D() override { return; };
	virtual void C_CAMERA::Draw2D()      override { return; };

	CAMERA  GetCamera() const { return camera; };
	Light   GetLight()  const { return light; };
	Vector3 GetPos()    const { return pos;    };

	void C_CAMERA::Get_Other_Tranceform(Transform* _player_transform);

private:
	CAMERA  camera;
	Light   light;
	Vector3 pos;

	Transform* player_transform;

};

