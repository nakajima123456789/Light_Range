#pragma once
//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include <vector>

//------------------------------------------------------------------------------
//	���̊֐��͂Q�̍��W�̋����𒲂׃^�O�ɂ��ŒZ�������擾�o���܂��B
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
	//sharedptr�ŊǗ�
	virtual ~CDis() { IsRemove(); };

	void  Init();
	void  IsRemove();
	
	//�^�O�̍ŏ��l���擾�֐�
	float GetTagDistance(std::string _tag);

	//�Ăяo�����̃^�O���w��
	void IsTagSet(std::string _tag);

	//�Ăяo�����̃��f�����W���擾
	void IsPosition(Vector3 _pos);

	bool TagSerch(std::string _tag);

};