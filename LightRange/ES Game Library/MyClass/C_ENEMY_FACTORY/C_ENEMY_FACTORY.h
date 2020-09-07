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

class EnemyFactory
{
public:
	EnemyFactory() {};
	virtual ~EnemyFactory() {};
/**
 *  @brief object�𐶐����A���̃C���X�^���X��Ԃ��֐�
 */
	Object* Create(std::string _type, Vector3 _position);
	Object* Create(std::string _type, std::map<int, Vector3> _position);
private:
/**
 *  @brief Product���쐬���鏃�����z�֐�
 *  @param type Product�̎��
 *  @param name Product�̏��L�҂̖��O
 */
	virtual Object* CreateProduct(std::string _type, Vector3 _position)                = 0;
	virtual Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) = 0;
};

class EnemyStationeryFactory : public EnemyFactory {
public:
	/**
	 * @brief Product���쐬����֐�
	 */
	Object* CreateProduct(std::string _type, Vector3 _position) override;
	Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) override;

private:

	EnemyData set_enemy_serch_data;
};