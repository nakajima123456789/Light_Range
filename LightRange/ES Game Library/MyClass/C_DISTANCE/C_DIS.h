#pragma once
//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include <vector>

class C_DIS
{
public:
	C_DIS::C_DIS() {}; //	コンストラクタは必ずパブリック
	virtual C_DIS::~C_DIS() { IsRemove(); };

public:

//	変数定義
private:

	static std::list<C_DIS*> c_dis_list;
	std::string tag;

	Vector3 target_position;

public:

	void IsTagSet(std::string _tag)           { tag = _tag; };
	void IsPosition(Vector3 _target_position) { target_position = _target_position; };

//  関数定義
private:

	C_DIS* GetThisDis(){ return this; };

public:

	void  C_DIS::Init();
	void  C_DIS::IsRemove();

	float C_DIS::GetTagDistance(std::string _tag);
};



