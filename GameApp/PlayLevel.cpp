#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "UI_HpBar.h"
#include "FlyBug.h"
#include "Map.h"
#include "ViewMap.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>


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
		Map* Player = CreateActor<Map>();
	}

	{
	//	ViewMap* Player = CreateActor<ViewMap>();
	}

	{
		Player* PlayerActor = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}

	{
		FlyBug* Actor = CreateActor<FlyBug>();
		Actor->GetTransform()->SetWorldPosition(float4(6050.0f*1.25f, -2200.0f * 1.25f, 0.0f));
	}

	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}

}

void PlayLevel::LevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("DebugOn"))
	{
		if (false == IsDebugCheck())
		{
			DebugOn();
		}
		else
		{
			DebugOff();
		}
		
	}

	static GameEngineRenderWindow* Window = nullptr;

	if (nullptr == GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		Window = GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineRenderWindow>("RenderWindow");
		float4 Size = { 128, 72 };
		Window->PushRenderTarget("메인 카메라 타겟", GetMainCamera()->GetCameraRenderTarget(), Size * 3);
		Window->PushRenderTarget("UI 카메라 타겟", GetUICamera()->GetCameraRenderTarget(), Size * 3);
	}
}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
