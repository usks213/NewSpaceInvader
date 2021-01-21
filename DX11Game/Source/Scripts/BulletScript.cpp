//==================================================================
//								BulletScript.cpp
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


//====== �C���N���[�h�� ======

// ���g
#include "BulletScript.h"

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


// �l�[���X�y�[�X
using namespace ECS;


//===== �}�N����` =====
#define PLAYERBULLET_SIZE_X (1 * SCREEN_SCALE_X)
#define PLAYERBULLET_SIZE_Y (4 * SCREEN_SCALE_Y)


//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
//
//========================================
void BulletScript::Start()
{
	// ���O�E�^�O
	gameObject().lock()->SetName("PlayerBullet");
	gameObject().lock()->SetTag("PlayerBullet");

	// �傫��
	transform().lock()->m_scale = Vector3(PLAYERBULLET_SIZE_X, PLAYERBULLET_SIZE_Y, 1);

	//--- �R���|�[�l���̒ǉ�

	// �C���X�^���V���O�����_���[
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/PlayerBullt.png");

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
void BulletScript::Update()
{
	m_nExitTime--;
	if (m_nExitTime < 0)
	{
		// �V���b�g�t���O������
		const auto& player = m_player.lock();
		if (player)
			player->SetShotFlg(true);

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}

	// ��ʊO
	Vector3 pos = transform().lock()->m_pos;
	Vector3 scale = transform().lock()->m_scale;
	if (pos->y - scale->y > SCREEN_CENTER_Y)
	{
		// �V���b�g�t���O������
		const auto& player = m_player.lock();
		if (player)
			player->SetShotFlg(true);

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
//	��X�V��
//
//========================================
void BulletScript::LateUpdate()
{
}

//========================================
//
//	�I����
//
//========================================
void BulletScript::End()
{
}


//******************** �R�[���o�b�N�֐� ********************

//========================================
//
// ����������
//
//========================================
void BulletScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "Enemy" ||
		collider->gameObject().lock()->tag() == "EnemyBullet" ||
		collider->gameObject().lock()->tag() == "Wall" ||
		collider->gameObject().lock()->tag() == "Pillbox")
	{
		// �V���b�g�t���O������
		const auto& player = m_player.lock();
		if (player)
			player->SetShotFlg(true);

		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
// �������Ă����
//
//========================================
void BulletScript::OnCollisionStay(Collider* collider)
{
	// ��������
	OnCollisionEnter(collider);
}

//========================================
//
// ���ꂽ��
//
//========================================
void BulletScript::OnCollisionExit(Collider* collider)
{
}

