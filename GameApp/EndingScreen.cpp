#include "PreCompile.h"
#include "EndingScreen.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "GameEngineBase/GameEngineSoundPlayer.h"

GameEngineSoundPlayer* EndingScreen::EndingBackGroundPlayer = nullptr;

EndingScreen::EndingScreen() // default constructer ����Ʈ ������
{

}

EndingScreen::~EndingScreen() // default destructer ����Ʈ �Ҹ���
{

}

EndingScreen::EndingScreen(EndingScreen&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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