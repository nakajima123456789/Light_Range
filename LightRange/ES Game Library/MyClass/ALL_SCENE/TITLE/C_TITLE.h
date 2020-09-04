#pragma once
#include "../SCENEMANAGER/BaseScreen.h"

class C_TITLE : public BaseScene
{
public:

	C_TITLE() {};
	virtual ~C_TITLE() {};

	virtual void Initialize()  override;
	virtual void Update()      override;
	virtual void Draw3D()      override { return; };
	virtual void Draw2D()      override;
	virtual void DrawAlpha3D() override { return; };

private:

	SPRITE sprite;
	Vector3 sprite_pos;

	void Add_Sprite(LPCTSTR _sprite_name);
	void Add_Sprite_Pos(Vector3 _sprite_pos);

	std::vector<SPRITE> sprite_list_name;
	std::vector<Vector3> sprite_list_pos;

	MEDIA media;

	int ƒ¢time = 1;
	int end_time = 0;
	bool scene_flag = false;
};

