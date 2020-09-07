#include "MAP_OBJECT.h"
#include <functional>

//MAPに配置されるCHARACTERMODELの文字登録
CHARACTER_MANAGER::CHARACTER_MANAGER(){ 
	CharacterTagPreference(CHARACTER_TYPE_MAX, 'p', 'e', 'i', 'w', 'n');
};

//CHARACTERMODEL登録関数　可変型関数
void CHARACTER_MANAGER::CharacterTagPreference(char _tag, ...){
	va_list arguments;
	va_start(arguments, _tag);

	//引数の文字を登録する。
	for (char x = 0; x < _tag; x++)
	{
		character_tag_manager.push_back(va_arg(arguments, char));
	}
	//
	character_position_manager.resize(character_tag_manager.size());
	return;
}
//文字と座標をそれぞれの配列に入れる二次元配列
int CHARACTER_MANAGER::PosSetCharacterEach(char _map_tag, Vector3 _position)
{
	for (int i = 0; i < character_tag_manager.size(); i++)
	{
		if (_map_tag == character_tag_manager[i])
		{
			character_position_manager[i].push_back(_position);
		}
	}
	return 0;
}
//文字とモデルデータを登録する
void MAP_OBJECT_MANAGER::SetModelAndTag(char _tag, LPCTSTR _model_name)
{
	map_tag_manager.push_back(_tag);
	map_model_manager.push_back(GraphicsDevice.CreateModelFromFile(_model_name));

	int size = map_tag_manager.size();

	      map_manager_pos.resize(size);
	all_map_with_distance.resize(size);
	     c_shader_manager.resize(size);
}

MAP_OBJECT_MANAGER::MAP_OBJECT_MANAGER()
{
	IsHitObjectsInit();

	SetModelAndTag('#', GetModelFileName(MAP_TYPE_WALL));
	SetModelAndTag('B', GetModelFileName(MAP_TYPE_BOOKSHELL));
	SetModelAndTag(' ', GetModelFileName(MAP_TYPE_FROAR));

	std::fill(c_shader_manager.begin(), c_shader_manager.end(), new CShaderModel);

	for (UINT i = 0; i < MAP_TYPE_MAX; ++i)
	{
		c_shader_manager[i]->ShaderInitialize(GetModelFileName(i), _T("FX/Light.hlsl"));
	}
};

//モデルのファイルネーム取得
LPCTSTR MAP_OBJECT_MANAGER::GetModelFileName(int _model_index)
{
	switch (_model_index)
	{
	case MAP_TYPE_WALL:
		return LPCTSTR(_T("MODEL//新しいステージ//壁//stage_wall.X"));
		break;
	case MAP_TYPE_BOOKSHELL:
		return LPCTSTR(_T("MODEL//20200702//tana_02.X"));
		break;
	case MAP_TYPE_FROAR:
		return LPCTSTR(_T("MODEL//新しいステージ//床//stage_kai.X"));
		break;
	}
}

//マップとの距離を取得
void MAP_OBJECT_MANAGER::MapDistance(Vector3 _target_pos)
{
	for (int i = 0; i < map_manager_pos.size(); i++)
	{
		for (int x = 0; x < map_manager_pos[i].size(); x++)
		{
			all_map_with_distance[i][x] = Vector3_Distance(_target_pos, map_manager_pos[i][x]);
		}
	}
}

//一番近い座標にヒットボックスを表示する
void MAP_OBJECT_MANAGER::MapSetHitBox()
{
	std::vector<std::vector<float>> txt_dis;

	txt_dis.resize(hitbox.size());

	for (int i = 0; i < txt_dis.size(); i++)
	{
		txt_dis[i] = all_map_with_distance[i];

		auto&& min_distance = std::min_element(txt_dis[i].begin(), txt_dis[i].end(), [](float actor, float min) {return actor < min; });

		hitbox[i]->SetHitBoxPosition(map_manager_pos[i][std::distance(txt_dis[i].begin(), min_distance)]);
	}
}

void MAP_OBJECT_MANAGER::Draw()
{
	const unsigned int light_range = 10;

	for (int i = 0; i < map_manager_pos.size(); i++){
		for (int z = 0; z < map_manager_pos[i].size(); z++)
		{
			if (all_map_with_distance[i][z] <= light_range)
			{
				float alpha = 1.0f;

				c_shader_manager[i]->IsModelPass(map_model_manager[i]);

				EFFECT shader = c_shader_manager[i]->ShaderDraw(alpha);

				this->map_model_manager[i]->SetPosition(map_manager_pos[i][z]);

				this->map_model_manager[i]->Draw(shader);
			}
        }
	}
	MapObjectScale(Vector3_One * 0.0254f);

	IsHitObjectsDraw();
}

void MAP_OBJECT_MANAGER::MapObjectScale(Vector3 _scale)
{
	each([&](MODEL& model) {model->SetScale(_scale); });
}

void MAP_OBJECT_MANAGER::each(std::function<void(MODEL&)> action)
{ 
	std::for_each(map_model_manager.begin(), map_model_manager.end(),[&](MODEL& model) { action(model); });
}

