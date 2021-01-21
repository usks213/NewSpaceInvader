//==================================================================
//								EnemyEnemyBulletScript.h
//	エネミーバレットスクリプト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/22	エネミーバレットスクリプトクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "EnemyBulletScript.h"

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

// スクリプト
#include "HitEffectScript.h"


// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define ENEMY_BULLET_SIZE_X (3 * SCREEN_SCALE_X)
#define ENEMY_BULLET_SIZE_Y (7 * SCREEN_SCALE_Y)


//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void EnemyBulletScript::Start()
{
	// 名前・タグ
	gameObject().lock()->SetName("EnemyBullet");
	gameObject().lock()->SetTag("EnemyBullet");

	// 大きさ
	transform().lock()->m_scale = Vector3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 1);

	//--- コンポーネンの追加

	// インスタンシングレンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/EnemyBullet.png");

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
void EnemyBulletScript::Update()
{
	m_nExitTime--;
	if (m_nExitTime < 0)
	{
		// ショットフラグを解除
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}

	// 画面外(下)
	Vector3 pos = transform().lock()->m_pos;
	Vector3 scale = transform().lock()->m_scale;
	if (pos->y + scale->y < -SCREEN_CENTER_Y)
	{
		// ショットフラグを解除
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
//	後更新時
//
//========================================
void EnemyBulletScript::LateUpdate()
{
}

//========================================
//
//	終了時
//
//========================================
void EnemyBulletScript::End()
{
}


//******************** コールバック関数 ********************

//========================================
//
// 当たった時
//
//========================================
void EnemyBulletScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "PlayerBullet" ||
		collider->gameObject().lock()->tag() == "Wall" ||
		collider->gameObject().lock()->tag() == "Pillbox")
	{
		// ショットフラグを解除
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// エフェクトの生成
		Vector3 dir = { 1,0,0 };
		int num = 8;
		float angle = 360.0f / num;
		for (int i = 0; i < num; i++)
		{
			const auto& effect = Instantiate<GameObject>(transform().lock()->m_pos);
			effect->AddComponent<HitEffectScript>();

			const auto& rb = effect->GetComponent<Rigidbody>();
			dir = dir.RotationZ(i * angle);
			rb->AddForce(dir * SCREEN_SCALE_X);
		}

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
	else if (collider->gameObject().lock()->tag() == "Player")
	{
		// ショットフラグを解除
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
// 当たっている間
//
//========================================
void EnemyBulletScript::OnCollisionStay(Collider* collider)
{
	// 同じ処理
	OnCollisionEnter(collider);
}

//========================================
//
// 離れた時
//
//========================================
void EnemyBulletScript::OnCollisionExit(Collider* collider)
{
}

