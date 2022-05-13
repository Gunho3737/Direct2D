#include "PreCompile.h"
#include "TitleScreen.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"


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
}

void TitleScreen::Update(float _DeltaTime)
{
}