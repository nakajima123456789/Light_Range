#include "C_ITEM_BOOK.h"

#include "../../C_SE/C_SE.h"

CItemBook::CItemBook(Vector3 _position)
{
	this->transform.position = _position;
}

void CItemBook::Init()
{
	model   = GraphicsDevice.CreateModelFromFile(_T("MODEL//book_item//book_01.X"));
	ASSERT(model != nullptr && "�A�C�e�����f����������܂���");

	item_get_se = SNDMANAGER.LoadSE(_T("SE//SE//�L�[�A�C�e���l����.wav"), 5);

	IsHitObjectsInit("item");
}

void CItemBook::Update()
{
	//�v���C���[�Ɠ���������
	if (IsHitObjects("player")) 
	{ 
		//�I�u�U�[�o�[UGUL �N���X�ɕ�
		obsever.ItemIsCollision();
		//����������
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

