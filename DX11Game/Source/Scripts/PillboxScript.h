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

#pragma once

//====== インクルード部 ======
#include "../Engine/ECSCompoent/Script.h"
#include "PlayerScript.h"


//===== マクロ定義 =====
#define PILLBOX_SIZE_X (2 * SCREEN_SCALE_X)
#define PILLBOX_SIZE_Y (2 * SCREEN_SCALE_Y)


//===== クラス定義 =====
namespace ECS
{
	class PillboxScript : public Script
	{
	private:
		// ----- メンバ -----

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
