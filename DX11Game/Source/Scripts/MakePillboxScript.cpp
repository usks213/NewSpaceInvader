//==================================================================
//								MakePillboxScript.h
//	�g�[�`�J�쐬
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/01/22	�g�[�`�J�쐬�N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======

// ���g
#include "MakePillboxScript.h"

// �V�X�e��
#include "../Engine/System/input.h"
#include "../Engine/System/Sound.h"

// �}�l�[�W���[
#include "../Engine/ECS/Entity/EntityManager.h"

// �G���e�B�e�B
#include "../Engine/ECSEntity/GameObject.h"

// �R���|�[�l���g
#include "../Engine/ECSCompoent/Transform.h"
#include "../Engine/ECSCompoent/MeshRenderer.h"
#include "../Engine/ECSCompoent/BillboardRenderer.h"
#include "../Engine/ECSCompoent/AssimpRenderer.h"
#include "../Engine/ECSCompoent/SpriteRenderer.h"
#include "../Engine/ECSCompoent/InstancingMeshRenderer.h"
#include "../Engine/ECSCompoent/Rigidbody.h"
#include "../Engine/ECSCompoent/BoxCollider.h"
#include "../Engine/ECSCompoent/SphereCollider.h"

// �X�N���v�g
#include "PillboxScript.h"


// �l�[���X�y�[�X
using namespace ECS;


//===== �}�N����` =====
#define MAX_PILLBOX_X (20 / 2)
#define MAX_PILLBOX_Y (16 / 2)

#define MAX_PILLBOX_NUM (4)

//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
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
				// �g�[�`�J�̌`��
				if ((y < MAX_PILLBOX_X / 5) &&
					(x < k || x >= MAX_PILLBOX_X - k)) continue;

				if((y >= MAX_PILLBOX_Y - MAX_PILLBOX_X / 5) &&
					x >= k && x < MAX_PILLBOX_X - k) continue;


				const auto& obj = Instantiate<GameObject>(pos);
				obj->AddComponent<PillboxScript>();
			}
			pos->y -= PILLBOX_SIZE_Y;
			pos->x = posX;

			// �`�̌v�Z
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
//	�X�V��
//
//========================================
void MakePillboxScript::Update()
{
}

//========================================
//
//	��X�V��
//
//========================================
void MakePillboxScript::LateUpdate()
{
}

//========================================
//
//	�I����
//
//========================================
void MakePillboxScript::End()
{
}

