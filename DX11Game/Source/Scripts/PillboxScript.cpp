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


//====== �C���N���[�h�� ======

// ���g
#include "PillboxScript.h"

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


//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
//
//========================================
void PillboxScript::Start()
{
	// ���O�E�^�O
	gameObject().lock()->SetName("Pillbox");
	gameObject().lock()->SetTag("Pillbox");

	// �傫��
	transform().lock()->m_scale = Vector3(PILLBOX_SIZE_X, PILLBOX_SIZE_Y, 1);

	//--- �R���|�[�l���̒ǉ�

	// �C���X�^���V���O�����_���[
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseColor(1.0f, 0.5f, 0.0f);

	//// ECS���W�b�h�{�f�B
	//const auto& rb = gameObject().lock()->AddComponent<Rigidbody>();
	//rb->SetDrag({ 0,0,0 });
	//rb->SetGravityForce({ 0,0,0 });
	//rb->SetStaticFriction(0);
	//rb->SetDynamicFriction(0);
	//rb->SetMass(1);
	//rb->SetTorqueDrag({ 0,0,0 });
	//rb->SetUsePhysics(false);
	//rb->SetUseGravity(false);

	// �R���C�_�[
	gameObject().lock()->AddComponent<BoxCollider>();

}

//========================================
//
//	�X�V��
//
//========================================
void PillboxScript::Update()
{
}

//========================================
//
//	��X�V��
//
//========================================
void PillboxScript::LateUpdate()
{
}

//========================================
//
//	�I����
//
//========================================
void PillboxScript::End()
{
}


//******************** �R�[���o�b�N�֐� ********************

//========================================
//
// ����������
//
//========================================
void PillboxScript::OnCollisionEnter(Collider* collider)
{
	if (collider->gameObject().lock()->tag() == "Enemy" ||
		collider->gameObject().lock()->tag() == "EnemyBullet" ||
		collider->gameObject().lock()->tag() == "PlayerBullet")
	{
		// ���g�̍폜
		GetEntityManager()->DestroyEntity(gameObject().lock());
	}
}

//========================================
//
// �������Ă����
//
//========================================
void PillboxScript::OnCollisionStay(Collider* collider)
{
	// ��������
	OnCollisionEnter(collider);
}

//========================================
//
// ���ꂽ��
//
//========================================
void PillboxScript::OnCollisionExit(Collider* collider)
{
}

