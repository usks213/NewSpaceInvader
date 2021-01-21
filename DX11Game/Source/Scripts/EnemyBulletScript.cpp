//==================================================================
//								EnemyEnemyBulletScript.h
//	�G�l�~�[�o���b�g�X�N���v�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2021/01/22	�G�l�~�[�o���b�g�X�N���v�g�N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======

// ���g
#include "EnemyBulletScript.h"

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
#include "HitEffectScript.h"


// �l�[���X�y�[�X
using namespace ECS;


//===== �}�N����` =====
#define ENEMY_BULLET_SIZE_X (3 * SCREEN_SCALE_X)
#define ENEMY_BULLET_SIZE_Y (7 * SCREEN_SCALE_Y)


//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
//
//========================================
void EnemyBulletScript::Start()
{
	// ���O�E�^�O
	gameObject().lock()->SetName("EnemyBullet");
	gameObject().lock()->SetTag("EnemyBullet");

	// �傫��
	transform().lock()->m_scale = Vector3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 1);

	//--- �R���|�[�l���̒ǉ�

	// �C���X�^���V���O�����_���[
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/EnemyBullet.png");

	// ECS���W�b�h�{�f�B
	const auto& rb = gameObject().lock()->AddComponent<Rigidbody>();
	rb->SetDrag({ 0,0,0 });
	rb->SetGravityForce({ 0,0,0 });
	rb->SetStaticFriction(0);
	rb->SetDynamicFriction(0);
	rb->SetMass(1);
	rb->SetTorqueDrag({ 0,0,0 });
	rb->SetUsePhysics(false);
	rb->SetUseGravity(false);

	// ECS�R���C�_�[
	gameObject().lock()->AddComponent<BoxCollider>();


	// ��������
	m_nExitTime = 120;
}

//========================================
//
//	�X�V��
//
//========================================
void EnemyBulletScript::Update()
{
	m_nExitTime--;
	if (m_nExitTime < 0)
	{
		// �V���b�g�t���O������
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}

	// ��ʊO(��)
	Vector3 pos = transform().lock()->m_pos;
	Vector3 scale = transform().lock()->m_scale;
	if (pos->y + scale->y < -SCREEN_CENTER_Y)
	{
		// �V���b�g�t���O������
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
//	��X�V��
//
//========================================
void EnemyBulletScript::LateUpdate()
{
}

//========================================
//
//	�I����
//
//========================================
void EnemyBulletScript::End()
{
}


//******************** �R�[���o�b�N�֐� ********************

//========================================
//
// ����������
//
//========================================
void EnemyBulletScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "PlayerBullet" ||
		collider->gameObject().lock()->tag() == "Wall" ||
		collider->gameObject().lock()->tag() == "Pillbox")
	{
		// �V���b�g�t���O������
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

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

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
	else if (collider->gameObject().lock()->tag() == "Player")
	{
		// �V���b�g�t���O������
		const auto& enemy = m_enemy.lock();
		if (enemy)
			enemy->SetShotFlg(true);

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
// �������Ă����
//
//========================================
void EnemyBulletScript::OnCollisionStay(Collider* collider)
{
	// ��������
	OnCollisionEnter(collider);
}

//========================================
//
// ���ꂽ��
//
//========================================
void EnemyBulletScript::OnCollisionExit(Collider* collider)
{
}

