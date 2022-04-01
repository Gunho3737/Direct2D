#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "BitMap.h"

BitMap* BitMap::CurrentMap = nullptr;

BitMap::BitMap()
	: Progress(MapProgress::BENCH)
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