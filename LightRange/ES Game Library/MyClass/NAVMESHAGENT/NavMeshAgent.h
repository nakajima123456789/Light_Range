#pragma once
#include "../../ESGLib.h"

class Astar
{
public:
	Astar::Astar();
	virtual Astar::~Astar() { };

	void Update(Vector3 _player_position, ANIMATIONMODEL& _animation_model, double _speed);

private:

	std::vector< std::vector<int> > route;
	std::vector<tstring> mapdata;
	std::vector<tstring> new_mapdata;

	void findChar(TCHAR c, int& sx, int& sy, int t);
	void findRouteSub(int cx, int cy, int d, int t);
	void findRoute(int t);
	void updateMap(int t);
	void clearMap(int t);

	void route_recalculation(int mx, int mz, int px, int pz);
	void else_when_process(int mx, int mz, int px, int pz);
	void right_when_process(int mx, int mz);
	void front_when_process(int mx, int mz);
	void back_when_process(int mx, int mz);
	void left_when_process(int mx, int mz);

	void animation_model_rotation(int mx, int my);

	int enemy_state = -1;

	int ex_integer;
	int ez_integer;

	int prev_px;
	int prev_pz;

	int enemy_x;
	int enemy_z;

	enum STATE
	{
		STATE_RIGHT,
		STATE_FRONT,
		STATE_LEFT,
		STATE_BACK,
		STATE_MAX,
		STATE_ELSE = -1,
	};

	ANIMATIONMODEL animation_model;
	Vector3 enemy_pos;

protected:
};