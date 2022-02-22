#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"
#include "TopUI.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Player* Actor = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Actor->GetTransform()->GetLocalPosition());
	}

	{
		Monster* Actor = CreateActor<Monster>();
		Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
	}

	{
		TopUI* Actor = CreateActor<TopUI>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{

}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
