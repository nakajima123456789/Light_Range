#pragma once
#include "../../ESGLib.h"
class Information
{
public:
	class Ui_Information
	{
	public:
		static int    point_gage;
		static double point_sutamina;
		static bool   game_over_flag;
		static bool   game_clear_flag;
		static bool   obsever_enemy_flag;
	};

	class Player_Information
	{
	public:
		static int    player_state;
	};
};

