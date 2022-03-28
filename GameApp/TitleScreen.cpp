#include "PreCompile.h"
#include "TitleScreen.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"


TitleScreen::TitleScreen() // default constructer 디폴트 생성자
{

}

TitleScreen::~TitleScreen() // default destructer 디폴트 소멸자
{

}

TitleScreen::TitleScreen(TitleScreen&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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