#include "PreCompile.h"
#include "FinalBossRoomLevel.h"
#include "Player.h"
#include "UI_HpBar.h"
#include "FlyBug.h"
#include "BitMap.h"
#include "ViewMap.h"
#include "FinalBoss.h"
#include "CollapseFloor.h"
#include "Door.h"
#include <GameEngine\PostFade.h>
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>

bool FinalBossRoomLevel::BossBattleOn = false;
Door* FinalBossRoomLevel::BossBlockDoor = nullptr;
Door* FinalBossRoomLevel::EndingBlockDoor = nullptr;

FinalBossRoomLevel::FinalBossRoomLevel() // default constructer ����Ʈ ������
{

}

FinalBossRoomLevel::~FinalBossRoomLevel() // default destructer ����Ʈ �Ҹ���
{

}

void FinalBossRoomLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());

	{
		BitMapActor = CreateActor<BitMap>();
		BitMapActor->Progress = MapProgress::FINALBOSSROOM;
	}

	{
		ViewMap* Player = CreateActor<ViewMap>();
	}

	{
		PlayerActor = CreateActor<Player>();
		PlayerActor->PlayerDirection = LeftRight::LEFT;
		PlayerActor->GetTransform()->SetLocalPosition({ 3900.0f, -1950.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}

	{
		UI_HpBar* Actor = CreateActor<UI_HpBar>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	}

	{
		CollapseFloor* Floor = CreateActor<CollapseFloor>();
		Floor->GetTransform()->SetWorldPosition({ 1650.0f,-842.0f, -90.0f });
		CollapseFloor::FinalBossRoomFloor = Floor;
	}

	{
		FinalBossActor = CreateActor<FinalBoss>();
		FinalBossActor->GetTransform()->SetWorldPosition({ 1000.0f,-700.0f});
		FinalBossActor->Direction = LeftRight::RIGHT;
	}

	{
		FinalBossRoomLevel::BossBlockDoor = CreateActor<Door>();
		//2370, 630
		FinalBossRoomLevel::BossBlockDoor->DoorOn = false;
		FinalBossRoomLevel::BossBlockDoor->GetTransform()->SetWorldPosition({ 2370.0f,-600.0f , -70.0f });
	}

	{
		FinalBossRoomLevel::EndingBlockDoor = CreateActor<Door>();
		//830 2080
		FinalBossRoomLevel::EndingBlockDoor->DoorOn = true;
		FinalBossRoomLevel::EndingBlockDoor->GetTransform()->SetWorldPosition({ 820.0f,-1950.0f , -70.0f});
	}
	

	BossBattleOn = false;
}

void FinalBossRoomLevel::LevelUpdate(float _DeltaTime)
{
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

	if (PlayerPos.y < -1750.0f)
	{
		if (PlayerPos.x < 1000.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 1000.0f, -1750.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 1000.0f && PlayerPos.x <= 3200.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -1750.0f, PlayerPos.z });
		}
		else if (PlayerPos.x >= 3200.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalPosition({ 3200.0f, -1750.0f, PlayerPos.z });
		}
	}
	

	if (BossBattleOn == false)
	{
		if (PlayerPos.y >= -1750.0f && PlayerPos.y <= -600.0f)
		{
			if (PlayerPos.x < 1000.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 1000.0f, PlayerPos.y, PlayerPos.z });
			}
			else if (PlayerPos.x >= 1000.0f && PlayerPos.x <= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, PlayerPos.y, PlayerPos.z });
			}
			else if (PlayerPos.x >= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 3200.0f, PlayerPos.y, PlayerPos.z });
			}
		}
	
		if (PlayerPos.y > -600.0f)
		{
			if (PlayerPos.x < 1000.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 1000.0f, -600.0f, PlayerPos.z });
			}
			else if (PlayerPos.x >= 0.0f && PlayerPos.x <= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -600.0f, PlayerPos.z });
			}
			else if (PlayerPos.x >= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 3200.0f, -600.0f, PlayerPos.z });
			}
		}
	}
	else if (BossBattleOn == true)
	{
		if (GetMainCameraActor()->GetTransform()->GetLocalPosition().y < -450.0f)
		{
			GetMainCameraActor()->GetTransform()->SetLocalDeltaTimeMove(float4::UP * 200.0f);

			if (PlayerPos.x < 1000.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 1000.0f, GetMainCameraActor()->GetTransform()->GetLocalPosition().y, PlayerPos.z });
			}
			else if (PlayerPos.x >= 0.0f && PlayerPos.x <= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, GetMainCameraActor()->GetTransform()->GetLocalPosition().y, PlayerPos.z });
			}
			else if (PlayerPos.x >= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 3200.0f, GetMainCameraActor()->GetTransform()->GetLocalPosition().y, PlayerPos.z });
			}
		}
		else if (GetMainCameraActor()->GetTransform()->GetLocalPosition().y >= -450.0f)
		{
			if (PlayerPos.x < 1000.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 1000.0f, -450.0f, PlayerPos.z });
			}
			else if (PlayerPos.x >= 0.0f && PlayerPos.x <= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ PlayerPos.x, -450.0f, PlayerPos.z });
			}
			else if (PlayerPos.x >= 3200.0f)
			{
				GetMainCameraActor()->GetTransform()->SetLocalPosition({ 3200.0f, -450.0f, PlayerPos.z });
			}
		}
	}


	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
		float4 Size = { 128, 72};
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

void FinalBossRoomLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	GameEngineLevel::PrevMap = "FinalBossRoom";
}

void FinalBossRoomLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	FadeOn();

	Player::MainPlayer = PlayerActor;

	{
		BitMapActor->Progress = MapProgress::FINALBOSSROOM;
	}

	{
		PlayerActor->PlayerDirection = LeftRight::LEFT;
		PlayerActor->GetTransform()->SetLocalPosition({ 3900.0f, -2080.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(PlayerActor->GetTransform()->GetLocalPosition());
	}
}

void FinalBossRoomLevel::FadeOn()
{
	FadeEffect->SetData(0.5f, FadeOption::LIGHT);
}

void FinalBossRoomLevel::FadeOff()
{
	FadeEffect->SetData(0.5f, FadeOption::DARK);
}
