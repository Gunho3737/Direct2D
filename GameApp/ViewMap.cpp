#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"
#include "ViewMap.h"


ViewMap::ViewMap()
{
}

ViewMap::~ViewMap()
{
}

void ViewMap::Start()
{
	{
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		ImageRenderer->SetImage("FinalMap_ver01.Png");
		float4 Mapsize = ImageRenderer->GetCurrentTexture()->GetTextureSize();
		ImageRenderer->GetTransform()->SetLocalPosition({ Mapsize.hx(), -(Mapsize.hy()), -80.0f });
		ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());
	}
}

void ViewMap::LevelChangeStartEvent()
{
}
