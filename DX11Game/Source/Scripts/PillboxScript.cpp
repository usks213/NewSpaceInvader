//==================================================================
//								PillboxScript.h
//	トーチカスクリプト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/22	トーチカスクリプトクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "PillboxScript.h"

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


//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void PillboxScript::Start()
{
	// 名前・タグ
	gameObject().lock()->SetName("Pillbox");
	gameObject().lock()->SetTag("Pillbox");

	// 大きさ
	transform().lock()->m_scale = Vector3(PILLBOX_SIZE_X, PILLBOX_SIZE_Y, 1);

	//--- コンポーネンの追加

	// インスタンシングレンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseColor(1.0f, 0.5f, 0.0f);

	//// ECSリジッドボディ
	//const auto& rb = gameObject().lock()->AddComponent<Rigidbody>();
	//rb->SetDrag({ 0,0,0 });
	//rb->SetGravityForce({ 0,0,0 });
	//rb->SetStaticFriction(0);
	//rb->SetDynamicFriction(0);
	//rb->SetMass(1);
	//rb->SetTorqueDrag({ 0,0,0 });
	//rb->SetUsePhysics(false);
	//rb->SetUseGravity(false);

	// コライダー
	gameObject().lock()->AddComponent<BoxCollider>();

}

//========================================
//
//	更新時
//
//========================================
void PillboxScript::Update()
{
}

//========================================
//
//	後更新時
//
//========================================
void PillboxScript::LateUpdate()
{
}

//========================================
//
//	終了時
//
//========================================
void PillboxScript::End()
{
}


//******************** コールバック関数 ********************

//========================================
//
// 当たった時
//
//========================================
void PillboxScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "Enemy" ||
		collider->gameObject().lock()->tag() == "EnemyBullet" ||
		collider->gameObject().lock()->tag() == "PlayerBullet")
	{
		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
// 当たっている間
//
//========================================
void PillboxScript::OnCollisionStay(Collider* collider)
{
	// 同じ処理
	OnCollisionEnter(collider);
}

//========================================
//
// 離れた時
//
//========================================
void PillboxScript::OnCollisionExit(Collider* collider)
{
}

