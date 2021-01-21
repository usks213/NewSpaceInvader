//==================================================================
//								BulletScript.h
//	�o���b�g�X�N���v�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2021/01/07	�o���b�g�X�N���v�g�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../Engine/ECSCompoent/Script.h"
#include "PlayerScript.h"


//===== �}�N����` =====


//===== �N���X��` =====
namespace ECS
{
	class BulletScript : public Script
	{
	private:
		// ----- �����o -----
		int m_nExitTime;	// ��������

		// �v���C���[
		std::weak_ptr<PlayerScript> m_player;

	public:
		// �v���C���[�̃Z�b�g
		void SetPlayer(const std::weak_ptr<PlayerScript>& player) { m_player = player; }

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


		// ----- �R�[���o�b�N�֐� -----

		// ECS
		// ����������
		void OnCollisionEnter(Collider* collider) override;
		// �������Ă����
		void OnCollisionStay(Collider* collider) override;
		// ���ꂽ��
		void OnCollisionExit(Collider* collider) override;
	};
}
