#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "Monster.h"
#include "Bullet.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::TestStartCallBack()
{
	int a = 0;
}

void Monster::TestEndCallBack()
{
	Death();
}

void Monster::Start()
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
//		PlayerImageRenderer->SetImage("Animation.png");
//	
//		//잘린 이미지중 몇번째 스프라이트를 사용할지 선택(애니메이션이 아닌 )
//		PlayerImageRenderer->SetIndex(10);
//	
//		//애니메이션 제작
//		PlayerImageRenderer->CreateAnimation("Test", 0, 20, 0.5f);
//	
//		//애니메이션의 첫프레임/마지막 프레임/애니메이션의x번째프레임을 지정해 특정 함수가 실행되도록한다
//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&Monster::TestStartCallBack, this));
//		PlayerImageRenderer->SetEndCallBack("Test", std::bind(&Monster::TestEndCallBack, this));
//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&Monster::TestEndCallBack, this));
//	
//		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
//		PlayerImageRenderer->SetChangeAnimation("Test");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });


	}

	{
		GameEngineCollision* Collision = CreateTransformComponent<GameEngineCollision>(20);
		Collision->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
	}

}

void Monster::Update(float _DeltaTime)
{

}