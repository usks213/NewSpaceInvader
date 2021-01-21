//==================================================================
//								EnemyBulletScript.h
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

#pragma once

//====== インクルード部 ======
#include "../Engine/ECSCompoent/Script.h"
#include "EnemyBaseScript.h"


//===== マクロ定義 =====


//===== クラス定義 =====
namespace ECS
{
	class EnemyBulletScript : public Script
	{
	private:
		// ----- メンバ -----
		int m_nExitTime;	// 生存時間

		// プレイヤー
		std::weak_ptr<EnemyBaseScript> m_enemy;

	public:
		// プレイヤーのセット
		void SetEnemy(const std::weak_ptr<EnemyBaseScript>& enemy) { m_enemy = enemy; }

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


		// ----- コールバック関数 -----

		// ECS
		// 当たった時
		void OnCollisionEnter(Collider* collider) override;
		// 当たっている間
		void OnCollisionStay(Collider* collider) override;
		// 離れた時
		void OnCollisionExit(Collider* collider) override;
	};
}
