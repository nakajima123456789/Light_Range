#include "NavMeshAgent.h"

Astar::Astar()
{
	// ファイルを開く //マップデータ取得
	FILE* fp = fopen("File//MAP.txt", "r");
	// マップデータを読み込む
	TCHAR str[CHAR_MAX + 1];
		
	while (_fgetts(str, sizeof str - 1, fp) != NULL){mapdata.push_back(str);}
	// ファイルを閉じる
	fclose(fp);

	//マップにある不必要な文字を消す
	for (int y = 0; y < mapdata.size(); y++){
		for (int x = 0; x < mapdata[y].size(); x++){
			if (mapdata[y][x] != ' ' && mapdata[y][x] != '#'){
				mapdata[y][x] = ' ';
			}
		}
	}
	new_mapdata = mapdata;
};


void Astar::Update(Vector3 _player_position, ANIMATIONMODEL& _animation_model,double _speed)
{
	animation_model = _animation_model;

	enemy_pos = animation_model->GetPosition();

	//座標が一つずれているので+-1をし補正 / 2をする事により二次元配列でどの場所にいるかに変換する　mzの-は3Dの世界では下になるので
	int mx =  ((int)enemy_pos.x + 1) / 2;
	int mz = -((int)enemy_pos.z - 1) / 2;
	int px =  ((int)_player_position.x + 1) / 2;
	int pz = -((int)_player_position.z - 1) / 2;

	//敵がPLAYERに重なったりもしもマイナス1になり止まらないように再度MAPの計算をする
	if (enemy_state == STATE_ELSE) { else_when_process(mx, mz, px, pz); }

	enemy_x =  (int)animation_model->GetPosition().x;
	enemy_z = -(int)animation_model->GetPosition().z;

	//敵が過去の座標と同じで無かったら何故ならルート再計算を頻繫にやっては行けないから
	if (ex_integer != enemy_x || ez_integer != enemy_z) {

		//enemy_state(プレイヤーの向いてる方向)により別のの処理をする内容は似ているがマップサイズにより調整が必要
		switch (enemy_state)
		{
		case STATE_LEFT:
			left_when_process(mx, mz);
			break;
		case STATE_RIGHT:
			right_when_process(mx, mz);
			break;
		case STATE_BACK:
			back_when_process(mx, mz);
			break;
		case STATE_FRONT:
			front_when_process(mx, mz);
			break;
		}

		//ここで古い座標はex_integer、ez_integerにいれていく
		ex_integer = enemy_x;
		ez_integer = enemy_z;
	}

	if (enemy_state != -1) {animation_model->Move(Vector3(0, 0, -_speed));}

	//自機が同じ座標にいなかったら処理を実行する
	if (prev_px != px || prev_pz != pz)
	{
		prev_px = px;
		prev_pz = pz;

		route_recalculation(mx, mz, px, pz);
	}
}

void Astar::findChar(TCHAR c, int& sx, int& sy, int t)
{
	for (int y = 0; y < mapdata.size(); ++y) {
		for (int x = 0; x < mapdata[y].size(); ++x) {
			if (mapdata[y][x] == c) {
				sx = x;
				sy = y;
				return;
			}
		}
	}
}

//ここではドットを打つ処理をする今ここでは空白の所だけに対し行うどんどん追加していく
void Astar::findRouteSub(int cx, int cy, int d, int t)
{
	if (d < route[cy][cx]) {
		route[cy][cx] = d;
	}
	else { return; }
	if (cy - 1 >= 0 && (mapdata[cy - 1][cx] == ' ')) {
		findRouteSub(cx, cy - 1, d + 1, t);
	}
	if (cy + 1 < mapdata[cy].size() && mapdata[cy + 1][cx] == ' ') {
		findRouteSub(cx, cy + 1, d + 1, t);
	}
	if (cx - 1 >= 0 && mapdata[cy][cx - 1] == ' ') {
		findRouteSub(cx - 1, cy, d + 1, t);
	}
	if (cx + 1 < mapdata[cy].size() && mapdata[cy][cx + 1] == ' ') {
		findRouteSub(cx + 1, cy, d + 1, t);
	}
}

void Astar::findRoute(int t)
{
	for (int i = 0; i < mapdata.size(); ++i) {
		UINT u = mapdata[i].size();
		std::vector<int> line(mapdata[i].size(), INT_MAX);
		route.push_back(line);
	}
	int sx;
	int sy;
	findChar('S', sx, sy, t);
	findRouteSub(sx, sy, 0, t);
}

