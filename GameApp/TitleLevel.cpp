#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleScreen.h"
#include "UserGame.h"
#include <GameEngine\PostFade.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst().CreateKey("AimUp", VK_UP);
		GameEngineInput::GetInst().CreateKey("AimDown", VK_DOWN);
		GameEngineInput::GetInst().CreateKey("Attack", 'X');
		GameEngineInput::GetInst().CreateKey("Jump", 'Z');
		GameEngineInput::GetInst().CreateKey("DebugOn", 'R');
		GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');
		GameEngineInput::GetInst().CreateKey("NextLevel", VK_SPACE);
		GameEngineInput::GetInst().CreateKey("SuperUp", 'y');

	}

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MOn", 'p');
		GameEngineInput::GetInst().CreateKey("MOff", 'o');
		GameEngineInput::GetInst().CreateKey("LevelControl", 'i');
	}


	{
		TitleScreen* Player = CreateActor<TitleScreen>();
	}

}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("NextLevel"))
	{
		UserGame::LevelChange("BenchRoom");
	}

}
void TitleLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	FadeOff();
}
void TitleLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	FadeOn();
}

void TitleLevel::FadeOn()
{
	FadeEffect->SetData(0.5f, FadeOption::LIGHT);
}

void TitleLevel::FadeOff()
{
	FadeEffect->SetData(0.5f, FadeOption::DARK);
}