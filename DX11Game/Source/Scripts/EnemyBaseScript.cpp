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


//====== �C���N���[�h�� ======

// ���g
#include "EnemyBaseScript.h"

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
#include "EnemyEffectScript.h"
#include "MakeEnemyScript.h"
#include "EnemyBulletScript.h"
#include "HitEffectScript.h"


// �l�[���X�y�[�X
using namespace ECS;


//===== �}�N����` =====


//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
//
//========================================
void EnemyBaseScript::Start()
{
	// ���g�̎擾
	m_myPointer = gameObject().lock()->GetComponent<EnemyBaseScript>();

	// ���O�E�^�O
	gameObject().lock()->SetName("Enemy");
	gameObject().lock()->SetTag("Enemy");

	// �傫��
	transform().lock()->m_scale = Vector3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 1);


	//--- �R���|�[�l���̒ǉ�

	// �X�v���C�g
	// �����_���[
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetTexSize(Vector3{ 0.5f, 1.0f, 1.0f });
	renderer->UpdateTexMatrix();
	m_sprite = renderer;

	// �R���C�_�[
	gameObject().lock()->AddComponent<BoxCollider>();


}

//========================================
//
//	�X�V��
//
//========================================
void EnemyBaseScript::Update()
{
	
}

//========================================
//
//	��X�V��
//
//========================================
void EnemyBaseScript::LateUpdate()
{
	// ���C�J�[���擾
	const auto& maker = m_enemyMaker.lock();
	if (!maker) return;

	// ���W�X�P�[��
	Vector3 pos = transform().lock()->m_pos;
	Vector3 scale = transform().lock()->m_scale;


	// ���E����
	if (pos->x + scale->x / 2 > SCREEN_CENTER_X ||
		pos->x - scale->x / 2 < -SCREEN_CENTER_X)
	{
		maker->UpdateMoveDir();
	}

}

//========================================
//
//	�I����
//
//========================================
void EnemyBaseScript::End()
{
}

//========================================
//
//	�e�̐���
//
//========================================
void EnemyBaseScript::Shot(float speed)
{
	const auto& test = Instantiate<GameObject>();
	test->AddComponent<EnemyBulletScript>()->SetEnemy(m_myPointer.lock());
	const auto& rb = test->GetComponent<Rigidbody>();

	Vector3 dir = Vector3{ 0, 1, 0 };

	test->transform().lock()->m_pos = transform().lock()->m_pos - dir * ENEMY_SIZE_Y / 4;
	rb->AddForceY(-speed);

	// �V���b�g�t���O
	m_bShot = false;

	// �T�E���h
	//CSound::PlaySE("Shot.wav", 0.3f);
}

void EnemyBaseScript::SetTexure(int nType)
{
	switch (nType)
	{
	case 0:
		m_sprite.lock()->SetDiffuseTexture("data/texture/Enemy1.png");
		break;
	case 1:
		m_sprite.lock()->SetDiffuseTexture("data/texture/Enemy2.png");
		break;
	case 2:
		m_sprite.lock()->SetDiffuseTexture("data/texture/Enemy3.png");
		break;
	default:
		break;
	}
}

//******************** �R�[���o�b�N�֐� ********************

//========================================
//
// ����������
//
//========================================
void EnemyBaseScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "Player" || 
		collider->gameObject().lock()->tag() == "PlayerBullet")
	{
		// �G�t�F�N�g�̐���
		Vector3 dir = { 1,0,0 };
		int num = 8;
		float angle = 360.0f / num;
		for (int i = 0; i < num; i++)
		{
			const auto& effect = Instantiate<GameObject>(transform().lock()->m_pos);
			effect->AddComponent<HitEffectScript>();

			const auto& rb = effect->GetComponent<Rigidbody>();
			dir = dir.RotationZ(i * angle);
			rb->AddForce(dir * SCREEN_SCALE_X);
		}

		// �폜
		Destroy(gameObject().lock());
	}
}

//========================================
//
// �������Ă����
//
//========================================
void EnemyBaseScript::OnCollisionStay(Collider* collider)
{
	// ����
	OnCollisionEnter(collider);
}

//========================================
//
// ���ꂽ��
//
//========================================
void EnemyBaseScript::OnCollisionExit(Collider* collider)
{
}

