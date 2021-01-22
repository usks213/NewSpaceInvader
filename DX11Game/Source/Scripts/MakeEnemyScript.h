//==================================================================
//								MakeEnemyScript.h
//	�G�l�~�[�����X�N���v�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2021/01/08	�G�l�~�[�����X�N���v�g�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../Engine/ECSCompoent/Script.h"
#include "EnemyBaseScript.h"


//===== �}�N����` =====


//===== �N���X��` =====
namespace ECS
{
	class MakeEnemyScript : public Script
	{
	private:
		// ----- �����o -----
		enum EEnemyType
		{
			eEnemy1,
			eEnemy2,
			eEnemy3,
			eUFO,

			eMaxType,
		};

		// �v���C���[�I�u�W�F�N�g
		std::weak_ptr<GameObject> m_player;

		// �G�l�~�[�z��
		std::vector<std::weak_ptr<EnemyBaseScript>> m_aEnemy;
		// �G�l�~�[��
		int m_nEnemyCount;

		// �ړ�����
		bool m_bRightMove;
		// �ړ��Ԋu
		int m_nMoveCount;
		// �ړ����x
		float m_fMoveSpeed;

		// �e�̐����t���O
		bool m_bShot;
		// �e�̑��x
		float m_fBulletSpeed;

	protected:
		// ----- ���\�b�h -----

		// �J�n���ɌĂ΂�܂�
		void Start() override;
		// ���t���[���Ă΂�܂�
		void Update() override;
		// ���t���[���X�V��ɌĂ΂�܂�
		void LateUpdate() override;
		// �I�����ɌĂ΂�܂�
		void End() override;

	public:
		// �v���C���[�̃Z�b�g
		void SetPlayer(std::weak_ptr<GameObject> player) { m_player = player; }
		// �ړ������̍X�V
		void UpdateMoveDir();
		// �G�l�~�[����
		void SubEnemyCnt() { m_nEnemyCount--; }
	};
}