//ライトの光源の強さ
float MAP_OBJECT_MANAGER::Attenuation(float _index) 
{
	ASSERT(_index <= 1.0f && "ライトの光源は1.0未満の値にしてください");
	std::for_each(c_shader_manager.begin(), c_shader_manager.end(), [=](CShaderManager* _c_shader_manager) {_c_shader_manager->SetAttenuation(_index);});
	return 0;
}

//二次元配列それぞれの座標を入れていく
void MAP_OBJECT_MANAGER::PosSetMapEachBegin(char tag_name, Vector3 _position)
{
	for (int i = 0; i < map_tag_manager.size(); i++)
	{
		if (tag_name == map_tag_manager[i])
		{
			all_map_with_distance[i].push_back(0);
			map_manager_pos[i].push_back(_position);
		}
		else {
			if (tag_name >= '0' && tag_name <= '9')
			{
				wandering_route_coordinate.insert(std::make_pair(tag_name - '0', _position));
			}
		}
	}
};

void MAP_OBJECT_MANAGER::PosSetMapEachEnd(char tag_name, Vector3 _position)
{
	for (int i = 0; i < MAP_TYPE_MAX; i++)
	{
		if (tag_name == map_tag_manager[i])
		{
			all_map_with_distance[i].push_back(0);
			map_manager_pos[i].push_back(_position);
		}
	}
}

int  MAP_OBJECT_MANAGER::IsHitObjectsInit()
{
	hitbox.resize(1);

	hitbox[MAP_TYPE_WALL] = new HitBox;
	hitbox[MAP_TYPE_WALL]->Init();
	hitbox[MAP_TYPE_WALL]->Settags("map");

	hitbox[MAP_TYPE_WALL]->SetHitBoxScale(2.2f);


	return 0;
}

MAP_OBJECT_MANAGER::~MAP_OBJECT_MANAGER()
{
	//自分を消す
	std::for_each(hitbox.begin(), hitbox.end(), [&](HitBox* _hitbox) { _hitbox->OnReMove(); });
};

float MAP_OBJECT_MANAGER::SpecifiedArgument(Vector3 pos, Vector3 _p)
{
	float n_distance = FLT_MAX;
	const int distance_range = 2.0;

	for (int z = 0; z < map_manager_pos[MAP_TYPE_WALL].size(); z++)
	{
		if (all_map_with_distance[MAP_TYPE_WALL][z] <= 2.5)
		{
			map_model_manager[MAP_TYPE_WALL]->SetPosition(map_manager_pos[MAP_TYPE_WALL][z]);
			map_model_manager[MAP_TYPE_WALL]->IntersectRay(pos + Vector3(0.f, 0.7f, 0.f), _p, &n_distance);
		}
	}
	return n_distance;
}

void MAP_OBJECT_MANAGER::IsHitObjectsDraw()
{
	std::for_each(hitbox.begin(), hitbox.end(), [&](HitBox* _hitbox) { _hitbox->Draw3D(); });
}

void MAP_MANAGER::Init()
{
	MapDataFileName("File//MAP.txt");
	MapDataSetAllPosition();
}

void MAP_MANAGER::MapDataFileName(char* _map_name)
{
	FILE* fp = fopen(_map_name, "r");
	// マップデータを読み込む
	char load_char[CHAR_MAX + 1];

	while (fgets(load_char, sizeof load_char - 1, fp) != NULL)
	{
		mapdata.push_back(load_char);
	}
	// ファイルを閉じる
	fclose(fp);
}

void MAP_MANAGER::MapDataSetAllPosition()
{
	const int map_size = 2;

	for (int z = 0; z < mapdata.size(); z++){
		for (int x = 0; x < mapdata[z].size(); x++){
			Vector3 position = Vector3((1 * map_size) * x, (0 * map_size), -((1 * map_size) * z));

			ASSERT(Tag_sarch(mapdata[z][x]) && "MAPDATEテキストに存在しないタグがあります。");

			map_object_manager->PosSetMapEachBegin(get_map_date(z, x), position);
			character_manager->PosSetCharacterEach(get_map_date(z, x), position);

			if (get_map_date(z, x) != '#')
			{
				SetBlock(z, x, ' ');
				map_object_manager->PosSetMapEachEnd(get_map_date(z, x), position);
			};
		}
	}
}

void MAP_MANAGER::Update()
{
	map_object_manager->MapSetHitBox();
	map_object_manager->MapDistance((*player_animation_model)->GetPosition() + (*player_animation_model)->GetFrontVector() * 0.09);
	map_object_manager->Attenuation(0.4);

}

void MAP_MANAGER::Draw3D()
{
	map_object_manager->Draw();
}

//指定されたタグかどうかを調べえる
bool MAP_MANAGER::Tag_sarch(char _is_mapdate)
{
	bool flag = false;
	for (int i = 0; i < character_manager->GetCharacterTag().size(); i++)
	{if (_is_mapdate == character_manager->GetCharacterTag()[i]){flag = true;}}

	for (int i = 0; i < map_object_manager->GetMapTag().size(); i++)
	{if (_is_mapdate == map_object_manager->GetMapTag()[i]){flag = true;}}

	char null_char[] = { '\n',' ', };
	const size_t size = sizeof(null_char) / sizeof(null_char[0]);
	for (int i = 0; i < size; i++){if (_is_mapdate == null_char[i]) {flag = true; }}

	return flag;
}