#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Map.h"

Map* Map::CurrentMap = nullptr;

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	{
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		ImageRenderer->SetImage("BenchBitMap.Png");
		float4 Mapsize = ImageRenderer->GetCurrentTexture()->GetTextureSize();
		ImageRenderer->GetTransform()->SetLocalPosition({Mapsize.hx(), -(Mapsize.hy()), 100.0f});
		ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());
	}
}

void Map::LevelChangeStartEvent()
{
	CurrentMap = this;
}

float4 Map::GetColor(GameEngineTransform* _Ptr, bool YReverse /*= true*/)
{
	float4 Pos = _Ptr->GetWorldPosition();

	return GetColor(Pos, true);
}

float4 Map::GetColor(float4 _Position, bool YReverse /*= true*/)
{
	float4 Pos = _Position;

	if (true == YReverse)
	{
		Pos.y *= -1.0f;
	}

	return CurrentMap->ImageRenderer->GetCurrentTexture()->GetPixel(Pos.ix(), Pos.iy());
}