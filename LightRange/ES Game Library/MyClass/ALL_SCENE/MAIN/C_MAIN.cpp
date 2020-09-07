#include "C_MAIN.h"
#include "../SCENEMANAGER/SceneManager.h"

#include "../../C_PLAYER/C_PLAYER.h"
#include "../../C_CAMERA/C_CAMERA.h"
#include "../../C_MAP_OBJECT/MAP_OBJECT.h"
#include "../../C_SHADER/C_SHADER.h"
#include "../../C _UGUI/UGUI.h"

#include "../../C_SE/C_SE.h"

#include "../../C_ENEMY_FACTORY/C_ENEMY_FACTORY.h"
#include "../../C_ITEM_FACTORY/C_ITEM_FACTORY.h"

#include "../../C_Information/Information.h"

void C_MAIN::Initialize(){

	auto c_camera = (new CCamera_);
	_objectroot.AddList((ChildObjRef)c_camera);
	CShaderAnimation::CameraSetting(*c_camera);

	auto&& c_map = (new MAP_MANAGER);
	_objectroot.AddList((ChildObjRef)c_map);

	auto&& c_player = (new CPlayer(c_map->GetCharacterPos()[CHARACTER_TYPE_PLAYER][IS_CHARACTER_ONCE]));
	c_camera->GetPlayerTranceform(&c_player->transform);
	_objectroot.AddList((ChildObjRef)c_player);

	c_map->player_animation_model = &c_player->player_model;
	c_player->map_manager = (c_map);

	auto&& c_ugul = (new UGUI);
	c_ugul->GetItemSize(c_map->GetCharacterPos()[CHARACTER_TYPE_ITEM].size());
	_objectroot.AddList((ChildObjRef)c_ugul);

	CItemFactory* c_item_factory = new ItemStationeryFactory();

	for (int i = 0; i < c_map->GetCharacterPos()[CHARACTER_TYPE_ITEM].size(); i++)
	{
		Object* c_item_book = c_item_factory->Create("ÉAÉCÉeÉÄ", c_map->GetCharacterPos()[CHARACTER_TYPE_ITEM][i]);
		_objectroot.AddList((ChildObjRef)c_item_book);
	}

	delete c_item_factory;
	c_item_factory = 0;

	EnemyFactory* c_enemy_factory = new EnemyStationeryFactory();

	if (c_map->GetWanderingRoutePosition().size() != 0)
	{
		Object* c_enemy_wander = c_enemy_factory->Create("úpújìG", c_map->GetWanderingRoutePosition());
		_objectroot.AddList((ChildObjRef)c_enemy_wander);
	}
	for (int i = 0; i < c_map->GetCharacterPos()[CHARACTER_TYPE_NAV_E].size(); i++)
	{
		Object* c_enemy_search_n = c_enemy_factory->Create("íTçıìGíx", c_map->GetCharacterPos()[CHARACTER_TYPE_NAV_E][i]);
		_objectroot.AddList((ChildObjRef)c_enemy_search_n);
	}
	for (int i = 0; i < c_map->GetCharacterPos()[CHARACTER_TYPE_WOMAN].size(); i++)
	{
		Object* c_enemy_search_w = c_enemy_factory->Create("íTçıìGëÅ", c_map->GetCharacterPos()[CHARACTER_TYPE_WOMAN][i]);
		_objectroot.AddList((ChildObjRef)c_enemy_search_w);
	}

	delete c_enemy_factory;
	c_enemy_factory = 0;

	CEnemyBase::Set_Player_position(&c_player->transform.position);

	SNDMANAGER.LoadBGM(_T("SE//SE//ÉQÅ[ÉÄíÜBGM.wav"));
}

C_MAIN::~C_MAIN()
{
	MediaManager.ReleaseAllMedia();
	GraphicsDevice.ReleaseAllRenderTargets();
	GraphicsDevice.ReleaseAllStateBlocks();
	GraphicsDevice.ReleaseAllFonts();
	GraphicsDevice.ReleaseAllSprites();
	GraphicsDevice.ReleaseAllAnimationModels();
	GraphicsDevice.ReleaseAllModels();
	GraphicsDevice.ReleaseAllVertexBuffers();
	GraphicsDevice.ReleaseAllEffects();

	SoundDevice.ReleaseAllMusics();
	SoundDevice.ReleaseAllSounds();

	Information::Ui_Information::game_over_flag  = false;
	Information::Ui_Information::game_clear_flag = false;
};

void C_MAIN::Update(){
	_objectroot.Update();

	SNDMANAGER.PlayBGM();

	if (Information::Ui_Information::game_over_flag)  { SceneManager::ChangeScene(SceneManager::GAME_OVER);}

	if (Information::Ui_Information::game_clear_flag) { SceneManager::ChangeScene(SceneManager::GAME_CLEAR);};
}
void C_MAIN::Draw3D()
{
	_objectroot.Draw3D();
}
void C_MAIN::Draw2D()
{
	_objectroot.Draw2D();
}
void C_MAIN::DrawAlpha3D() 
{
	GraphicsDevice.BeginAlphaBlend();

	_objectroot.DrawAlpha3D();

	GraphicsDevice.EndAlphaBlend();
};

