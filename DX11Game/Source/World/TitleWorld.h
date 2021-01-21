//==================================================================
//												TitleWorld.h
//	タイトルワールド
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/15	タイトルワールドクラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../Engine/ECS/World/World.h"


//===== マクロ定義 =====


//===== クラス定義 =====
namespace ECS
{
	// タイトルワールドクラス
	class TitleWorld : public World
	{
	public:
		// コンストラクタ
		TitleWorld(std::string name);
		// デストラクタ
		virtual ~TitleWorld();

		// ワールドの初期化
		virtual void Start();
		// ワールドの終了
		virtual void End();
	};
}
