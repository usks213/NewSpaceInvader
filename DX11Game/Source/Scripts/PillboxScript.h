//==================================================================
//								PillboxScript.h
//	�g�[�`�J�X�N���v�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2021/01/22	�g�[�`�J�X�N���v�g�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../Engine/ECSCompoent/Script.h"
#include "PlayerScript.h"


//===== �}�N����` =====
#define PILLBOX_SIZE_X (2 * SCREEN_SCALE_X)
#define PILLBOX_SIZE_Y (2 * SCREEN_SCALE_Y)


//===== �N���X��` =====
namespace ECS
{
	class PillboxScript : public Script
	{
	private:
		// ----- �����o -----

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
