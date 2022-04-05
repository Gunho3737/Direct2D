#include "PreCompile.h"
#include "MiddleRoomLevel.h"
#include "Player.h"
#include "UI_HpBar.h"
#include "FlyBug.h"
#include "BitMap.h"
#include "ViewMap.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>

MiddleRoomLevel::MiddleRoomLevel() // default constructer 디폴트 생성자
{

}

MiddleRoomLevel::~MiddleRoomLevel() // default destructer 디폴트 소멸자
{

}

void MiddleRoomLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		BitMap* Player = CreateActor<BitMap>();
	}

	{
		ViewMap* Player = CreateActor<ViewMap>();
	}

	{
		PlayerActor = CreateActor<Player>();
		PlayerActor->GetTransform()->SetLocalPosition({ 9500.0f,-2800.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}

	{
		FlyBug* Actor = CreateActor<FlyBug>();
		Actor->GetTransform()->SetWorldPosition(float4(6050.0f * 1.25f, -2200.0f * 1.25f, 0.0f));
	}

	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}

}

void MiddleRoomLevel::LevelUpdate(float _DeltaTime)
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

	PlayerPos = PlayerActor->GetTransform()->GetLocalPosition();

	if (PlayerPos.y < -2760.0f)
	{
		if (PlayerPos.x < 10100.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10100.0f, -2760.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10100.0f && PlayerPos.x <= 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -2760.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10250.0f, -2760.0f, PlayerPos.z });
		}
	}
	

	if (PlayerPos.y >= -2760.0f && PlayerPos.y <= -1600.0f )
	{
		if (PlayerPos.x < 10100.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10100.0f, PlayerPos.y, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10100.0f && PlayerPos.x <= 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, PlayerPos.y, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10250.0f, PlayerPos.y, PlayerPos.z });
		}
	}


	if (PlayerPos.y > -1600.0f)
	{
		if (PlayerPos.x < 10100.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10100.0f, -1600.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10100.0f && PlayerPos.x <= 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -1600.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10250.0f, -1600.0f, PlayerPos.z });
		}
	}
	

	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
		float4 Size = { 128, 72};
		Window->PushRenderTarget("메인 카메라 타겟", GetMainCamera()->GetCameraRenderTarget(), Size * 3);
		Window->PushRenderTarget("UI 카메라 타겟", GetUICamera()->GetCameraRenderTarget(), Size * 3);
		Check = true;
	}

	if (true == GameEngineInput::GetInst().Down("LevelControl"))
	{
		GameEngineGUIWindow* Window = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");

		Window->OnOffChange();
	}

}

void MiddleRoomLevel::LevelChangeEndEvent()
{}

void MiddleRoomLevel::LevelChangeStartEvent()
{}
