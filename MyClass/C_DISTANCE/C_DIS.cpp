#include "C_DIS.h"

std::list<C_DIS*> C_DIS::c_dis_list = {};

void C_DIS::Init()
{
	c_dis_list.push_back(this);
	tag = "default";
}

//�������g�����X�g�������
void C_DIS::IsRemove()
{
	auto is_it = c_dis_list.begin();
	while (is_it != c_dis_list.end()) {
		if ((*is_it) != this) {
			is_it++;}
		else {
			is_it = c_dis_list.erase(is_it);
			return;
		}
	}
}

//�w�肳�ꂽ�^�O�̍ŒZ�������擾����֐�
float C_DIS::GetTagDistance(std::string _tag)
{
	std::vector<C_DIS*> C_DIS;
	for (auto&& other : c_dis_list)
	{
		//Tag�ȊO�͒e��
		if (other->tag != _tag) continue;
		//�����̃A�h���X��e��
		if (other->GetThisDis() == this) continue; 
		//�w�肳�ꂽ�^�O����������
		C_DIS.push_back(other->GetThisDis());
	}

	if (C_DIS.size() != 0)
	{
		std::vector<float> at_distance;
		for (auto&& other : C_DIS)
		{
			//�������擾
			float other_distance = Vector3_Distance(other->target_position, this->target_position);
			//
			at_distance.push_back(other_distance);
		}
		//�ŏ��������擾
		auto&& min_dis = std::min_element(at_distance.begin(), at_distance.end(), [](float a, float b) {return a < b; });
		return  *min_dis;
	}
	else return 0.0f;
}

