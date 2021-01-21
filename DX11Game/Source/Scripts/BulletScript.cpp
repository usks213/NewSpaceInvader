//==================================================================
//								BulletScript.cpp
//	バレットスクリプト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/07	バレットスクリプトクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "BulletScript.h"

// システム
#include "../Engine/System/input.h"
#include "../Engine/System/Sound.h"

// マネージャー
#include "../Engine/ECS/Entity/EntityManager.h"

// エンティティ
#include "../Engine/ECSEntity/GameObject.h"

// コンポーネント
#include "../Engine/ECSCompoent/Transform.h"
#include "../Engine/ECSCompoent/MeshRenderer.h"
#include "../Engine/ECSCompoent/BillboardRenderer.h"
#include "../Engine/ECSCompoent/AssimpRenderer.h"
#include "../Engine/ECSCompoent/SpriteRenderer.h"
#include "../Engine/ECSCompoent/InstancingMeshRenderer.h"
#include "../Engine/ECSCompoent/Rigidbody.h"
#include "../Engine/ECSCompoent/BoxCollider.h"
#include "../Engine/ECSCompoent/SphereCollider.h"


// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define PLAYERBULLET_SIZE_X (1 * SCREEN_SCALE_X)
#define PLAYERBULLET_SIZE_Y (4 * SCREEN_SCALE_Y)


//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void BulletScript::Start()
{
	// 名前・タグ
	gameObject().lock()->SetName("PlayerBullet");
	gameObject().lock()->SetTag("PlayerBullet");

	// 大きさ
	transform().lock()->m_scale = Vector3(PLAYERBULLET_SIZE_X, PLAYERBULLET_SIZE_Y, 1);

	//--- コンポーネンの追加

	// インスタンシングレンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/PlayerBullt.png");

	// ECSリジッドボディ
	const auto& rb = gameObject().lock()->AddComponent<Rigidbody>();
	rb->SetDrag({ 0,0,0 });
	rb->SetGravityForce({ 0,0,0 });
	rb->SetStaticFriction(0);
	rb->SetDynamicFriction(0);
	rb->SetMass(1);
	rb->SetTorqueDrag({ 0,0,0 });
	rb->SetUsePhysics(false);
	rb->SetUseGravity(false);

	// ECSコライダー
	gameObject().lock()->AddComponent<BoxCollider>();


	// 生存時間
	m_nExitTime = 120;
}

//========================================
//
//	更新時
//
//========================================
void BulletScript::Update()
{
	m_nExitTime--;
	if (m_nExitTime < 0)
	{
		// ショットフラグを解除
		const auto& player = m_player.lock();
		if (player)
			player->SetShotFlg(true);

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}

	// 画面外
	Vector3 pos = transform().lock()->m_pos;
	Vector3 scale = transform().lock()->m_scale;
	if (pos->y - scale->y > SCREEN_CENTER_Y)
	{
		// ショットフラグを解除
		const auto& player = m_player.lock();
		if (player)
			player->SetShotFlg(true);

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
//	後更新時
//
//========================================
void BulletScript::LateUpdate()
{
}

//========================================
//
//	終了時
//
//========================================
void BulletScript::End()
{
}


//******************** コールバック関数 ********************

//========================================
//
// 当たった時
//
//========================================
void BulletScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "Enemy" ||
		collider->gameObject().lock()->tag() == "EnemyBullet" ||
		collider->gameObject().lock()->tag() == "Wall" ||
		collider->gameObject().lock()->tag() == "Pillbox")
	{
		// ショットフラグを解除
		const auto& player = m_player.lock();
		if (player)
			player->SetShotFlg(true);

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
// 当たっている間
//
//========================================
void BulletScript::OnCollisionStay(Collider* collider)
{
	// 同じ処理
	OnCollisionEnter(collider);
}

//========================================
//
// 離れた時
//
//========================================
void BulletScript::OnCollisionExit(Collider* collider)
{
}

