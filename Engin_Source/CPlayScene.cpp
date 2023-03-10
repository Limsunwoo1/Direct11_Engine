#include "CPlayScene.h"
#include "CRenderer.h"
#include "CMeshRenderer.h"
#include "CSpriteRenderer.h"
#include "CResourceManager.h"
#include "CTexture2D.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "CGridScript.h"
#include "CObject.h"
#include "CInput.h"
#include "CCollider2D.h"
#include "CCollisionManager.h"
#include "CBackGround.h"
#include "CAnimator.h"
#include "Cplayer.h"



PlayScene::PlayScene()
	: Scene(eSceneType::Play)
{

}
PlayScene::~PlayScene()
{

}

void PlayScene::Initalize()
{
	// Main Camera Game Object
	{
		GameObject* cameraObj = Object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		Renderer::mainCamera = cameraComp;
	}
	// Ui Camera
	{
		GameObject* uiCamera = Object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* uiCameraComp = uiCamera->AddComponent<Camera>();
		uiCameraComp->DisableLayerMasks();
		uiCameraComp->TurnLayerMask(eLayerType::UI, true);

		uiCameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		Renderer::Cameras->push_back(uiCameraComp);
	}

	// Player
	{
		Player* player = Object::Instantiate<Player>(eLayerType::Player, this);
		player->AddComponent<PlayerScript>();
		player->SetName(L"Zelda");

		Collider2D* collider = player->AddComponent<Collider2D>();
		collider->SetSize(Vector2(1.0f, 1.0f));
		collider->SetType(eColliderType::Rect);

		SpriteRenderer* spr = player->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = ResourceManager::GetInstance()->Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = ResourceManager::GetInstance()->Find<Material>(L"SpriteMaterial");

		spr->SetMesh(mesh);
		spr->SetMaterial(material);

		std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
		texture->Load(L"Zelda.png");
		ResourceManager::GetInstance()->Insert(L"Zelda", texture);

		Animator* animator = player->AddComponent<Animator>();

		animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(120.f, 130.f), Vector2(0.0f, 0.0f), 3, 0.1f);
		animator->Play(L"Idle");
	}

	Scene::Initalize();
}

void PlayScene::Update()
{
	Scene::Update();
}

void PlayScene::FixedUpdate()
{
	Scene::FixedUpdate();
}

void PlayScene::Render()
{
	Scene::Render();
}

void PlayScene::OnEnter()
{

}

void PlayScene::OnExit()
{

}