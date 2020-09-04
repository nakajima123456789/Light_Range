#pragma once
//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include <vector>

class C_DIS
{
public:
	C_DIS::C_DIS() {}; //	�R���X�g���N�^�͕K���p�u���b�N
	virtual C_DIS::~C_DIS() { IsRemove(); };

public:

//	�ϐ���`
private:

	static std::list<C_DIS*> c_dis_list;
	std::string tag;

	Vector3 target_position;

public:

	void IsTagSet(std::string _tag)           { tag = _tag; };
	void IsPosition(Vector3 _target_position) { target_position = _target_position; };

//  �֐���`
private:

	C_DIS* GetThisDis(){ return this; };

public:

	void  C_DIS::Init();
	void  C_DIS::IsRemove();

	float C_DIS::GetTagDistance(std::string _tag);
};



