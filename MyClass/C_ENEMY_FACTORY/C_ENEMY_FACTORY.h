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

class C_ENEMY_FACTORY
{
public:
	C_ENEMY_FACTORY() {};
	virtual ~C_ENEMY_FACTORY() {};
/**
 *  @brief objectを生成し、そのインスタンスを返す関数
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
 *  @brief Productを作成する純粋仮想関数
 *  @param type Productの種類
 *  @param name Productの所有者の名前
 */
	virtual Object* CreateProduct(std::string _type, Vector3 _position) = 0;
	virtual Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) = 0;
};

class EnemyStationeryFactory : public C_ENEMY_FACTORY {
public:
	/**
	 * @brief Productを作成する関数
	 */
	Object* CreateProduct(std::string _type, Vector3 _position) override 
	{
		if (_type == "探索敵早") { return new C_ENEMY_SEARCH(1, _position, 0.02f, 30); }

		if (_type == "探索敵遅") { return new C_ENEMY_SEARCH(0, _position, 0.01f, 120); }
		ASSERT(FALSE && !"敵の名前が違う!");
	}

	Object* CreateProduct(std::string _type, std::map<int, Vector3> _position) override
	{
		if (_type == "徘徊敵"){ return new C_ENEMY_WANDER(_position);}
		ASSERT(FALSE && !"敵の名前が違う!");
	}
};