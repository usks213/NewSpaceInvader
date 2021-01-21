//==================================================================
//								MakeEnemyScript.h
//	エネミー生成スクリプト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/08	エネミー生成スクリプトクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "MakeEnemyScript.h"

// システム
#include "../Engine/System/input.h"
#include "../Engine/System/Sound.h"
#include "../Engine/System/debugproc.h"

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

// ECSコンポーネント
#include "../Engine/ECSCompoent/Rigidbody.h"
#include "../Engine/ECSCompoent/DeltaCollider.h"

// ECSシステム
#include "../Engine/ECSSystem/RigidbodySystem.h"
#include "../Engine/ECSSystem/DeltaCollisionSystem.h"

// スクリプト
#include "PlayerScript.h"
#include "EnemyBaseScript.h"



// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define MAX_ENEMY_NUM_X (11)
#define MAX_ENEMY_NUM_Y (5)
#define MAX_ENEMY_NUM (MAX_ENEMY_NUM_X * MAX_ENEMY_NUM_Y)

#define ENEMY_OFFSET_X (ENEMY_SIZE_X + 4 * SCREEN_SCALE_X)
#define ENEMY_OFFSET_Y (ENEMY_SIZE_Y + 4 * SCREEN_SCALE_Y)

#define MOVE_INTAERVAL (45)

//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void MakeEnemyScript::Start()
{
	// 自身のポイント
	const auto& myPointer = gameObject().lock()->GetComponent<MakeEnemyScript>();

	// 移動速度
	m_fMoveSpeed = ENEMY_OFFSET_X / 4;
	// 移動速度向き
	m_bRightMove = true;
	// 弾の速度
	m_fBulletSpeed = m_fMoveSpeed * 0.75f;
	// 弾の生成フラグ
	m_bShot = true;

	// エネミーの生成
	float initPosX = -SCREEN_CENTER_X + ENEMY_OFFSET_X;
		Vector3 pos = { initPosX, SCREEN_CENTER_Y - ENEMY_OFFSET_Y, 0};

	for (int y = 0; y < MAX_ENEMY_NUM_Y; y++)
	{
		for (int x = 0; x < MAX_ENEMY_NUM_X; x++)
		{
			// オブジェクトの生成
			const auto& obj = Instantiate<GameObject>(pos);
			const auto& enemy = obj->AddComponent<EnemyBaseScript>();
			enemy->SetEnemyMaker(myPointer);

			// テクスチャの指定
			if (y == 0)					enemy->SetTexure(eEnemy1);
			else if(y == 1 || y == 2)	enemy->SetTexure(eEnemy2);
			else if(y == 3 || y == 4)	enemy->SetTexure(eEnemy3);

			// 配列に格納
			m_aEnemy.push_back(enemy);

			pos->x += ENEMY_OFFSET_X;
		}
		pos->x  = initPosX;
		pos->y -= ENEMY_OFFSET_Y;
	}
}

//========================================
//
//	更新時
//
//========================================
void MakeEnemyScript::Update()
{
	// 移動処理
	m_nMoveCount--;
	if (m_nMoveCount >= 0) return;
	m_nMoveCount = MOVE_INTAERVAL;

	// 弾の生成を有効
	m_bShot = true;

	// エネミーの更新
	for (int y = 0; y < MAX_ENEMY_NUM_Y; y++)
	{
		for (int x = 0; x < MAX_ENEMY_NUM_X; x++)
		{
			const auto& enemy = m_aEnemy[y * MAX_ENEMY_NUM_X + x].lock();
			if (!enemy) continue;

			// 座標
			Vector3& pos = enemy->transform().lock()->m_pos;

			// 移動
			if(m_bRightMove) pos->x += m_fMoveSpeed;
			else pos->x -= m_fMoveSpeed;

			// 自身より前が存在するか
			if (y + 1 < MAX_ENEMY_NUM_Y &&
				m_aEnemy[(y + 1) * MAX_ENEMY_NUM_X + x].lock())
			{
				continue;
			}

			// 弾の生成
			if (m_bShot && rand() % 100 < 10)
			{
				enemy->Shot(m_fBulletSpeed);
				m_bShot = false;
			}
		}
	}

}

//========================================
//
//	後更新時
//
//========================================
void MakeEnemyScript::LateUpdate()
{
	// デバック表示
	PrintDebugProc("EntityNum:%d\n", GetEntityManager()->GetEntityCount());
}

//========================================
//
//	終了時
//
//========================================
void MakeEnemyScript::End()
{
}

//========================================
//
//	移動向きの更新
//
//========================================
void MakeEnemyScript::UpdateMoveDir()
{
	// 移動向きの変更
	m_bRightMove ^= 1;

	for (int y = 0; y < MAX_ENEMY_NUM_Y; y++)
	{
		for (int x = 0; x < MAX_ENEMY_NUM_X; x++)
		{
			const auto& enemy = m_aEnemy[y * MAX_ENEMY_NUM_X + x].lock();
			if (!enemy) continue;

			// 座標
			Vector3& pos = enemy->transform().lock()->m_pos;

			// 一段下へ
			pos->y -= ENEMY_OFFSET_Y;

			// 移動
			if (m_bRightMove) pos->x += m_fMoveSpeed;
			else pos->x -= m_fMoveSpeed;
		}
	}
}