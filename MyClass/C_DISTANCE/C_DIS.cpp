#include "C_DIS.h"

std::list<CDis*> CDis::c_dis_list = {};

void CDis::Init()
{
	c_dis_list.push_back(this);
	tag = "default";
}

//自分自身をリストから消す
void CDis::IsRemove()
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

void CDis::IsTagSet(std::string _tag)
{ 
	ASSERT(_tag != "default" && "default以外にしてください。");
	tag = _tag;
};

void CDis::IsPosition(Vector3 _pos)
{
	pos = _pos;
}

//現在登録されているタグを調べ存在しないタグであれば停止する
bool CDis::TagSerch(std::string _tag)
{
	bool flag = false;
	for (auto&& h : c_dis_list) {
		if (h->tag == _tag) { flag = true; };
	}
	return flag;
}


//タグの中で一番最小値を調べ返す。
float CDis::GetTagDistance(std::string _tag)
{
	ASSERT(TagSerch(_tag) && "tagが存在していない!");

	std::vector<CDis*> C_DIS;
	for (auto&& other : c_dis_list)
	{
		if (other->tag != _tag) continue;
		if (other->GetThisDis() == this) continue; 
		C_DIS.push_back(other->GetThisDis());
	}
	if (C_DIS.size() != 0)
	{
		std::vector<float> at_distance;
		for (auto&& other : C_DIS)
		{
			float other_distance = Vector3_Distance(other->pos, this->pos);
			at_distance.push_back(other_distance);
		}
		auto&& min_dis = std::min_element(at_distance.begin(), at_distance.end(), [](float a, float b) {return a < b; });
		return  *min_dis;
	}
	else return 0.0f;
}

