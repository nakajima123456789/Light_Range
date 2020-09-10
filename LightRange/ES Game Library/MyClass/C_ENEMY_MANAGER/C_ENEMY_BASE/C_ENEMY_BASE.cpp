#include "C_ENEMY_BASE.h"
Vector3 *CEnemyBase::player_pos;

//モデルファイルネーム取得
LPCTSTR  CEnemyBase::GetModelFileName(int _enemy_model)
{
	switch (_enemy_model)
	{
	case ENEMY_LARGE:
		return (LPCTSTR)_T("MODEL//enemy_motion//enemy_large.x");
		break;
	case ENEMY_WAMAN:
		return (LPCTSTR)_T("MODEL//woman_enemy//woman_enemy.X");
		break;
	}
}

//モデルテクスチャファイルネーム取得
LPCTSTR  CEnemyBase::GetModelTextureFileName(int _enemy_model)
{
	switch (_enemy_model)
	{
	case ENEMY_LARGE:
		return (LPCTSTR)_T("MODEL//enemy_motion//lambert1_2D_View.png");
		break;
	case ENEMY_WAMAN:
		return (LPCTSTR)_T("MODEL//woman_enemy//lambert1_2D_View.png");
		break;
	}
}

//プレイヤーに向く方向のベクトル取得
float CEnemyBase::LockAtTarget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;
	float angle = MathHelper_Atan2(other_position.z - is_position.z, other_position.x - is_position.x);
	return angle;
}

//プレイヤーとの座標を取得
float CEnemyBase::DisAtTraget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;

	float distance = Vector3_Distance(is_position, other_position);

	return distance;
}

//プレイヤーに自分を近づける
Vector3 CEnemyBase::SkaterAtTraget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;

	is_position += Vector3_Normalize(other_position - is_position) * 0.02;

	return is_position;
}

//モーション切り替えフレーム対応
bool CEnemyBase::SetPlayerState(int new_state)
{
	if (this_track_enable == new_state) { return FALSE; }
	else {
		animation_model->SetTrackEnable(this_track_enable, FALSE);
		animation_model->SetTrackEnable(new_state, TRUE);
		animation_model->SetTrackPosition(new_state, 0);
		this_track_enable = new_state;
	}
	return TRUE;
}

Material CEnemyBase::SetMaterial(Color color)
{
	Material mtrl;

	mtrl.Diffuse = color;
	mtrl.Ambient = color;
	mtrl.Specular = color;
	mtrl.Emissive = color;
	mtrl.Power = 1.0f;

	return mtrl;
}

//ラップアラウンド
int CEnemyBase::wrap(int x, int low, int high)
{
	ASSERT(low < high);
	const int n = (x - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

//テキストネームを代入しSHADERに登録する
void CEnemyBase::ShaderInit(LPCTSTR _file_texcha)
{
	c_shader_manager.reset(new CShaderAnimation);
	c_shader_manager->ShaderInitialize(_file_texcha, _T("FX/Light.hlsl"));
}


EFFECT CEnemyBase::ShaderDrawGetEffct()
{
	c_shader_manager->IsModelPass(this->animation_model);

	EFFECT shader = c_shader_manager->ShaderDraw(alpha);

	return EFFECT(shader);
}

//プレイヤーとの距離に合わせ敵の不透明度を変更する
void CEnemyBase::ShaderAlphaDraw()
{
	Vector3 enemy_pos  = this->animation_model->GetPosition();
	Vector3 target_pos = (*player_pos);

	float v_dis = 1.8f;
	float add_alpha = 0.05f;

	if ((enemy_pos.x - target_pos.x) * (enemy_pos.x - target_pos.x) + (enemy_pos.z - target_pos.z) * (enemy_pos.z - target_pos.z) <= v_dis * v_dis)
	{
		alpha = min(alpha + add_alpha, 1);
	}
	else {
		alpha = max(alpha - add_alpha, 0);
	};
}
//初期化
void  CEnemyBase::IsDistanceInit(std::string _tags)
{
	c_dis.reset(new CDis);
	c_dis->Init();
	c_dis->IsTagSet(_tags);
}

void  CEnemyBase::IsDistanceUpdate(Vector3 _pos)
{
	c_dis->IsPosition(animation_model->GetPosition());
}

void  CEnemyBase::IsHitObjectsInit(std::string _tags)
{
	hitbox.reset(new HitBox);
	hitbox->Init();
	hitbox->Settags(_tags);

	hitbox->SetHitBoxScale(1.15f);
	hitbox->SetHitBoxPosition(Vector3(2, 0, -2));
}

void  CEnemyBase::IsHitObjectsDraw(Vector3 _pos)
{
	hitbox->SetHitBoxPosition(_pos);
	hitbox->Draw3D();
}

//欲しいヒットボックスを呼び出しそれが当たっていたらTRUEを返す
bool CEnemyBase::IsHitObjects(std::string tags) {
	bool result = false;
	std::list<HitBox*> HitList = hitbox->HitHitBoxlist();

	for (auto&& other : HitList) {
		if (other->tag == tags)
		{
			result = true;
		}
	}
	return result;
}

bool CEnemyBase::FrameTime(int _index)
{
	time++;
	if (time % _index == 0) { return true; }
	return false;
}