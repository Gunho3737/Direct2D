#include "PreCompile.h"
#include "EndingLevel.h"
#include <GameEngine\PostFade.h>
#include "GameEngineBase/GameEngineSoundPlayer.h"
#include "EndingScreen.h"
#include "GameEngineBase/GameEngineSoundPlayer.h"

EndingLevel::EndingLevel() // default constructer 디폴트 생성자
{

}

EndingLevel::~EndingLevel() // default destructer 디폴트 소멸자
{

}

void EndingLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());


	{
		EndingScreen* Player = CreateActor<EndingScreen>();
	}
}

void EndingLevel::LevelUpdate(float _DeltaTime)
{}

void EndingLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{}

void EndingLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	FadeOn();
}

void EndingLevel::FadeOn()
{
	FadeEffect->SetData(0.5f, FadeOption::LIGHT);
}

void EndingLevel::FadeOff()
{}