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
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ImageRenderer->SetImage("TitleBackGround.png");
	ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());
}

void TitleScreen::Update(float _DeltaTime)
{
}