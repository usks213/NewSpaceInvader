//==================================================================
//								BulletScript.h
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

#pragma once

//====== インクルード部 ======
#include "../Engine/ECSCompoent/Script.h"
#include "PlayerScript.h"


//===== マクロ定義 =====


//===== クラス定義 =====
namespace ECS
{
	class BulletScript : public Script
	{
	private:
		// ----- メンバ -----
		int m_nExitTime;	// 生存時間

		// プレイヤー
		std::weak_ptr<PlayerScript> m_player;

	public:
		// プレイヤーのセット
		void SetPlayer(const std::weak_ptr<PlayerScript>& player) { m_player = player; }

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
