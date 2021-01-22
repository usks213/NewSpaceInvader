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

#pragma once

//====== インクルード部 ======
#include "../Engine/ECSCompoent/Script.h"
#include "EnemyBaseScript.h"


//===== マクロ定義 =====


//===== クラス定義 =====
namespace ECS
{
	class MakeEnemyScript : public Script
	{
	private:
		// ----- メンバ -----
		enum EEnemyType
		{
			eEnemy1,
			eEnemy2,
			eEnemy3,
			eUFO,

			eMaxType,
		};

		// プレイヤーオブジェクト
		std::weak_ptr<GameObject> m_player;

		// エネミー配列
		std::vector<std::weak_ptr<EnemyBaseScript>> m_aEnemy;
		// エネミー数
		int m_nEnemyCount;

		// 移動向き
		bool m_bRightMove;
		// 移動間隔
		int m_nMoveCount;
		// 移動速度
		float m_fMoveSpeed;

		// 弾の生成フラグ
		bool m_bShot;
		// 弾の速度
		float m_fBulletSpeed;

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

	public:
		// プレイヤーのセット
		void SetPlayer(std::weak_ptr<GameObject> player) { m_player = player; }
		// 移動向きの更新
		void UpdateMoveDir();
		// エネミー減少
		void SubEnemyCnt() { m_nEnemyCount--; }
	};
}
