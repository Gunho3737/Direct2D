#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "FlyBug.h"


FlyBug::FlyBug()
{
}

FlyBug::~FlyBug()
{
}

void FlyBug::TestStartCallBack()
{
	int a = 0;
}

void FlyBug::TestEndCallBack()
{
	Death();
}

void FlyBug::Start()
{
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	//{
	//	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	//	Renderer->SetRenderingPipeLine("Color");
	//	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	//	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(0.0f, 0.0f, 0.0f));
	//}

	{
		GameEngineImageRenderer* PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("FlyBug.png");
		//	
		//		//잘린 이미지중 몇번째 스프라이트를 사용할지 선택(애니메이션이 아닌 )
		//		PlayerImageRenderer->SetIndex(10);
		//	
		//애니메이션 제작
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Idle", 1, 6, 0.1f);
		//	
		//		//애니메이션의 첫프레임/마지막 프레임/애니메이션의x번째프레임을 지정해 특정 함수가 실행되도록한다
		//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&FlyBug::TestStartCallBack, this));
		//		PlayerImageRenderer->SetEndCallBack("Test", std::bind(&FlyBug::TestEndCallBack, this));
		//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&FlyBug::TestEndCallBack, this));

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 300.0f, 300.0f, 1.0f });


	}

	Collision = CreateTransformComponent<GameEngineCollision>(20);
	Collision->GetTransform()->SetLocalScaling(float4{ 120.0f, 120.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({0.0f, 50.0f});



}

void FlyBug::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
}