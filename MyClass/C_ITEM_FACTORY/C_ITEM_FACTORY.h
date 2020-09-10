#pragma once

//ヘッダーファイル追加
#include "../../ESGLib.h"
#include "../C_OBJECT/Object.h"

//アイテムヘッダーファイル追加
#include "../C_ITEM_MANAGER/C_ITEM_BOOK/C_ITEM_BOOK.h"

/**
*  @brief FACTORYデザインパターン
*/

/**
 *  @brief 抽象_ENEMY_FACTORYクラス
 */

class CItemFactory
{
public:
	CItemFactory() {};
	virtual ~CItemFactory() {};

/**
 *  @brief objectを生成し、そのインスタンスを返す関数
 */
	Object* Create(std::string _type, Vector3 _position);

/**
 *  @brief Productを作成する純粋仮想関数
 *  @param type Productの種類
 *  @param name Productの所有者の名前
 */
	virtual Object* CreateProduct(std::string _type, Vector3 _position) = 0;

};

class ItemStationeryFactory : public CItemFactory
{
public:
/**
 * @brief Productを作成する関数
 */
	Object* CreateProduct(std::string _type, Vector3 _position);
};