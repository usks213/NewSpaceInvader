//==================================================================
//												GameWorld.cpp
//	ゲームワールド
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/11	ゲームワールドクラス作成
//				ゲームシーンを移植
//
//===================================================================


//===== インクルード部 =====
#include "GameWorld.h"

// システム
#include "../Engine/ECS/Entity/EntityManager.h"
#include "../Engine/ECSEntity/GameObject.h"
#include "../Engine/Renderer/Camera.h"
#include "../Engine/System/Sound.h"

// コンポーネント
#include "../Engine/ECSCompoent/Transform.h"
#include "../Engine/ECSCompoent/MeshRenderer.h"

// スクリプト
#include "../Scripts/PlayerScript.h"
#include "../Scripts/MakeEnemyScript.h"
#include "../Scripts/DeltaUIScript.h"


using namespace ECS;


//===== マクロ定義 =====


//===== プロトタイプ宣言 =====


//===== グローバル変数 =====


//===================================
//
//	コンストラクタ
//
//===================================
GameWorld::GameWorld(std::string name)
	:World(name)
{
}

//===================================
//
//	デストラクタ
//
//===================================
GameWorld::~GameWorld()
{
}

//===================================
//
//	ワールドの初期化
//
//===================================
void GameWorld::Start()
{
	//--- ゲームオブジェクトを追加

	// プレイヤー
	const auto& player = GetEntityManager()->CreateEntity<GameObject>();
	const auto & playerScript = player->AddComponent<PlayerScript>();

	//// デルタUI
	//const auto& deltaUi = GetEntityManager()->CreateEntity<GameObject>();
	//deltaUi->AddComponent<DeltaUIScript>()->SetPlayer(playerScript);

	// エネミーメイカー
	const auto& enemyMaker = GetEntityManager()->CreateEntity<GameObject>();
	enemyMaker->AddComponent<MakeEnemyScript>()->SetPlayer(player);
	
	//// カーソル
	//const auto& cursor = GetEntityManager()->CreateEntity<GameObject>();
	//const auto& cursorRn = cursor->AddComponent<SpriteRenderer>();
	//cursorRn->SetDiffuseTexture("data/texture/Cursor.png");
	//cursorRn->SetLayer(cursorRn->eUI1);
	//cursor->transform().lock()->m_scale = Vector3{ 64 * SCREEN_SCALE_X,64 * SCREEN_SCALE_Y,32 };

	//// 操作UI
	//const auto& opUI = GetEntityManager()->CreateEntity<GameObject>();
	//const auto& opSpr = opUI->AddComponent<SpriteRenderer>();
	//opSpr->SetDiffuseTexture("data/texture/OperationUI.png");
	//opSpr->SetLayer(opSpr->eUI1);
	//opUI->transform().lock()->m_pos = Vector3{ -SCREEN_CENTER_X / 3.0f * 2, -SCREEN_HEIGHT / 3.85f, 1 };
	//opUI->transform().lock()->m_scale = Vector3{ 2400.0f / 6 * SCREEN_SCALE_X, 2100.0f / 6 * SCREEN_SCALE_Y, 1 };

}

//===================================
//
//	ワールドの終了
//
//===================================
void GameWorld::End()
{
	// BGM
	CSound::StopBGM("GameBGM.mp3");

}