void Astar::updateMap(int t)
{
	int cx;
	int cy;
	findChar('G', cx, cy, t);
	for (;;) {
		if (cy - 1 >= 0 && route[cy - 1][cx] < route[cy][cx]) {
			cy = cy - 1;
		}
		else if (cy + 1 < mapdata.size() && route[cy + 1][cx] < route[cy][cx]) {
			cy = cy + 1;
		}
		else if (cx - 1 >= 0 && route[cy][cx - 1] < route[cy][cx]) {
			cx = cx - 1;
		}
		else if (cx + 1 < mapdata[cy].size() && route[cy][cx + 1] < route[cy][cx]) {
			cx = cx + 1;
		}
		if (mapdata[cy][cx] == 'S') {
			break;
		}
		mapdata[cy][cx] = '.';
	}
}

void Astar::clearMap(int t)
{
	for (int y = 0; y < mapdata.size(); y++) {
		for (int x = 0; x < mapdata[y].size(); x++) {
			if (mapdata[y][x] != '#')
				mapdata[y][x] = ' ';
		}
	}
	std::vector< std::vector<int> >().swap(route);
}


//敵の操作はローカル座標で動かしているので回転で制御する
void Astar::animation_model_rotation(int mx, int my)
{
	if (mapdata[my][mx + 1] == '.')
	{
		//右にドットがあったら回転する
		enemy_state = STATE_RIGHT;
		animation_model->SetRotation(Vector3(0, 270, 0));
	}
	else if (mapdata[my + 1][mx] == '.')
	{
		//上にドットがあったら回転する
		enemy_state = STATE_FRONT;
		animation_model->SetRotation(Vector3(0, 0, 0));
	}
	else if (mapdata[my][mx - 1] == '.')
	{
		//左にドットがあったら回転する
		enemy_state = STATE_LEFT;
		animation_model->SetRotation(Vector3(0, 90, 0));
	}
	else if (mapdata[my - 1][mx] == '.')
	{
		//したにドットがあったら回転する
		enemy_state = STATE_BACK;
		animation_model->SetRotation(Vector3(0, 180, 0));
	}
	else {
		//万が一
		enemy_state = STATE_ELSE;
	}
	//敵のfloat座標が奇数の時偶数にする
	int even_x = (int)enemy_pos.x;
	if (even_x > 0) {
		even_x += 4 + (1 & (even_x / 10));
	}
	else {
		even_x -= 4 + (1 & (even_x / 10));
	}
	even_x = even_x - (even_x % 10);

	int even_y = (int)enemy_pos.z;
	if (even_y > 0) {
		even_y += 4 + (1 & (even_y / 10));
	}
	else {
		even_y -= 4 + (1 & (even_y / 10));
	}
	even_y = even_y - (even_y % 10);

	enemy_pos.x = even_x;
	enemy_pos.z = even_y;
}

void Astar::else_when_process(int mx, int mz, int px, int pz)
{
	enemy_pos.x = mx * 2;
	enemy_pos.z = -mz * 2;
	animation_model->SetPosition(enemy_pos);

	route_recalculation(mx, mz, px, pz);
	animation_model_rotation(mx, mz);

}

void Astar::right_when_process(int mx, int mz)
{
	if (ex_integer % 2 == 1 && enemy_x % 2 == 0)
	{
		mx = enemy_x / 2;
		mz = (enemy_z + 1) / 2;

		mapdata[mz][mx] = ' ';

		animation_model_rotation(mx, mz);
	}
}

void Astar::front_when_process(int mx, int mz)
{
	if (ez_integer % 2 == 1 && enemy_z % 2 == 0)
	{
		mx = (enemy_x + 1) / 2;
		mz = enemy_z / 2;

		mapdata[mz][mx] = ' ';

		animation_model_rotation(mx, mz);
	}
}

void Astar::back_when_process(int mx, int mz)
{
	if (ez_integer % 2 == 0 && enemy_z % 2 == 1)
	{
		mx = (enemy_x + 1) / 2;
		mz = enemy_z / 2 + 1;

		mapdata[mz][mx] = ' ';

		animation_model_rotation(mx, mz);
	}
}

void Astar::left_when_process(int mx, int mz)
{
	if (ex_integer % 2 == 0 && enemy_x % 2 == 1)
	{
		mx = enemy_x / 2 + 1;
		mz = (enemy_z + 1) / 2;

		mapdata[mz][mx] = ' ';

		animation_model_rotation(mx, mz);
	}
}
//ルートの再計算の処理
void Astar::route_recalculation(int mx, int mz, int px, int pz)
{
	//マップクリア	
	clearMap(0);
	mapdata = new_mapdata;
	//敵の座標にSを配列START
	mapdata[mz][mx] = 'S';
	//自機の座標にGを配列GOAL
	mapdata[pz][px] = 'G';

	//SとGが同じ場所に無かったら
	if (mapdata[mz][mx] != mapdata[pz][px])
	{
		//SからGまでドットを打ち込む
		findRoute(0);//ルートの再検索
		updateMap(0);//ルートの再検索

		//今いる座標にドットがあるいけないので消す	
		mapdata[mz][mx] = ' ';
		//自機の座標にドットがないと手前で止まってしまうので必要
		mapdata[pz][px] = '.';
	}
}