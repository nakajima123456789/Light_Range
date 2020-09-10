#pragma once
#include "../../ESGLib.h"
class CEffekseer_
{
public:
	CEffekseer_::CEffekseer_();
	CEffekseer_::~CEffekseer_();
	// シングルトンインスタンスの取得
	static CEffekseer_& GetInstance()
	{
		static CEffekseer_  Effekseer_Manager;
		return              Effekseer_Manager;
	}

	int       LoadEffekseer(TCHAR* filename);
	EFFEKSEER GetEffekseer(int _number);
	void      SetPosEffekseer(int _number, Vector3 _pos);

	int CEffekseer_::PlayEffekseer(int _number, double _scale, Vector3 _pos);

	void Update();
	void Draw(CAMERA& _camera);
	 
private:
	CEffekseer_(const CEffekseer_&)            = delete;
	CEffekseer_& operator=(const CEffekseer_&) = delete;
	CEffekseer_(CEffekseer_&&)                 = delete;
	CEffekseer_& operator=(CEffekseer_&&)      = delete;

	std::vector<EFFEKSEER> effekseer;

};
#define EffekseerMgr CEffekseer_::GetInstance()