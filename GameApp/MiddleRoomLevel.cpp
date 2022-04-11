#include "PreCompile.h"
#include "MiddleRoomLevel.h"
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

MiddleRoomLevel::MiddleRoomLevel() // default constructer ����Ʈ ������
{

}

MiddleRoomLevel::~MiddleRoomLevel() // default destructer ����Ʈ �Ҹ���
{

}

void MiddleRoomLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());

	Reverse = false;

	{
		BitMapActor = CreateActor<BitMap>();
		BitMapActor->Progress = MapProgress::MIDDLEROOM;
	}

	{
		ViewMap* Player = CreateActor<ViewMap>();
	}

	{
		PlayerActor = CreateActor<Player>();
		PlayerActor->PlayerDirection = LeftRight::RIGHT;
		PlayerActor->GetTransform()->SetLocalPosition({ 9600.0f,-2850.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}

	{
		FlyBug* Actor = CreateActor<FlyBug>();
		Actor->GetTransform()->SetWorldPosition(float4(10000.0f, -2900.0f, 0.0f));
	}

	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}

}

void MiddleRoomLevel::LevelUpdate(float _DeltaTime)
{
	//����ī�޶� ���� �¿���
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

	if (PlayerPos.y < -2760.0f)
	{
		if (PlayerPos.x < 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10250.0f, -2760.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10250.0f && PlayerPos.x <= 10300.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -2760.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10300.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10300.0f, -2760.0f, PlayerPos.z });
		}
	}
	

	if (PlayerPos.y >= -2760.0f && PlayerPos.y <= -1600.0f )
	{
		if (PlayerPos.x < 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10250.0f, PlayerPos.y, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10250.0f && PlayerPos.x <= 10300.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, PlayerPos.y, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10300.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10300.0f, PlayerPos.y, PlayerPos.z });
		}
	}


	if (PlayerPos.y > -1600.0f)
	{
		if (PlayerPos.x < 10250.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10250.0f, -1600.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10250.0f && PlayerPos.x <= 10300.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -1600.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 10300.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 10300.0f, -1600.0f, PlayerPos.z });
		}
	}


	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
		float4 Size = {128, 72};
		Window->PushRenderTarget("���� ī�޶� Ÿ��", GetMainCamera()->GetCameraRenderTarget(), Size * 3);
		Window->PushRenderTarget("UI ī�޶� Ÿ��", GetUICamera()->GetCameraRenderTarget(), Size * 3);
		//Window->PushRenderTarget("PostEffectFade", PlayerActor->FadeEffect->GetResult(), Size * 3);
		Check = true;
	}

	if (true == GameEngineInput::GetInst().Down("LevelControl"))
	{
		GameEngineGUIWindow* Window = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");

		Window->OnOffChange();
	}

}

void MiddleRoomLevel::LevelChangeEndEvent()
{
	GameEngineLevel::PrevMap = "MiddleRoom";
}

void MiddleRoomLevel::LevelChangeStartEvent()
{
	FadeOn();

	{
		BitMapActor->Progress = MapProgress::MIDDLEROOM;
	}

	if (GameEngineLevel::PrevMap == "BenchRoom")
	{
		Reverse = false;
	}

	if (Reverse == false)
	{
		PlayerActor->PlayerDirection = LeftRight::RIGHT;
		PlayerActor->GetTransform()->SetLocalPosition({ 9600.0f,-2850.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
		Reverse = true;
	}
	else
	{
		PlayerActor->PlayerDirection = LeftRight::RIGHT;
		PlayerActor->GetTransform()->SetLocalPosition({ 9600.0f,-1550.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}
}

void MiddleRoomLevel::FadeOn()
{
	FadeEffect->SetData(0.5f, FadeOption::LIGHT);
}

void MiddleRoomLevel::FadeOff()
{
	FadeEffect->SetData(0.5f, FadeOption::DARK);
}
