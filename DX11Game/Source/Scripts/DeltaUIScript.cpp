//==================================================================
//								DeltaUIScript.h
//	Δ数表示UI
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2021/01/15	Δ表示UIクラス作成
//
//===================================================================


//====== インクルード部 ======

// 自身
#include "DeltaUIScript.h"

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



// ネームスペース
using namespace ECS;


//===== マクロ定義 =====
#define ANIM_DELTA_SPLIT_X (10)  // 画像の分割数(横)
#define ANIM_DELTA_SPLIT_Y (1)  // 画像の分割数(縦)

#define DELTA_SIZE_X	(64*2 * SCREEN_SCALE_X)
#define DELTA_OFFSET_X	(DELTA_SIZE_X * 0.85f)

#define MAX_DELTA (6)


//******************** スクリプトメソッド ********************

//========================================
//
//	開始時
//
//========================================
void DeltaUIData::Start()
{
	// トランスフォーム
	transform().lock()->m_scale = Vector3{ DELTA_SIZE_X, DELTA_SIZE_X, 1 };

	// レンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/DeltaNumber.png");
	renderer->SetLayer(renderer->eUI1);
	renderer->SetTexSize(Vector3{ 1.0f / (float)ANIM_DELTA_SPLIT_X, 1.0f / (float)ANIM_DELTA_SPLIT_Y , 0 });
	m_sprite = renderer;

	// アニメーションナンバー
	m_nAnimNo = 0;

}


//========================================
//
//	開始時
//
//========================================
void DeltaUIScript::Start()
{
	// トランスフォーム
	transform().lock()->m_pos = Vector3{ SCREEN_CENTER_X - DELTA_OFFSET_X * ( 1),
		-SCREEN_CENTER_Y + DELTA_OFFSET_X, 1 };
	transform().lock()->m_scale = Vector3{ DELTA_SIZE_X, DELTA_SIZE_X, 1 };

	// レンダラー
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/DeltaLogo.png");
	renderer->SetLayer(renderer->eUI1);

	// 数字データの生成
	for (int i = 0; i < MAX_DELTA; i++)
	{
		Vector3 pos = transform().lock()->m_pos;
		pos->x -= (MAX_DELTA - i) * DELTA_OFFSET_X;

		const auto& obj = Instantiate<GameObject>(pos);
		m_data.push_back(obj->AddComponent<DeltaUIData>());
	}
}

//========================================
//
//	更新時
//
//========================================
void DeltaUIScript::Update()
{
}

//========================================
//
//	後更新時
//
//========================================
void DeltaUIScript::LateUpdate()
{
	// 数宇の更新
	UpdateTexCoord();
}

//========================================
//
//	終了時
//
//========================================
void DeltaUIScript::End()
{
}

//========================================
//
//	UV更新
//
//========================================
void DeltaUIScript::UpdateTexCoord()
{
	const auto& player = m_player.lock();
	if (!player) return;

	int tmp = player->GetDeltaCount();
	int nCnt = 0;
	// 桁数を数える
	while (tmp > 0)
	{
		tmp /= 10;
		nCnt++;
	}

	// UV更新
	tmp = player->GetDeltaCount();
	for (int i = m_data.size() - 1; 0 <= i; i--)
	{
		const auto& data = m_data[i].lock();
		if (!data) continue;

		data->m_nAnimNo = tmp % 10;

		data->m_sprite.lock()->SetTexPos(
			Vector3{ data->m_sprite.lock()->GetTexSize()->x * (data->m_nAnimNo % ANIM_DELTA_SPLIT_X) ,
					 data->m_sprite.lock()->GetTexSize()->y * (data->m_nAnimNo / ANIM_DELTA_SPLIT_X),
					 0 });

		if (data->m_nAnimNo == 0 && (m_data.size() - i) > nCnt)
		{
			data->m_sprite.lock()->SetAlpha(0);
		}
		else
		{
			data->m_sprite.lock()->SetAlpha(1);
		}

		tmp /= 10;
	}
}