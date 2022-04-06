#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleScreen.h"
#include "UserGame.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst().CreateKey("AimUp", VK_UP);
		GameEngineInput::GetInst().CreateKey("AimDown", VK_DOWN);
		GameEngineInput::GetInst().CreateKey("Attack", 'X');
		GameEngineInput::GetInst().CreateKey("Jump", 'Z');
		GameEngineInput::GetInst().CreateKey("DebugOn", 'R');
		GameEngineInput::GetInst().CreateKey("NextLevel", VK_SPACE);
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
void TitleLevel::LevelChangeEndEvent()
{

}
void TitleLevel::LevelChangeStartEvent() 
{

}