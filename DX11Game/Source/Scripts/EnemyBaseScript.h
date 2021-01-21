//==================================================================
//								EnemyBaseScript.h
//	�G�l�~�[�x�[�X�X�N���v�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2021/01/09	�G�l�~�[�x�[�X�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../Engine/ECSCompoent/Script.h"


//===== �}�N����` =====
#define ENEMY_SIZE_X (12 * SCREEN_SCALE_X)
#define ENEMY_SIZE_Y (12 * SCREEN_SCALE_Y)


//===== �N���X��` =====
namespace ECS
{
	class MakeEnemyScript;

	class EnemyBaseScript : public Script
	{
		friend MakeEnemyScript;
	protected:
		// ----- �����o -----
		// ���C�J�[
		std::weak_ptr<MakeEnemyScript> m_enemyMaker;
		// �����_���[
		std::weak_ptr<SpriteRenderer> m_sprite;
		// ���g�̃|�C���^
		std::weak_ptr<EnemyBaseScript> m_myPointer;
		// �V���b�g
		bool m_bShot;
	public:
		// ���C�J�[�̃Z�b�g
		void SetEnemyMaker(std::weak_ptr<MakeEnemyScript> maker) { m_enemyMaker = maker; }
		// �V���b�g�t���O
		void SetShotFlg(bool shot) { m_bShot = shot; }
		// �e�N�X�`���̎w��
		void SetTexure(int nType);
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

		// �V���b�g
		void Shot(float speed);

		// ----- �R�[���o�b�N�֐� -----

		// ����������
		virtual void OnCollisionEnter(Collider* collider) override;
		// �������Ă����
		virtual void OnCollisionStay(Collider* collider) override;
		// ���ꂽ��
		virtual void OnCollisionExit(Collider* collider) override;
	};
}
