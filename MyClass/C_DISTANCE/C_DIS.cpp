#include "C_DIS.h"

std::list<C_DIS*> C_DIS::c_dis_list = {};

void C_DIS::Init()
{
	c_dis_list.push_back(this);
	tag = "default";
}

//自分自身をリストから消す
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

//指定されたタグの最短距離を取得する関数
float C_DIS::GetTagDistance(std::string _tag)
{
	std::vector<C_DIS*> C_DIS;
	for (auto&& other : c_dis_list)
	{
		//Tag以外は弾く
		if (other->tag != _tag) continue;
		//自分のアドレスを弾く
		if (other->GetThisDis() == this) continue; 
		//指定されたタグだけを入れる
		C_DIS.push_back(other->GetThisDis());
	}

	if (C_DIS.size() != 0)
	{
		std::vector<float> at_distance;
		for (auto&& other : C_DIS)
		{
			//距離を取得
			float other_distance = Vector3_Distance(other->target_position, this->target_position);
			//
			at_distance.push_back(other_distance);
		}
		//最小距離を取得
		auto&& min_dis = std::min_element(at_distance.begin(), at_distance.end(), [](float a, float b) {return a < b; });
		return  *min_dis;
	}
	else return 0.0f;
}

