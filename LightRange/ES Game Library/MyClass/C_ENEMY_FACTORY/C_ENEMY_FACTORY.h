#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

//�G�̃w�b�_�[�t�@�C���ǉ�
#include "../C_ENEMY_MANAGER/C_ENEMY_WANDER/C_ENEMY_WANDER.h"
#include "../C_ENEMY_MANAGER/C_ENEMY_SEARCH/C_ENEMY_SEARCH.h"

/**
 *  @brief FACTORY�f�U�C���p�^�[��
 */

/**
 *  @brief ����_ENEMY_FACTORY�N���X
 */

class C_ENEMY_FACTORY
{
public:
	C_ENEMY_FACTORY() {};
	virtual ~C_ENEMY_FACTORY() {};
/**
 *  @brief object�𐶐����A���̃C���X�^���X��Ԃ��֐�
 */
	Object* Create(std::string _type, Vector3 _position) {
		Object* object = CreateProduct(_type, _position);
		return object;
	}

	Object* Create(std::string _type, std::map<int, Vector3> _position) {
		Object* object = CreateProduct(_type, _position);
		return object;
	}
private:
/**
 *  @brief Product���쐬���鏃�����z�֐�
 *  @param type Product�̎��
 *  @param name Product�̏��L�҂̖��O
 */
	virtual Object* CreateProduct(std::string _type, Vector3 _position) = 0;
	virtual Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) = 0;
};

class EnemyStationeryFactory : public C_ENEMY_FACTORY {
public:
	/**
	 * @brief Product���쐬����֐�
	 */
	Object* CreateProduct(std::string _type, Vector3 _position) override 
	{
		if (_type == "�T���G��") { return new C_ENEMY_SEARCH(1, _position, 0.02f, 30); }

		if (_type == "�T���G�x") { return new C_ENEMY_SEARCH(0, _position, 0.01f, 120); }
		ASSERT(FALSE && !"�G�̖��O���Ⴄ!");
	}

	Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) override
	{
		if (_type == "�p�j�G"){ return new C_ENEMY_WANDER(_position);}
		ASSERT(FALSE && !"�G�̖��O���Ⴄ!");
	}
};