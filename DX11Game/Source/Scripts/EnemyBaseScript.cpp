//==================================================================
//								EnemyBaseScript.h
//	エネミーベーススクリプト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/09	エネミーベースクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "EnemyBaseScript.h"

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
#include "EnemyEffectScript.h"
#include "MakeEnemyScript.h"
#include "EnemyBulletScript.h"
#include "HitEffectScript.h"


// ネームスペース
using namespace ECS;


//===== マクロ定義 =====


//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void EnemyBaseScript::Start()
{
	// 自身の取得
	m_myPointer = gameObject().lock()->GetComponent<EnemyBaseScript>();

	// 名前・タグ
	gameObject().lock()->SetName("Enemy");
	gameObject().lock()->SetTag("Enemy");

	// 大きさ
	transform().lock()->m_scale = Vector3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 1);


	//--- コンポーネンの追加

	// スプライト
	// レンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetTexSize(Vector3{ 0.5f, 1.0f, 1.0f });
	renderer->UpdateTexMatrix();
	m_sprite = renderer;

	// コライダー
	gameObject().lock()->AddComponent<BoxCollider>();


}

//========================================
//
//	更新時
//
//========================================
void EnemyBaseScript::Update()
{
	
}

//========================================
//
//	後更新時
//
//========================================
void EnemyBaseScript::LateUpdate()
{
	// メイカーを取得
	const auto& maker = m_enemyMaker.lock();
	if (!maker) return;

	// 座標スケール
	Vector3 pos = transform().lock()->m_pos;
	Vector3 scale = transform().lock()->m_scale;


	// 境界判定
	if (pos->x + scale->x / 2 > SCREEN_CENTER_X ||
		pos->x - scale->x / 2 < -SCREEN_CENTER_X)
	{
		maker->UpdateMoveDir();
	}

}

//========================================
//
//	終了時
//
//========================================
void EnemyBaseScript::End()
{
}

//========================================
//
//	弾の生成
//
//========================================
void EnemyBaseScript::Shot(float speed)
{
	const auto& test = Instantiate<GameObject>();
	test->AddComponent<EnemyBulletScript>()->SetEnemy(m_myPointer.lock());
	const auto& rb = test->GetComponent<Rigidbody>();

	Vector3 dir = Vector3{ 0, 1, 0 };

	test->transform().lock()->m_pos = transform().lock()->m_pos - dir * ENEMY_SIZE_Y / 4;
	rb->AddForceY(-speed);

	// ショットフラグ
	m_bShot = false;

	// サウンド
	//CSound::PlaySE("Shot.wav", 0.3f);
}

void EnemyBaseScript::SetTexure(int nType)
{
	switch (nType)
	{
	case 0:
		m_sprite.lock()->SetDiffuseTexture("data/texture/Enemy1.png");
		break;
	case 1:
		m_sprite.lock()->SetDiffuseTexture("data/texture/Enemy2.png");
		break;
	case 2:
		m_sprite.lock()->SetDiffuseTexture("data/texture/Enemy3.png");
		break;
	default:
		break;
	}
}

//******************** コールバック関数 ********************

//========================================
//
// 当たった時
//
//========================================
void EnemyBaseScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "Player" || 
		collider->gameObject().lock()->tag() == "PlayerBullet")
	{
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

		// 削除
		Destroy(gameObject().lock());
	}
}

//========================================
//
// 当たっている間
//
//========================================
void EnemyBaseScript::OnCollisionStay(Collider* collider)
{
	// 同じ
	OnCollisionEnter(collider);
}

//========================================
//
// 離れた時
//
//========================================
void EnemyBaseScript::OnCollisionExit(Collider* collider)
{
}

