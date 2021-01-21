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

#pragma once

//====== インクルード部 ======
#include "../Engine/ECSCompoent/Script.h"


//===== マクロ定義 =====
#define ENEMY_SIZE_X (12 * SCREEN_SCALE_X)
#define ENEMY_SIZE_Y (12 * SCREEN_SCALE_Y)


//===== クラス定義 =====
namespace ECS
{
	class MakeEnemyScript;

	class EnemyBaseScript : public Script
	{
		friend MakeEnemyScript;
	protected:
		// ----- メンバ -----
		// メイカー
		std::weak_ptr<MakeEnemyScript> m_enemyMaker;
		// レンダラー
		std::weak_ptr<SpriteRenderer> m_sprite;
		// 自身のポインタ
		std::weak_ptr<EnemyBaseScript> m_myPointer;
		// ショット
		bool m_bShot;
	public:
		// メイカーのセット
		void SetEnemyMaker(std::weak_ptr<MakeEnemyScript> maker) { m_enemyMaker = maker; }
		// ショットフラグ
		void SetShotFlg(bool shot) { m_bShot = shot; }
		// テクスチャの指定
		void SetTexure(int nType);
	protected:
		// ----- メソッド -----

		// 開始時に呼ばれます
		void Start() override;
		// 毎フレーム呼ばれます
		void Update() override;
		// 毎フレーム更新後に呼ばれます
		void LateUpdate() override;
		// 終了時に呼ばれます
		void End() override;

		// ショット
		void Shot(float speed);

		// ----- コールバック関数 -----

		// 当たった時
		virtual void OnCollisionEnter(Collider* collider) override;
		// 当たっている間
		virtual void OnCollisionStay(Collider* collider) override;
		// 離れた時
		virtual void OnCollisionExit(Collider* collider) override;
	};
}
