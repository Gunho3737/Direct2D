#include "PreCompile.h"
#include "BenchRoomLevel.h"
#include "Player.h"
#include "UI_HpBar.h"
#include "BitMap.h"
#include "ViewMap.h"
#include "JumpBug.h"
#include <GameEngine\PostFade.h>
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>


BenchRoomLevel::BenchRoomLevel()
{
}

BenchRoomLevel::~BenchRoomLevel()
{
}

void BenchRoomLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());

	{
		BitMapActor = CreateActor<BitMap>();
		BitMapActor->Progress = MapProgress::BENCHROOM;
	}

	{
		VieMapActor = CreateActor<ViewMap>();
	}


	{
		PlayerActor = CreateActor<Player>();
		PlayerActor->PlayerDirection = LeftRight::RIGHT;
		PlayerActor->GetTransform()->SetLocalPosition({ 7300.0f,-2400.0f , 1.0f});
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());

	}

	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}

	{
		JumpActor = CreateActor<JumpBug>();
		JumpActor->GetTransform()->SetLocalPosition(float4(8500.0f, -2870.0f, 1.0f));
	}

	Reverse = false;
}

void BenchRoomLevel::LevelUpdate(float _DeltaTime)
{
	//프리카메라 상태 온오프
	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	if (true == GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

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

	{
		//플레이어의 위치로 카메라를 이동
		GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x ,-2650.0f, PlayerPos.z });

		if (PlayerPos.x <= 7600.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 7600.0f ,-2650.0f, PlayerPos.z });
		}

		if (PlayerPos.x >= 8700.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 8700.0f ,-2650.0f, PlayerPos.z });
		}
	}

	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
		float4 Size = { 128, 72 };
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
void BenchRoomLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	GameEngineLevel::PrevMap = "BenchRoom";
}

void BenchRoomLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	FadeOn();

	Player::MainPlayer = PlayerActor;

	{
		if (Reverse == false)
		{
		PlayerActor->PlayerDirection = LeftRight::RIGHT;
		PlayerActor->GetTransform()->SetLocalPosition({ 7300.0f,-2400.0f, 1.0f});
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
		Reverse = true;
		}
		else
		{
			PlayerActor->PlayerDirection = LeftRight::LEFT;
			PlayerActor->GetTransform()->SetLocalPosition({ 9350.0f,-2850.0f, 1.0f });
			GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
		}
	}
}

void BenchRoomLevel::FadeOn()
{
	FadeEffect->SetData(0.5f, FadeOption::LIGHT);
}

void BenchRoomLevel::FadeOff()
{
	FadeEffect->SetData(0.5f, FadeOption::DARK);
}