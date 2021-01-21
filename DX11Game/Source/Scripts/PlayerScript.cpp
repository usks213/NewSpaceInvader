//==================================================================
//								PlayerScript.cpp
//	�v���C���[�X�N���v�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/12/27	�v���C���[�X�N���v�g�N���X�쐬(Test)
//
//===================================================================


//====== �C���N���[�h�� ======

// ���g
#include "PlayerScript.h"

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
#include "../Engine/ECSCompoent/Rigidbody.h"
#include "../Engine/ECSCompoent/BoxCollider.h"
#include "../Engine/ECSCompoent/SphereCollider.h"

// �����_���[
#include "../Engine/Renderer/Camera.h"
#include "../Engine/Renderer/Light.h"
#include "../Engine/Renderer/PostProcessing.h"


// �X�N���v�g
#include "BulletScript.h"
#include "GameOverScript.h"
#include "HitEffectScript.h"


#include <iostream>


// �l�[���X�y�[�X
using namespace ECS;


//===== �}�N����` =====
#define PLAYER_SIZE_X (15 * SCREEN_SCALE_X)
#define PLAYER_SIZE_Y (8 * SCREEN_SCALE_Y)


//******************** �X�N���v�g���\�b�h ********************


//========================================
//
//	�J�n��
//
//========================================
void PlayerScript::Start()
{
	// ���g�̎擾
	m_myPointer = gameObject().lock()->GetComponent<PlayerScript>();

	// ���O�E�^�O
	gameObject().lock()->SetName("Player");
	gameObject().lock()->SetTag("Player");

	transform().lock()->m_pos = Vector3(0, -SCREEN_CENTER_Y + PLAYER_SIZE_Y * 2, 0);
	transform().lock()->m_scale = Vector3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 1);

	// �R���|�[�l���g�̒ǉ�

	// �����_���[
	const auto& renderer = gameObject().lock()->AddComponent<SpriteRenderer>();
	renderer->SetDiffuseTexture("data/texture/Player.png");

	// �R���C�_�[
	const auto& collider = gameObject().lock()->AddComponent<BoxCollider>();

	// �J����
	//CCamera::GetMainCamera()->SetCameraTarget(gameObject().lock()->transform().lock());
	// ���C�g
	//CLight::GetMainLight()->SetLightTarget(gameObject().lock()->transform().lock());


	// �f���^�J�E���^�[
	m_nDeltaCount = 0;
	// �V���b�g
	m_bShot = true;

	//HP
	m_fHP = m_fMaxHP;

	// �q�[��
	m_fHeel = 5.0f / 60.0f;
	m_nHeelCnt = m_nHeelInteral;

	// �_���[�W
	m_fDamage = 30.0f;
	m_nDamageCnt = m_nDamageInteral;

	// �A�N�e�B�u
	m_bActive = true;

	// BGM
	CSound::PlayBGM("GameBGM.mp3", 0.3f);
}

//========================================
//
//	�X�V��
//
//========================================
void PlayerScript::Update()
{
	// �A�N�e�B�u
	if (!m_bActive) return;

	const float speed = 2.0f * SCREEN_SCALE_X;

	// �ړ�	
	if (GetKeyPress(VK_D) || GetKeyPress(VK_RIGHT))
	{
		transform().lock()->m_pos->x += speed;
	}
	if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT))
	{
		transform().lock()->m_pos->x -= speed;
	}

	// ���E����
	Vector3& pos = transform().lock()->m_pos;
	Vector3 half = transform().lock()->m_scale / 2;
	if (pos->x - half->x < -SCREEN_CENTER_X) pos->x = -SCREEN_CENTER_X + half->x;
	if (pos->x + half->x > SCREEN_CENTER_X) pos->x = SCREEN_CENTER_X - half->x;

	// �V���b�g
	if (GetKeyPress(VK_SPACE) && m_bShot)
	{
		const auto& test = Instantiate<GameObject>();
		test->AddComponent<BulletScript>()->SetPlayer(m_myPointer.lock());
		const auto& rb = test->GetComponent<Rigidbody>();

		Vector3 dir = Vector3{ 0, 1, 0 };

		test->transform().lock()->m_pos = transform().lock()->m_pos + dir * PLAYER_SIZE_Y / 4;
		rb->AddForceY(speed * 1.5f);

		// �V���b�g�t���O
		m_bShot = false;

		// �T�E���h
		CSound::PlaySE("Shot.wav", 0.3f);

	}
}

//========================================
//
//	��X�V��
//
//========================================
void PlayerScript::LateUpdate()
{
	// �A�N�e�B�u
	if (!m_bActive) return;

	// �f�o�b�N�\��
	PrintDebugProc("DeltaCount:%d\n", m_nDeltaCount);

	// �X�e�[�^�X
	m_nHeelCnt--;
	if (m_nHeelCnt < 0)
	{
		// ��
		//m_fHP += m_fHeel;
	}
	// �ő�l
	if (m_fHP > m_fMaxHP)
		m_fHP = m_fMaxHP;

	// �_���[�W
	m_nDamageCnt--;


	// HP����ʂɔ��f
	auto post = PostProcessing::GetMain();
	post->GetColor()->y = m_fHP / m_fMaxHP;
	post->GetColor()->z = m_fHP / m_fMaxHP;
}

//========================================
//
//	�I����
//
//========================================
void PlayerScript::End()
{
	FILE* fp;
	int nScore = 0;

	// �O��̃X�R�A��ǂݍ���
	fopen_s(&fp, "data/score.bin", "rb");

	if (fp)
	{
		fread(&nScore, sizeof(int), 1, fp);

		fclose(fp);
	}

	if (m_nDeltaCount > nScore)
	{
		// �X�R�A�̏����o��
		fopen_s(&fp, "data/score.bin", "wb");

		if (fp)
		{
			fwrite(&m_nDeltaCount, sizeof(int), 1, fp);

			fclose(fp);
		}
	}
}


//******************** �R�[���o�b�N�֐� ********************

//========================================
//
// ����������
//
//========================================
void PlayerScript::OnCollisionEnter(Collider* collider)
{
	// �A�N�e�B�u
	if (!m_bActive) return;

	if (collider->gameObject().lock()->tag() == "EnemyBullet")
	{
		// �_���[�W
		if (m_nDamageCnt > 0) return;
		m_nDamageCnt = m_nDamageInteral;

		// HP
		m_fHP -= m_fDamage;
		m_nHeelCnt = m_nHeelInteral;

		// ��ʗh��
		CCamera::GetMainCamera()->SetShakeFrame(16);

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

		// �T�E���h
		CSound::PlaySE("PlayerDamage.wav", 1.0f);

		if (m_fHP > 0) return;
		// �Q�[���I�[�o�[
		const auto& gameover = GetEntityManager()->CreateEntity<GameObject>();
		gameover->AddComponent<GameOverScript>();

		// �A�N�e�B�u
		m_bActive = false;

		// �폜
		Destroy(gameObject().lock());

	}
}

//========================================
//
// �������Ă����
//
//========================================
void PlayerScript::OnCollisionStay(Collider* collider)
{
	// ��������
	OnCollisionEnter(collider);
}

//========================================
//
// ���ꂽ��
//
//========================================
void PlayerScript::OnCollisionExit(Collider* collider)
{

}

