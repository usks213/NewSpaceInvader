//==================================================================
//								HitEffectScript.h
//	エフェクト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/10	エフェクトスクリプトクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "HitEffectScript.h"

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


// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define EFFECT_SCALE_X (2 * SCREEN_SCALE_X)
#define EFFECT_SCALE_Y (2 * SCREEN_SCALE_Y)


//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void HitEffectScript::Start()
{
	// 名前・タグ
	gameObject().lock()->SetName("HitEffect");
	gameObject().lock()->SetTag("HitEffect");

	// 大きさ
	transform().lock()->m_scale = Vector3(EFFECT_SCALE_X, EFFECT_SCALE_Y, 1);
	//--- コンポーネンの追加

	// インスタンシングレンダラー
	const auto& rn = gameObject().lock()->AddComponent<SpriteRenderer>();
	rn->SetDiffuseColor(Vector3{ 1,1,1 });
	rn->SetRendererBlendState(BS_ADDITIVE);
	rn->SetLayer(rn->eUI1);

	// ECSリジッドボディ
	const auto& rb = gameObject().lock()->AddComponent<Rigidbody>();
	rb->SetDrag({ 0.0f,0.0f,0.0f });
	rb->SetGravityForce({ 0,0,0 });
	rb->SetStaticFriction(0);
	rb->SetDynamicFriction(0);
	rb->SetMass(1);
	rb->SetTorqueDrag({ 0,0,0 });

	// 生存時間
	m_nExitTime = 15;
}

//========================================
//
//	更新時
//
//========================================
void HitEffectScript::Update()
{
	m_nExitTime--;
	if (m_nExitTime < 0)
	{
		// 自身の削除
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
//	後更新時
//
//========================================
void HitEffectScript::LateUpdate()
{
}

//========================================
//
//	終了時
//
//========================================
void HitEffectScript::End()
{
}
