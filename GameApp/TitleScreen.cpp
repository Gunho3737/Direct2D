#include "PreCompile.h"
#include "TitleScreen.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "GameEngineBase/GameEngineSoundPlayer.h"

GameEngineSoundPlayer* TitleScreen::TitleBackGroundPlayer = nullptr;

TitleScreen::TitleScreen() // default constructer ����Ʈ ������
{

}

TitleScreen::~TitleScreen() // default destructer ����Ʈ �Ҹ���
{

}

TitleScreen::TitleScreen(TitleScreen&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void TitleScreen::Start()
{
	BackGroundImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackGroundImageRenderer->CreateAnimationFolder("TitleBackGround", "TitleBackGround", 0.05f);
	BackGroundImageRenderer->SetChangeAnimation("TitleBackGround");
	BackGroundImageRenderer->GetTransform()->SetLocalScaling(BackGroundImageRenderer->GetFolderTextureImageSize());

	LogoImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	LogoImageRenderer->SetImage("TitleLogo.png");
	LogoImageRenderer->GetTransform()->SetLocalScaling(LogoImageRenderer->GetCurrentTexture()->GetTextureSize());
	LogoImageRenderer->GetTransform()->SetLocalPosition({0.0f, 100.0f, 0.0f});

	TitleScreen::TitleBackGroundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();

	TitleScreen::TitleBackGroundPlayer->PlayAlone("Title.mp3");
}

void TitleScreen::Update(float _DeltaTime)
{
	
}