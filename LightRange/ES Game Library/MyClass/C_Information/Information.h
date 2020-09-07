#pragma once
#include "../../ESGLib.h"
class Information
{
public:
	class Ui_Information
	{
	public:
		//アイテムポイントゲージ
		static int    point_gage;
		//スタミナゲージ
		static double point_sutamina;
		//ゲームオーバー　フラッグ　TRUEで起動
		static bool   game_over_flag;
		//ゲームクリア　　フラッグ　TRUEで起動
		static bool   game_clear_flag;
		//
		static bool   obsever_enemy_flag;
	};

	class Player_Information
	{
	public:
		//プレイヤーの状態を取得
		static int    player_state;
	};
};

