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
	
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		ImageRenderer->SetImage("FinalMap_ver01.Png");
		float4 Mapsize = ImageRenderer->GetCurrentTexture()->GetTextureSize();
		ImageRenderer->GetTransform()->SetLocalPosition({ Mapsize.hx(), -(Mapsize.hy()), -80.0f });
		ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());


	{
		BackGroundImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		BackGroundImageRenderer->SetImage("BackGroundMap.Png");
		BackGroundImageRenderer->GetTransform()->SetLocalPosition({ Mapsize.hx(), -(Mapsize.hy()), 80.0f });
		BackGroundImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());
	}

	{
		FogRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		//FogRenderer->SetRenderingPipeLine("TextureTrans");
		FogRenderer->SetAlpha(0.5f);
		FogRenderer->SetImage("fog.Png");
		FogRenderer->CreateAnimation("fog.png", "fog", 0, 15, 0.15f);
		FogRenderer->SetChangeAnimation("fog");
		FogRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize() *= 5.0f);
		FogRenderer->GetTransform()->SetLocalPosition({(Mapsize.hx()), -(Mapsize.y += 400.0f), 10.0f});
	}
}

void ViewMap::LevelChangeStartEvent()
{
}
