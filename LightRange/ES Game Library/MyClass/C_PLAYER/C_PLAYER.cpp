#include "C_PLAYER.h"
#include "../C_FONT/C_FONT.h"
#include "../C_Information/Information.h"

CPlayer::CPlayer(Vector3  _pos)
{
	transform.position = _pos;
};

void CPlayer::Init()
{
	//オリジナルのプレイヤークラスにアクセス用
	player_state_processor.player_manager = this;
	player_state_processor.ChangeState(new CPlayer::IDOL(&player_state_processor));

	player_model = GraphicsDevice.CreateAnimationModelFromFile((_T("MODEL//woman_hand_kai/woman_motion_02.x")));
	player_model->SetMaterial(SetMaterial(Color(0.5f,0.5f,0.5)));

	ASSERT(player_model != nullptr && "モデルの名前が違います。");

	c_shader_manager.reset(new CShaderAnimation);
	c_shader_manager->ShaderInitialize(_T("MODEL//woman_hand_kai/lambert1_2D_View.png"), _T("FX/Light.hlsl"));

	IsHitObjectsInit();
	IsDistanceInit();

	se_i = SNDMANAGER.LoadLopeSE(_T("SE//SE//sinpaku.wav"));
}

CPlayer::~CPlayer()
{
	
};

void CPlayer::GetHitBoxPosition(Vector3 _position)
{
	c_hitbox->SetHitBoxPosition(_position);
}

int  CPlayer::IsHitObjectsInit()
{
	c_hitbox.reset(new HitBox);
	c_hitbox->Init();
	c_hitbox->Settags("player");

	c_hitbox->SetHitBoxScale(0.5f);
	//初期座標　ヒットボックスをもとに動かす
	c_hitbox->SetHitBoxPosition(this->transform.position);

	return 0;
}

void  CPlayer::IsDistanceInit()
{  
	c_dis.reset(new CDis);
	c_dis->Init();
	c_dis->IsTagSet("player");
	return;
}

//タグを代入しそのタグと当たっていればtrueを返す
bool CPlayer::IsHitObjects(std::string tags) {
	bool result = false;
	std::list<HitBox*> HitList = c_hitbox->HitHitBoxlist();
	for (auto&& other : HitList) {
		if (other->tag == tags){ 		
			result = true;}
	}
	return result;
}

void CPlayer::Update()
{
	CollisionDetection();
	IsDistanceUpdate();
	this->player_state_processor.Update();
}

void  CPlayer::CollisionDetection()
{
	//enemyと衝突したら
	if (IsHitObjects("enemy"))
	{ 
		//UGUIのIsCollisionを呼び出す
		observer.IsCollision();
		//ステートパターンダメージアルゴリズムへ交換
		player_state_processor.ChangeState(new CPlayer::DAMAGE(&player_state_processor));
	};
}

void  CPlayer::IsDistanceUpdate()
{
	c_dis->IsPosition((this->transform.position));
	//敵との距離によりSEの音量下げる
	SNDMANAGER.DistanceSeV(c_dis->GetTagDistance("enemy"), 3.5, se_i);
}

void CPlayer::IsPlayerMoveMent()
{
	std::vector<HitBox*> hit_box_model = map_manager->Get_Hit_Box();
	Vector3 POS = player_model->GetPosition();
	Vector3 F   = player_model->GetFrontVector();
	Vector3 N;

	//マップ障害物用ヒットボックスの数だけ要素を増やす
	std::vector<float> distacne;
	distacne.resize(hit_box_model.size());

	//上で増やした要素を初期化
	std::fill(distacne.begin(), distacne.end(), FLT_MAX);

	//マップ障害物用ヒットボックスにRayを飛ばし距離をもらう
	for (int i = 0; i < hit_box_model.size(); i++)	{hit_box_model[i]->Get_Tag_Model()->IntersectRay(POS, F, &distacne[i], &N);}

	//全てのマップ障害物用ヒットボックスとの距離が0.3以上であればTRUEを返す
	bool distance_flag   = std::all_of(distacne.begin(), distacne.end(), [](float x)->bool { return x >= 0.3; });

	//PADステックを動かしたら
	if (Input.AxisFlag()) {
		if (distance_flag) {c_hitbox->HitBoxMove(speed_vectol);}
		else
		{
			//壁ずりの計算をしプレイヤーの座標にそのベクトルを足していく
			Vector3 P = F + Vector3_Dot(-F, N) * N;
			POS  += P * 0.02f;
			if (map_manager->GetPDistance(POS, P) >= 0.3) { c_hitbox->SetHitBoxPosition(POS); };
		}
	}
}

