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
	RoomSkipCollsionSize = float4{ 60.0f, 130.0f, 1.0f};

	{
		BenchNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		BenchNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
		BenchNextCollision->GetTransform()->SetLocalPosition(float4{ 9500.0f, -2800.0f, -10.0f });


	}
	
	{
		MiddleRoomNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		MiddleRoomNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
	}

	{
		MiddleBossNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		MiddleBossNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);

	}

	{
		FinalBossNextCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::NEXTMAP);
		FinalBossNextCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);

	}

	{
		MiddleRoomPrevCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PREVMAP);
		MiddleRoomPrevCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);

	}

	{
		MiddleBossPrevCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PREVMAP);
		MiddleBossPrevCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);

	}

	{
		FinalBossPrevCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PREVMAP);
		FinalBossPrevCollision->GetTransform()->SetLocalScaling(RoomSkipCollsionSize);
	}

}

void BitMap::LevelChangeStartEvent()
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
			//GetLevel()->PushDebugRender(MiddleRoomNextCollision->GetTransform(), CollisionType::Rect);
			//GetLevel()->PushDebugRender(MiddleRoomPrevCollision->GetTransform(), CollisionType::Rect);
		}
		break;
		case MapProgress::MIDDLEBOSSROOM:
		{
			//GetLevel()->PushDebugRender(MiddleBossNextCollision->GetTransform(), CollisionType::Rect);
			//GetLevel()->PushDebugRender(MiddleBossPrevCollision->GetTransform(), CollisionType::Rect);
		}
			break;
		case MapProgress::FINALBOSSROOM:
		{
			//GetLevel()->PushDebugRender(FinalBossNextCollision->GetTransform(), CollisionType::Rect);
			//GetLevel()->PushDebugRender(FinalBossPrevCollision->GetTransform(), CollisionType::Rect);
		}
			break;
		default:
			break;
		}

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
		//BenchNextCollision->GetTransform()->SetLocalScaling(float4::ZERO);
		//BenchNextCollision->GetTransform()->SetLocalPosition(float4::ZERO);
	}
		break;
	case MapProgress::MIDDLEBOSSROOM:
		break;
	case MapProgress::FINALBOSSROOM:
		break;
	default:
		break;
	}
}