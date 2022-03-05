#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"
#include "UI_HpBar.h"
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

	
	Player* PlayerActor = CreateActor<Player>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	

	{
		Monster* Actor = CreateActor<Monster>();
		Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
	}

	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(-300.0f, 200.0f, 0.0f));
		Actor->GetTransform()->AttachTransform(PlayerActor->GetTransform());
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
