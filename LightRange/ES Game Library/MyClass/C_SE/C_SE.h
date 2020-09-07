#pragma once

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include <vector>

//------------------------------------------------------------------------------
//	SEManager�N���X��`
//------------------------------------------------------------------------------

class C_SE {
public:
	virtual ~C_SE(){};

	// �V���O���g���C���X�^���X�̎擾
	static C_SE& GetInstance()
	{ 
		static C_SE theSEManager;
		return theSEManager;
	}

	bool Initialize();

	//SE�̓o�^�@SE�̏d���Đ��̉\(multiple)
	int LoadSE(TCHAR* filename, const UINT multiple = 1);

	void PlaySE(int index);
	
	void LoadBGM(TCHAR* filename) { bgm = SoundDevice.CreateMusicFromFile(filename); };
	bool PlayBGM();

	int LoadLopeSE(TCHAR* filename);

	void PlayLopeSE(int _number);

	bool IsSeVolume(int _set_number);

	void StopLopeSE(int _number) { LopeSE[_number]->Stop(); };

	std::vector<SOUND> GetLopeSE() const { return LopeSE; };

	std::vector<SOUND> LopeSE;

	MUSIC GetBgm() { return bgm; };

	void  DistanceSeV(float _dis, float  _min_dis, int _number);

private:
	C_SE() {};
	
	MUSIC bgm;

	std::vector<float> volume;
	int C_SE::clamp(int x, int low, int high);

	// �����o�ϐ�
	std::vector< std::vector<SOUND> > se;

	C_SE(const C_SE&) = delete;
	C_SE& operator=(const C_SE&) = delete;
	C_SE(C_SE&&) = delete;
	C_SE& operator=(C_SE&&) = delete;
};

//------------------------------------------------------------------------------
//	�C�����C���֐���`
//------------------------------------------------------------------------------
inline C_SE& SNDMgr() { return C_SE::GetInstance(); }
#define SNDMANAGER C_SE::GetInstance()