#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "BitMap.h"

BitMap* BitMap::CurrentMap = nullptr;

BitMap::BitMap()
{
}

BitMap::~BitMap()
{
}

void BitMap::Start()
{
	{
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		ImageRenderer->SetImage("FinalBitMap_ver01.Png");
		float4 Mapsize = ImageRenderer->GetCurrentTexture()->GetTextureSize();
		ImageRenderer->GetTransform()->SetLocalPosition({Mapsize.hx(), -(Mapsize.hy()), 100.0f});
		ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());
	}

	//사이즈의 z값은 1.0f
	RoomSkipCollsionSize = float4{ 60.0f, 300.0f, 1.0f};

	{
		BenchNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		BenchNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		BenchNextCollision->GetTransform()->SetLocalPosition(float4{ 9500.0f, -2800.0f, -10.0f });


	}
	
	{
		MiddleRoomNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		MiddleRoomNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		MiddleRoomNextCollision->GetTransform()->SetLocalPosition(float4{ 9500.0f, -1550.0f, -10.0f });
	}

	{
		MiddleBossNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		MiddleBossNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		MiddleBossNextCollision->GetTransform()->SetLocalPosition(float4{ 4050.0f, -1950.0f, -10.0f });
	}

	{
		FinalBossNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		FinalBossNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);

	}

	{
		MiddleRoomPrevCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PREVMAP);
		MiddleRoomPrevCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		MiddleRoomPrevCollision->GetTransform()->SetLocalPosition(float4{ 9500.0f, -2800.0f, -10.0f });
	}

	{
		MiddleBossPrevCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PREVMAP);
		MiddleBossPrevCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		MiddleBossPrevCollision->GetTransform()->SetLocalPosition(float4{ 9500.0f, -1550.0f, -10.0f });
	}

	{
		FinalBossPrevCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PREVMAP);
		FinalBossPrevCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		FinalBossPrevCollision->GetTransform()->SetLocalPosition(float4{ 4000.0f, -1950.0f, -10.0f });
	}

	{
		MIddleBossRightMoveBlockCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERMOVESTOP));
		MIddleBossRightMoveBlockCollision->GetTransform()->SetLocalScaling(float4{ 10.0f, 300.0f, 1.0f });
		MIddleBossRightMoveBlockCollision->GetTransform()->SetLocalPosition(float4{ 8950.0f, -2100.0f, -10.0f });
	}

	{
	//7150, 2120
		MIddleBossLeftMoveBlockCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERMOVESTOP));
		MIddleBossLeftMoveBlockCollision->GetTransform()->SetLocalScaling(float4{ 10.0f, 300.0f, 1.0f });
		MIddleBossLeftMoveBlockCollision->GetTransform()->SetLocalPosition(float4{ 7150.0f, -2100.0f, -10.0f });
	}
}

void BitMap::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	CurrentMap = this;
}

float4 BitMap::GetColor(GameEngineTransform* _Ptr, bool YReverse /*= true*/)
{
	float4 Pos = _Ptr->GetWorldPosition();

	return GetColor(Pos, true);
}

float4 BitMap::GetColor(float4 _Position, bool YReverse /*= true*/)
{
	float4 Pos = _Position;

	if (true == YReverse)
	{
		Pos.y *= -1.0f;
	}

	return CurrentMap->ImageRenderer->GetCurrentTexture()->GetPixel(Pos.ix(), Pos.iy());
}

void BitMap::Update(float DeltaTime_)
{
	if (true == GetLevel()->IsDebugCheck())
	{
		switch (BitMap::Progress)
		{
		case MapProgress::BENCHROOM:
		{
			GetLevel()->PushDebugRender(BenchNextCollision->GetTransform(), CollisionType::Rect);
		}
		break;
		case MapProgress::MIDDLEROOM:
		{
			GetLevel()->PushDebugRender(MiddleRoomNextCollision->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(MiddleRoomPrevCollision->GetTransform(), CollisionType::Rect);
		}
		break;
		case MapProgress::MIDDLEBOSSROOM:
		{
			GetLevel()->PushDebugRender(MiddleBossNextCollision->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(MiddleBossPrevCollision->GetTransform(), CollisionType::Rect);
		}
			break;
		case MapProgress::FINALBOSSROOM:
		{
			//GetLevel()->PushDebugRender(FinalBossNextCollision->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(FinalBossPrevCollision->GetTransform(), CollisionType::Rect);
		}
			break;
		default:
			break;
		}

		GetLevel()->PushDebugRender(MIddleBossRightMoveBlockCollision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(MIddleBossLeftMoveBlockCollision->GetTransform(), CollisionType::Rect);
	}

	switch (BitMap::Progress)
	{
	case MapProgress::BENCHROOM:
	{
		BenchNextCollision->On();
		MiddleRoomPrevCollision->Off();
	}
		break;
	case MapProgress::MIDDLEROOM:
	{
		BenchNextCollision->Off();
		MiddleRoomPrevCollision->On();
		MiddleRoomNextCollision->On();
	}
		break;
	case MapProgress::MIDDLEBOSSROOM:
		MiddleRoomPrevCollision->Off();
		MiddleRoomNextCollision->Off();
		MiddleBossPrevCollision->On();
		break;
	case MapProgress::FINALBOSSROOM:
		break;
	default:
		break;
	}

	
}