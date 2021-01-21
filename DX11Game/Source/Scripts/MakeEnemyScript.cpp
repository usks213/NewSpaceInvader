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


//====== �C���N���[�h�� ======

// ���g
#include "MakeEnemyScript.h"

// �V�X�e��
#include "../Engine/System/input.h"
#include "../Engine/System/Sound.h"
#include "../Engine/System/debugproc.h"

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

// ECS�R���|�[�l���g
#include "../Engine/ECSCompoent/Rigidbody.h"
#include "../Engine/ECSCompoent/DeltaCollider.h"

// ECS�V�X�e��
#include "../Engine/ECSSystem/RigidbodySystem.h"
#include "../Engine/ECSSystem/DeltaCollisionSystem.h"

// �X�N���v�g
#include "PlayerScript.h"
#include "EnemyBaseScript.h"



// �l�[���X�y�[�X
using namespace ECS;


//===== �}�N����` =====
#define MAX_ENEMY_NUM_X (11)
#define MAX_ENEMY_NUM_Y (5)
#define MAX_ENEMY_NUM (MAX_ENEMY_NUM_X * MAX_ENEMY_NUM_Y)

#define ENEMY_OFFSET_X (ENEMY_SIZE_X + 4 * SCREEN_SCALE_X)
#define ENEMY_OFFSET_Y (ENEMY_SIZE_Y + 4 * SCREEN_SCALE_Y)

#define MOVE_INTAERVAL (45)

//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
//
//========================================
void MakeEnemyScript::Start()
{
	// ���g�̃|�C���g
	const auto& myPointer = gameObject().lock()->GetComponent<MakeEnemyScript>();

	// �ړ����x
	m_fMoveSpeed = ENEMY_OFFSET_X / 4;
	// �ړ����x����
	m_bRightMove = true;
	// �e�̑��x
	m_fBulletSpeed = m_fMoveSpeed * 0.75f;
	// �e�̐����t���O
	m_bShot = true;

	// �G�l�~�[�̐���
	float initPosX = -SCREEN_CENTER_X + ENEMY_OFFSET_X;
		Vector3 pos = { initPosX, SCREEN_CENTER_Y - ENEMY_OFFSET_Y, 0};

	for (int y = 0; y < MAX_ENEMY_NUM_Y; y++)
	{
		for (int x = 0; x < MAX_ENEMY_NUM_X; x++)
		{
			// �I�u�W�F�N�g�̐���
			const auto& obj = Instantiate<GameObject>(pos);
			const auto& enemy = obj->AddComponent<EnemyBaseScript>();
			enemy->SetEnemyMaker(myPointer);

			// �e�N�X�`���̎w��
			if (y == 0)					enemy->SetTexure(eEnemy1);
			else if(y == 1 || y == 2)	enemy->SetTexure(eEnemy2);
			else if(y == 3 || y == 4)	enemy->SetTexure(eEnemy3);

			// �z��Ɋi�[
			m_aEnemy.push_back(enemy);

			pos->x += ENEMY_OFFSET_X;
		}
		pos->x  = initPosX;
		pos->y -= ENEMY_OFFSET_Y;
	}
}

//========================================
//
//	�X�V��
//
//========================================
void MakeEnemyScript::Update()
{
	// �ړ�����
	m_nMoveCount--;
	if (m_nMoveCount >= 0) return;
	m_nMoveCount = MOVE_INTAERVAL;

	// �e�̐�����L��
	m_bShot = true;

	// �G�l�~�[�̍X�V
	for (int y = 0; y < MAX_ENEMY_NUM_Y; y++)
	{
		for (int x = 0; x < MAX_ENEMY_NUM_X; x++)
		{
			const auto& enemy = m_aEnemy[y * MAX_ENEMY_NUM_X + x].lock();
			if (!enemy) continue;

			// ���W
			Vector3& pos = enemy->transform().lock()->m_pos;

			// �ړ�
			if(m_bRightMove) pos->x += m_fMoveSpeed;
			else pos->x -= m_fMoveSpeed;

			// ���g���O�����݂��邩
			if (y + 1 < MAX_ENEMY_NUM_Y &&
				m_aEnemy[(y + 1) * MAX_ENEMY_NUM_X + x].lock())
			{
				continue;
			}

			// �e�̐���
			if (m_bShot && rand() % 100 < 10)
			{
				enemy->Shot(m_fBulletSpeed);
				m_bShot = false;
			}
		}
	}

}

//========================================
//
//	��X�V��
//
//========================================
void MakeEnemyScript::LateUpdate()
{
	// �f�o�b�N�\��
	PrintDebugProc("EntityNum:%d\n", GetEntityManager()->GetEntityCount());
}

//========================================
//
//	�I����
//
//========================================
void MakeEnemyScript::End()
{
}

//========================================
//
//	�ړ������̍X�V
//
//========================================
void MakeEnemyScript::UpdateMoveDir()
{
	// �ړ������̕ύX
	m_bRightMove ^= 1;

	for (int y = 0; y < MAX_ENEMY_NUM_Y; y++)
	{
		for (int x = 0; x < MAX_ENEMY_NUM_X; x++)
		{
			const auto& enemy = m_aEnemy[y * MAX_ENEMY_NUM_X + x].lock();
			if (!enemy) continue;

			// ���W
			Vector3& pos = enemy->transform().lock()->m_pos;

			// ��i����
			pos->y -= ENEMY_OFFSET_Y;

			// �ړ�
			if (m_bRightMove) pos->x += m_fMoveSpeed;
			else pos->x -= m_fMoveSpeed;
		}
	}
}