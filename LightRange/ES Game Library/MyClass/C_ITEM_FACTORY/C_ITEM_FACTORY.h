#pragma once

//�w�b�_�[�t�@�C���ǉ�
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

//�A�C�e���w�b�_�[�t�@�C���ǉ�
#include "../C_ITEM_MANAGER/C_ITEM_BOOK/C_ITEM_BOOK.h"

/**
*  @brief FACTORY�f�U�C���p�^�[��
*/

/**
 *  @brief ����_ENEMY_FACTORY�N���X
 */

class C_ITEM_FACTORY
{
public:
	C_ITEM_FACTORY() {};
	virtual ~C_ITEM_FACTORY() {};

/**
 *  @brief object�𐶐����A���̃C���X�^���X��Ԃ��֐�
 */
	Object* Create(std::string _type, Vector3 _position) {
		Object* object = CreateProduct(_type, _position);
		return object;
	}

/**
 *  @brief Product���쐬���鏃�����z�֐�
 *  @param type Product�̎��
 *  @param name Product�̏��L�҂̖��O
 */
	virtual Object* CreateProduct(std::string _type, Vector3 _position) = 0;

};

class ItemStationeryFactory : public C_ITEM_FACTORY
{
public:
/**
 * @brief Product���쐬����֐�
 */
	Object* CreateProduct(std::string _type, Vector3 _position) override
	{
		if (_type == "�A�C�e��") { return new C_ITEM_BOOK(_position); }
		ASSERT(FALSE && !"�A�C�e���̖��O���Ⴄ!");
	}
};