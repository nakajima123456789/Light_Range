#pragma once
#include "../../ESGLib.h"
class Information
{
public:
	class Ui_Information
	{
	public:
		//�A�C�e���|�C���g�Q�[�W
		static int    point_gage;
		//�X�^�~�i�Q�[�W
		static double point_sutamina;
		//�Q�[���I�[�o�[�@�t���b�O�@TRUE�ŋN��
		static bool   game_over_flag;
		//�Q�[���N���A�@�@�t���b�O�@TRUE�ŋN��
		static bool   game_clear_flag;
		//
		static bool   obsever_enemy_flag;
	};

	class Player_Information
	{
	public:
		//�v���C���[�̏�Ԃ��擾
		static int    player_state;
	};
};

