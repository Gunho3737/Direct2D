#include "PreCompile.h"
#include "MiddleBossRoomLevel.h"
#include "Player.h"
#include "UI_HpBar.h"
#include "FlyBug.h"
#include "BitMap.h"
#include "ViewMap.h"
#include <GameEngine\PostFade.h>
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>

MiddleBossRoomLevel::MiddleBossRoomLevel() // default constructer 디폴트 생성자
{

}

MiddleBossRoomLevel::~MiddleBossRoomLevel() // default destructer 디폴트 소멸자
{

}

void MiddleBossRoomLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());

	{
		BitMapActor = CreateActor<BitMap>();
		BitMapActor->Progress = MapProgress::MIDDLEBOSSROOM;
	}

	{
		ViewMap* Player = CreateActor<ViewMap>();
	}

	{
		PlayerActor = CreateActor<Player>();
		PlayerActor->PlayerDirection = LeftRight::RIGHT;
		PlayerActor->GetTransform()->SetLocalPosition({ 9400.0f,-1550.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}


	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}

	//FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	//FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());
	//
	//GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
	//float4 Size = { 128, 72 };
	//Window->PushRenderTarget("PostEffectFade", FadeEffect->GetResult(), Size * 3);
	//
	//FadeEffect->SetData(1.0f, FadeOption::LIGHT);

}

void MiddleBossRoomLevel::LevelUpdate(float _DeltaTime)
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
	// x = 4600 ~ 8720
	// y = 1160 ~ 1970
	if (PlayerPos.y < -1970.0f)
	{
		if (PlayerPos.x < 4600.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 4600.0f, -1970.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 4600.0f && PlayerPos.x <= 8720.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -1970.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 8720.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 8720.0f, -1970.0f, PlayerPos.z });
		}
	}
	

	if (PlayerPos.y >= -1970.0f && PlayerPos.y <= -1160.0f)
	{
		if (PlayerPos.x < 4600.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 4600.0f, PlayerPos.y, PlayerPos.z });
		}
		else if (PlayerPos.x >= 4600.0f && PlayerPos.x <= 8720.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, PlayerPos.y, PlayerPos.z });
		}
		else if (PlayerPos.x >= 8720.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 8720.0f, PlayerPos.y, PlayerPos.z });
		}
	}


	if (PlayerPos.y > -1160.0f)
	{
		if (PlayerPos.x < 4600.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 4600.0f, -1160.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 4600.0f && PlayerPos.x <= 8720.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -1160.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 8720.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 8720.0f, -1160.0f, PlayerPos.z });
		}
	}


	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
		float4 Size = { 128, 72};
		Window->PushRenderTarget("메인 카메라 타겟", GetMainCamera()->GetCameraRenderTarget(), Size * 3);
		Window->PushRenderTarget("UI 카메라 타겟", GetUICamera()->GetCameraRenderTarget(), Size * 3);
		//Window->PushRenderTarget("PostEffectFade", PlayerActor->FadeEffect->GetResult(), Size * 3);
		Check = true;
	}

	if (true == GameEngineInput::GetInst().Down("LevelControl"))
	{
		GameEngineGUIWindow* Window = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");

		Window->OnOffChange();
	}

}

void MiddleBossRoomLevel::LevelChangeEndEvent()
{
	GameEngineLevel::PrevMap = "MiddleBossRoom";
}

void MiddleBossRoomLevel::LevelChangeStartEvent()
{
	FadeOn();

	{
		BitMapActor->Progress = MapProgress::MIDDLEBOSSROOM;
	}

	{
		PlayerActor->PlayerDirection = LeftRight::LEFT;
		PlayerActor->GetTransform()->SetLocalPosition({ 9400.0f,-1550.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}



}

void MiddleBossRoomLevel::FadeOn()
{
	FadeEffect->SetData(0.5f, FadeOption::LIGHT);
}

void MiddleBossRoomLevel::FadeOff()
{
	FadeEffect->SetData(0.5f, FadeOption::DARK);
}
