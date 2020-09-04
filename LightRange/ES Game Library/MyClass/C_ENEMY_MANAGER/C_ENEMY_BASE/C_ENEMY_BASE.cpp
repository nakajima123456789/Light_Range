
#include "C_ENEMY_BASE.h"
Vector3 *C_ENEMY_BASE::player_pos;

/**
 * @file C_ENEMY_BASE.h
 * @brief　敵で共有されるメソッド機能
 * @date 
 */

 /**
  * @fn
  * ここに関数の説明を書く
  * @関数名　
  * @brief 要約説明
  * @param (引数名) 引数の説明　
  * @param (引数名) 引数の説明　
  * @return 戻り値の説明　
  * @detail 詳細な説明　
  */
LPCTSTR  C_ENEMY_BASE::GetModelFileName(int _enemy_model)
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

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　
 * @brief 要約説明
 * @param (引数名) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　
 */
LPCTSTR  C_ENEMY_BASE::GetModelTextureFileName(int _enemy_model)
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

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　Lock_at_Target
 * @brief 要約説明
 * @param (_position) 引数の説明　対象座標（プレイヤー）
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　敵と相手の方向取得する
 * @detail 詳細な説明　敵をプレイヤーに向かせたいときに使う
 */
float C_ENEMY_BASE::Lock_at_Target(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;
	float angle = MathHelper_Atan2(other_position.z - is_position.z, other_position.x - is_position.x);
	return angle;
}


/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　Distance_at_Traget
 * @brief 要約説明
 * @param (_position) 引数の説明　対象座標（プレイヤー）
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　二つの距離を計算し返す
 * @detail 詳細な説明　
 */
float C_ENEMY_BASE::Distance_at_Traget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;

	float distance = Vector3_Distance(is_position, other_position);

	return distance;
}


/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　skater_st_Traget
 * @brief 要約説明
 * @param (_position) 引数の説明　近づけたい相手の座標
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　ノーマライズ少しで近づけた座標を返す
 * @detail 詳細な説明　
 */
Vector3 C_ENEMY_BASE::skater_st_Traget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;

	is_position += Vector3_Normalize(other_position - is_position) * 0.02;

	return is_position;
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　SetPlayerState
 * @brief 要約説明
 * @param (new_state) 引数の説明　アニメーションの番号を代入
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　アニメーション切り替えフレーム再生も防止
 */
bool C_ENEMY_BASE::SetPlayerState(int new_state)
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

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　Set_Material
 * @brief 要約説明
 * @param (color) 引数の説明　色指定
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　
 */
Material C_ENEMY_BASE::Set_Material(Color color)
{
	Material mtrl;

	mtrl.Diffuse = color;
	mtrl.Ambient = color;
	mtrl.Specular = color;
	mtrl.Emissive = color;
	mtrl.Power = 1.0f;

	return mtrl;
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　wrap　
 * @brief 要約説明
 * @param (引数名) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　ラップアラウンド　引数ｘの値がhighの値を超えたらlowの値にするまたわその逆
 */
int C_ENEMY_BASE::wrap(int x, int low, int high)
{
	ASSERT(low < high);
	const int n = (x - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　ShaderInit
 * @brief 要約説明
 * @param (LPCTSTR _file_texcha) 引数の説明　モデルのファイルネームを代入　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　SHADERえの登録　
 */
void C_ENEMY_BASE::ShaderInit(LPCTSTR _file_texcha)
{
	c_shader_manager.reset(new CShaderAnimation);
	c_shader_manager->ShaderInitialize(_file_texcha, _T("FX/Light.hlsl"));
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　ShaderDrawGetEffct
 * @brief 要約説明
 * @param (引数名) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　ShaderInitで登録した情報を適用しかえす
 * @detail 詳細な説明　
 */
EFFECT C_ENEMY_BASE::ShaderDrawGetEffct()
{
	c_shader_manager->IsModelPass(this->animation_model);

	EFFECT shader = c_shader_manager->ShaderDraw(alpha);

	return EFFECT(shader);
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　ShaderAlphaDraw
 * @brief 要約説明
 * @param (引数名) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　敵とプレイヤーの距離に合わせて不透明を変える
 */
void C_ENEMY_BASE::ShaderAlphaDraw()
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

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　IsDistanceInit
 * @brief 要約説明
 * @param (std::string _tags) 引数の説明　呼び出し元のタグを代入
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　タグをlistに登録する
 */
void  C_ENEMY_BASE::IsDistanceInit(std::string _tags)
{
	ASSERT(_tags != "defult" && "defult以外にしてください");
	c_dis.reset(new C_DIS);
	c_dis->Init();
	c_dis->IsTagSet(_tags);
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　IsDistanceUpdate
 * @brief 要約説明
 * @param (_pos) 引数の説明　呼び出し元の座標を代入
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　
 */
void  C_ENEMY_BASE::IsDistanceUpdate(Vector3 _pos)
{
	c_dis->IsPosition(animation_model->GetPosition());
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　IsHitObjectsInit
 * @brief 要約説明
 * @param (_tags) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　ヒットボックスをlistに登録する
 */
void  C_ENEMY_BASE::IsHitObjectsInit(std::string _tags)
{
	ASSERT(_tags != "defult" && "defult以外にしてください");
	hitbox.reset(new HitBox);
	hitbox->Init();
	hitbox->Settags(_tags);

	hitbox->SetHitBoxScale(1.1f);
	hitbox->SetHitBoxPosition(Vector3(2, 0, -2));
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名
 * @brief 要約説明
 * @param (引数名) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　
 * @detail 詳細な説明　　
 */
void  C_ENEMY_BASE::IsHitObjectsDraw(Vector3 _pos)
{
	hitbox->SetHitBoxPosition(_pos);
	hitbox->Draw3D();
}

/**
 * @fn
 * ここに関数の説明を書く
 * @関数名　IsHitObjects
 * @brief 要約説明
 * @param (tags) 引数の説明　
 * @param (引数名) 引数の説明　
 * @return 戻り値の説明　指定したタグに該当するヒットボックスと衝突判定をし当たってたらTRUEを返す
 * @detail 詳細な説明　ヒットボックスは静的変数にlist型で管理されており、外部にあるヒットボックスと衝突判定をすることが可能
 */
bool C_ENEMY_BASE::IsHitObjects(std::string tags) {
	ASSERT(hitbox->Tag_Sarch(tags) && "指定したHITBOXのタグが存在していません。");
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