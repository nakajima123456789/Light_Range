#pragma once
//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include <vector>

//------------------------------------------------------------------------------
//	この関数は２つの座標の距離を調べタグにより最短距離を取得出来ます。
//------------------------------------------------------------------------------
class CDis
{
private:
	CDis* GetThisDis(){ return this; };

	static std::list<CDis*> c_dis_list;

	std::string tag;
	Vector3     pos;
public:

	CDis() {};
	//sharedptrで管理
	virtual ~CDis() { IsRemove(); };

	void  Init();
	void  IsRemove();
	
	//タグの最小値を取得関数
	float GetTagDistance(std::string _tag);

	//呼び出し元のタグを指定
	void IsTagSet(std::string _tag);

	//呼び出し元のモデル座標を取得
	void IsPosition(Vector3 _pos);

	bool TagSerch(std::string _tag);

};