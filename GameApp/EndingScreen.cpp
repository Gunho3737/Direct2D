#include "PreCompile.h"
#include "EndingScreen.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "GameEngineBase/GameEngineSoundPlayer.h"

GameEngineSoundPlayer* EndingScreen::EndingBackGroundPlayer = nullptr;

EndingScreen::EndingScreen() // default constructer 디폴트 생성자
{

}

EndingScreen::~EndingScreen() // default destructer 디폴트 소멸자
{

}

EndingScreen::EndingScreen(EndingScreen&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void EndingScreen::Start()
{

	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ImageRenderer->SetImage("Ending.png");
	ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());

	EndingScreen::EndingBackGroundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();

	//EndingScreen::TitleBackGroundPlayer->PlayAlone("Title.mp3");
}

void EndingScreen::Update(float _DeltaTime)
{
	
}