//==================================================================
//								PlayerScript.cpp
//	プレイヤースクリプト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/12/27	プレイヤースクリプトクラス作成(Test)
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "PlayerScript.h"

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
#include "../Engine/ECSCompoent/Rigidbody.h"
#include "../Engine/ECSCompoent/BoxCollider.h"
#include "../Engine/ECSCompoent/SphereCollider.h"

// レンダラー
#include "../Engine/Renderer/Camera.h"
#include "../Engine/Renderer/Light.h"
#include "../Engine/Renderer/PostProcessing.h"


// スクリプト
#include "BulletScript.h"
#include "GameOverScript.h"
#include "HitEffectScript.h"


#include <iostream>


// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define PLAYER_SIZE_X (15 * SCREEN_SCALE_X)
#define PLAYER_SIZE_Y (8 * SCREEN_SCALE_Y)


//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void PlayerScript::Start()
{
	// 自身の取得
	m_myPointer = gameObject().lock()->GetComponent<PlayerScript>();

	// 名前・タグ
	gameObject().lock()->SetName("Player");
	gameObject().lock()->SetTag("Player");

	transform().lock()->m_pos = Vector3(0, -SCREEN_CENTER_Y + PLAYER_SIZE_Y * 2, 0);
	transform().lock()->m_scale = Vector3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 1);

	// コンポーネントの追加

	// レンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/Player.png");

	// コライダー
	const auto& collider = gameObject().lock()->AddComponent<BoxCollider>();

	// カメラ
	//CCamera::GetMainCamera()->SetCameraTarget(gameObject().lock()->transform().lock());
	// ライト
	//CLight::GetMainLight()->SetLightTarget(gameObject().lock()->transform().lock());


	// デルタカウンター
	m_nDeltaCount = 0;
	// ショット
	m_bShot = true;

	//HP
	m_fHP = m_fMaxHP;

	// ヒール
	m_fHeel = 5.0f / 60.0f;
	m_nHeelCnt = m_nHeelInteral;

	// ダメージ
	m_fDamage = 30.0f;
	m_nDamageCnt = m_nDamageInteral;

	// アクティブ
	m_bActive = true;

	// BGM
	CSound::PlayBGM("GameBGM.mp3", 0.3f);
}

//========================================
//
//	更新時
//
//========================================
void PlayerScript::Update()
{
	// アクティブ
	if (!m_bActive) return;

	const float speed = 2.0f * SCREEN_SCALE_X;

	// 移動	
	if (GetKeyPress(VK_D) || GetKeyPress(VK_RIGHT))
	{
		transform().lock()->m_pos->x += speed;
	}
	if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT))
	{
		transform().lock()->m_pos->x -= speed;
	}

	// 境界判定
	Vector3& pos = transform().lock()->m_pos;
	Vector3 half = transform().lock()->m_scale / 2;
	if (pos->x - half->x < -SCREEN_CENTER_X) pos->x = -SCREEN_CENTER_X + half->x;
	if (pos->x + half->x > SCREEN_CENTER_X) pos->x = SCREEN_CENTER_X - half->x;

	// ショット
	if (GetKeyPress(VK_SPACE) && m_bShot)
	{
		const auto& test = Instantiate<GameObject>();
		test->AddComponent<BulletScript>()->SetPlayer(m_myPointer.lock());
		const auto& rb = test->GetComponent<Rigidbody>();

		Vector3 dir = Vector3{ 0, 1, 0 };

		test->transform().lock()->m_pos = transform().lock()->m_pos + dir * PLAYER_SIZE_Y / 4;
		rb->AddForceY(speed * 1.5f);

		// ショットフラグ
		m_bShot = false;

		// サウンド
		CSound::PlaySE("Shot.wav", 0.3f);

	}
}

//========================================
//
//	後更新時
//
//========================================
void PlayerScript::LateUpdate()
{
	// アクティブ
	if (!m_bActive) return;

	// デバック表示
	PrintDebugProc("DeltaCount:%d\n", m_nDeltaCount);

	// ステータス
	m_nHeelCnt--;
	if (m_nHeelCnt < 0)
	{
		// 回復
		//m_fHP += m_fHeel;
	}
	// 最大値
	if (m_fHP > m_fMaxHP)
		m_fHP = m_fMaxHP;

	// ダメージ
	m_nDamageCnt--;


	// HPを画面に反映
	auto post = PostProcessing::GetMain();
	post->GetColor()->y = m_fHP / m_fMaxHP;
	post->GetColor()->z = m_fHP / m_fMaxHP;
}

//========================================
//
//	終了時
//
//========================================
void PlayerScript::End()
{
	FILE* fp;
	int nScore = 0;

	// 前回のスコアを読み込む
	fopen_s(&fp, "data/score.bin", "rb");

	if (fp)
	{
		fread(&nScore, sizeof(int), 1, fp);

		fclose(fp);
	}

	if (m_nDeltaCount > nScore)
	{
		// スコアの書き出し
		fopen_s(&fp, "data/score.bin", "wb");

		if (fp)
		{
			fwrite(&m_nDeltaCount, sizeof(int), 1, fp);

			fclose(fp);
		}
	}
}


//******************** コールバック関数 ********************

//========================================
//
// 当たった時
//
//========================================
void PlayerScript::OnCollisionEnter(Collider* collider)
{
	// アクティブ
	if (!m_bActive) return;

	if (collider->gameObject().lock()->tag() == "EnemyBullet")
	{
		// ダメージ
		if (m_nDamageCnt > 0) return;
		m_nDamageCnt = m_nDamageInteral;

		// HP
		m_fHP -= m_fDamage;
		m_nHeelCnt = m_nHeelInteral;

		// 画面揺れ
		CCamera::GetMainCamera()->SetShakeFrame(16);

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

		// サウンド
		CSound::PlaySE("PlayerDamage.wav", 1.0f);

		if (m_fHP > 0) return;
		// ゲームオーバー
		const auto& gameover = GetEntityManager()->CreateEntity<GameObject>();
		gameover->AddComponent<GameOverScript>();

		// アクティブ
		m_bActive = false;

		// 削除
		Destroy(gameObject().lock());

	}
}

//========================================
//
// 当たっている間
//
//========================================
void PlayerScript::OnCollisionStay(Collider* collider)
{
	// 同じ処理
	OnCollisionEnter(collider);
}

//========================================
//
// 離れた時
//
//========================================
void PlayerScript::OnCollisionExit(Collider* collider)
{

}

