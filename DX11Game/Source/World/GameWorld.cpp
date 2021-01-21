//==================================================================
//												GameWorld.cpp
//	�Q�[�����[���h
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2021/01/11	�Q�[�����[���h�N���X�쐬
//				�Q�[���V�[�����ڐA
//
//===================================================================


//===== �C���N���[�h�� =====
#include "GameWorld.h"

// �V�X�e��
#include "../Engine/ECS/Entity/EntityManager.h"
#include "../Engine/ECSEntity/GameObject.h"
#include "../Engine/Renderer/Camera.h"
#include "../Engine/System/Sound.h"

// �R���|�[�l���g
#include "../Engine/ECSCompoent/Transform.h"
#include "../Engine/ECSCompoent/MeshRenderer.h"

// �X�N���v�g
#include "../Scripts/PlayerScript.h"
#include "../Scripts/MakeEnemyScript.h"
#include "../Scripts/DeltaUIScript.h"


using namespace ECS;


//===== �}�N����` =====


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===================================
//
//	�R���X�g���N�^
//
//===================================
GameWorld::GameWorld(std::string name)
	:World(name)
{
}

//===================================
//
//	�f�X�g���N�^
//
//===================================
GameWorld::~GameWorld()
{
}

//===================================
//
//	���[���h�̏�����
//
//===================================
void GameWorld::Start()
{
	//--- �Q�[���I�u�W�F�N�g��ǉ�

	// �v���C���[
	const auto& player = GetEntityManager()->CreateEntity<GameObject>();
	const auto & playerScript = player->AddComponent<PlayerScript>();

	//// �f���^UI
	//const auto& deltaUi = GetEntityManager()->CreateEntity<GameObject>();
	//deltaUi->AddComponent<DeltaUIScript>()->SetPlayer(playerScript);

	// �G�l�~�[���C�J�[
	const auto& enemyMaker = GetEntityManager()->CreateEntity<GameObject>();
	enemyMaker->AddComponent<MakeEnemyScript>()->SetPlayer(player);
	
	//// �J�[�\��
	//const auto& cursor = GetEntityManager()->CreateEntity<GameObject>();
	//const auto& cursorRn = cursor->AddComponent<SpriteRenderer>();
	//cursorRn->SetDiffuseTexture("data/texture/Cursor.png");
	//cursorRn->SetLayer(cursorRn->eUI1);
	//cursor->transform().lock()->m_scale = Vector3{ 64 * SCREEN_SCALE_X,64 * SCREEN_SCALE_Y,32 };

	//// ����UI
	//const auto& opUI = GetEntityManager()->CreateEntity<GameObject>();
	//const auto& opSpr = opUI->AddComponent<SpriteRenderer>();
	//opSpr->SetDiffuseTexture("data/texture/OperationUI.png");
	//opSpr->SetLayer(opSpr->eUI1);
	//opUI->transform().lock()->m_pos = Vector3{ -SCREEN_CENTER_X / 3.0f * 2, -SCREEN_HEIGHT / 3.85f, 1 };
	//opUI->transform().lock()->m_scale = Vector3{ 2400.0f / 6 * SCREEN_SCALE_X, 2100.0f / 6 * SCREEN_SCALE_Y, 1 };

}

//===================================
//
//	���[���h�̏I��
//
//===================================
void GameWorld::End()
{
	// BGM
	CSound::StopBGM("GameBGM.mp3");

}
