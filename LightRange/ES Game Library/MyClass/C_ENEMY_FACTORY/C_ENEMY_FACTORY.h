#pragma once
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

//敵のヘッダーファイル追加
#include "../C_ENEMY_MANAGER/C_ENEMY_WANDER/C_ENEMY_WANDER.h"
#include "../C_ENEMY_MANAGER/C_ENEMY_SEARCH/C_ENEMY_SEARCH.h"

/**
 *  @brief FACTORYデザインパターン
 */

/**
 *  @brief 抽象_ENEMY_FACTORYクラス
 */

class EnemyFactory
{
public:
	EnemyFactory() {};
	virtual ~EnemyFactory() {};
/**
 *  @brief objectを生成し、そのインスタンスを返す関数
 */
	Object* Create(std::string _type, Vector3 _position);
	Object* Create(std::string _type, std::map<int, Vector3> _position);
private:
/**
 *  @brief Productを作成する純粋仮想関数
 *  @param type Productの種類
 *  @param name Productの所有者の名前
 */
	virtual Object* CreateProduct(std::string _type, Vector3 _position)                = 0;
	virtual Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) = 0;
};

class EnemyStationeryFactory : public EnemyFactory {
public:
	/**
	 * @brief Productを作成する関数
	 */
	Object* CreateProduct(std::string _type, Vector3 _position) override;
	Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) override;

private:

	EnemyData set_enemy_serch_data;
};