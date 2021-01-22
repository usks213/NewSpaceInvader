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


//====== インクルード部 ======

// 自身
#include "MakePillboxScript.h"

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
#include "PillboxScript.h"


// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define MAX_PILLBOX_X (20 / 2)
#define MAX_PILLBOX_Y (16 / 2)

#define MAX_PILLBOX_NUM (4)

//******************** スクリプトメソッド ********************


//========================================
//
//	開始時
//
//========================================
void MakePillboxScript::Start()
{
	for (int n = 0; n < MAX_PILLBOX_NUM; n++)
	{
		float posX = SCREEN_WIDTH / 8 * (n * 2 + 1) - SCREEN_CENTER_X - PILLBOX_SIZE_X * MAX_PILLBOX_X / 2.0f;
		Vector3 pos = { posX, -SCREEN_CENTER_Y / 2, 0 };
		int k = MAX_PILLBOX_X / 5;

		for (int y = 0; y < MAX_PILLBOX_Y; y++)
		{
			for (int x = 0; x < MAX_PILLBOX_X; x++, pos->x += PILLBOX_SIZE_X)
			{
				// トーチカの形に
				if ((y < MAX_PILLBOX_X / 5) &&
					(x < k || x >= MAX_PILLBOX_X - k)) continue;

				if((y >= MAX_PILLBOX_Y - MAX_PILLBOX_X / 5) &&
					x >= k && x < MAX_PILLBOX_X - k) continue;


				const auto& obj = Instantiate<GameObject>(pos);
				obj->AddComponent<PillboxScript>();
			}
			pos->y -= PILLBOX_SIZE_Y;
			pos->x = posX;

			// 形の計算
			if (y < MAX_PILLBOX_X / 5)
			{
				k--;
				if (k < 0) k = 0;
			}
			if (y == MAX_PILLBOX_Y / 2) k = MAX_PILLBOX_X / 5;
			if (y >= MAX_PILLBOX_Y - MAX_PILLBOX_X / 5)
			{
				k--;
			}

		}
	}

}

//========================================
//
//	更新時
//
//========================================
void MakePillboxScript::Update()
{
}

//========================================
//
//	後更新時
//
//========================================
void MakePillboxScript::LateUpdate()
{
}

//========================================
//
//	終了時
//
//========================================
void MakePillboxScript::End()
{
}