void CPlayer::IDOL::Update()
{
	_owner->player_manager->SetPlayerState(PLAYER_ANIMATION_TYPE::_IDOL);

	if (Input.AxisFlag())
	{
		_owner->player_manager->player_state_processor.ChangeState(new CPlayer::WALK(&_owner->player_manager->player_state_processor));
		return;
	}
}

void CPlayer::WALK::Update()
{
	_owner->player_manager->SetPlayerState(PLAYER_ANIMATION_TYPE::_WALK);

	_owner->player_manager->IsPlayerMoveMent();

	_owner->player_manager->speed_vectol = Input.GetArrowpadVector() * 0.02;

	if (Input.AxisFlag())
	{
		//ステックの傾きによりプレイヤーの方向を変える
	    _owner->player_manager->transform.rotation.y = Input.PadKeyAngle();
	}
	else 
	{ 
		_owner->player_manager->player_state_processor.ChangeState(new CPlayer::IDOL(&_owner->player_manager->player_state_processor));
		   return;
	}

	if (Input.GetPadInputDown(0)) 
	{
		_owner->player_manager->player_state_processor.ChangeState(new CPlayer::RUN(&_owner->player_manager->player_state_processor));
		return;
	};
}

void CPlayer::RUN::Update()
{
	_owner->player_manager->SetPlayerState(PLAYER_ANIMATION_TYPE::_RUN);

	_owner->player_manager->IsPlayerMoveMent();

	_owner->player_manager->speed_vectol = Input.GetArrowpadVectorNomalize() * 0.06;

	if (Input.GetPadInput(0) && Input.AxisFlag()) 
	{
		_owner->player_manager->transform.rotation.y = Input.PadKeyAngle();
	}
	else 
	{
		_owner->player_manager->player_state_processor.ChangeState(new CPlayer::WALK(&_owner->player_manager->player_state_processor));
		return;
	}

	if (Information::Ui_Information::point_sutamina <= 0)
	{
		_owner->player_manager->player_state_processor.ChangeState(new CPlayer::WALK(&_owner->player_manager->player_state_processor));
		return;
	}
}

void CPlayer::DAMAGE::Update()
{
	_owner->player_manager->SetPlayerState(PLAYER_ANIMATION_TYPE::_DAMEGE);

	AddTime();

	if (GetTime() >= ExitTime())
	{
		_owner->player_manager->player_state_processor.ChangeState(new CPlayer::IDOL(&_owner->player_manager->player_state_processor));
		return;
	}
}

inline Matrix CPlayer::Create_Shadow_Matrix(const D3DLIGHTTYPE light_type, const Vector3& light,const Vector3& pos, const Vector3& shadow_offset,const Vector3& normal)
{
	D3DXVECTOR4   Light;
	Light = D3DXVECTOR4(light + Vector3(0, 1500000, 150000) - pos, 0.0f);
	::D3DXVec4Normalize(&Light, &Light);

	D3DXPLANE     Plane;
	::D3DXPlaneFromPointNormal(&Plane, &(pos + shadow_offset), &normal);

	D3DXMATRIX   matT;
	::D3DXMatrixShadow(&matT, &Light, &Plane);

	return matT;
}


void CPlayer::Draw3D()
{
	player_model->SetPosition((this->transform.position = this->c_hitbox->GetHitBoxPosition()));
	player_model->SetRotation(this->transform.rotation);
	player_model->SetScale(this->transform.scale);
	player_model->AdvanceTime(1.0 / 60);

	c_shader_manager->IsModelPass(player_model);
	float  alpha = 1.0f;
	EFFECT shader = c_shader_manager->ShaderDraw(alpha);

	GraphicsDevice.BeginShadowRendering();
	Matrix mat;
	mat = Create_Shadow_Matrix(Light_Directional, Vector3_Zero, player_model->GetPosition(), Vector3(0.0f, 0.1f, 0.0f), Vector3_Up);
	player_model->DrawShadow(mat, 0.75f);
	GraphicsDevice.EndShadowRendering();

	player_model->Draw();
	IsHitObjectsDraw();
}

void CPlayer::IsHitObjectsDraw()
{
	c_hitbox->Draw3D();
}

Material CPlayer::SetMaterial(Color color)
{
	Material mtrl;

	mtrl.Diffuse  = color;
	mtrl.Ambient  = color;
	mtrl.Specular = color;
	mtrl.Emissive = color;
	mtrl.Power = 1.0f;

	return mtrl;
}

//プレイヤーのモーションと切り替えフレーム処理にも対応
bool CPlayer::SetPlayerState(int new_state)
{
	Information::Player_Information::player_state = new_state;
	if (this_track_enable == new_state) { return FALSE; }
	else {
		player_model->SetTrackEnable(this_track_enable, FALSE);
		player_model->SetTrackEnable(new_state, TRUE);
		player_model->SetTrackPosition(new_state, 0);
		this_track_enable = new_state;
	} 
	return TRUE;
}
