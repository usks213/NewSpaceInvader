//==================================================================
//								MakePillboxScript.h
//	トーチカ作成
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/01/22	トーチカ作成クラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../Engine/ECSCompoent/Script.h"


//===== マクロ定義 =====


//===== クラス定義 =====
namespace ECS
{
	class MakePillboxScript : public Script
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

	};
}
