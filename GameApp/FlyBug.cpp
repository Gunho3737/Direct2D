#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "FlyBug.h" 
#include <GameApp/BitMap.h>
#include "Player.h"



FlyBug::FlyBug()
	: HP(3), GetDamage(false), ImmuneTime(0.0f), Speed(300.0f)
{
}

FlyBug::~FlyBug()
{
}


void FlyBug::Start()
{
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("FlyBug.png");
		//	
		//		//잘린 이미지중 몇번째 스프라이트를 사용할지 선택(애니메이션이 아닌 )
		//		PlayerImageRenderer->SetIndex(10);
		//	

		//애니메이션 제작
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Idle", 1, 6, 0.1f);
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Startle", 10, 13, 0.1f);
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Chase", 14, 19, 0.1f);
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Die", 21, 23, 0.1f, false);
		//	
		//		//애니메이션의 첫프레임/마지막 프레임/애니메이션의x번째프레임을 지정해 특정 함수가 실행되도록한다
		//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&FlyBug::TestStartCallBack, this));
		//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&FlyBug::TestEndCallBack, this));

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 300.0f, 300.0f, 1.0f });


	}

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 90.0f, 80.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({-10.0f, 40.0f, -10.0f});

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 500.0f, 300.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -10.0f });

	StateManager_.CreateState("Idle", std::bind(&FlyBug::Idle, this));
	StateManager_.CreateState("Startle", std::bind(&FlyBug::Startle, this));
	StateManager_.CreateState("Chase", std::bind(&FlyBug::Chase, this));
	StateManager_.CreateState("Die", std::bind(&FlyBug::Die, this));

	StateManager_.ChangeState("Idle");


}

void FlyBug::Update(float _DeltaTime)
{
	StateManager_.Update();

	MapBotCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 0.0f, 0.0f});

	MapTopCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 150.0f, 0.0f});
	MapLeftCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 0.0f, 0.0f});
	MapRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 0.0f, 0.0f});


	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(RangeCollision->GetTransform(), CollisionType::Rect);
	}

	if (Direction == LeftRight::LEFT)
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
	}
	else
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f } *= float4::XFLIP);
	}

	if (HP <= 0)
	{
		StateManager_.ChangeState("Die");
	}

	if (true == GetDamage)
	{
		ImmuneTime -= _DeltaTime;

		if (Direction == LeftRight::LEFT)
		{
			if (MapRightCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 500.0f);
			}
		}
		else if (Direction == LeftRight::RIGHT)
		{
			if (MapLeftCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 500.0f);
			}
		}

		if (Player::MainPlayer->GetTransform()->GetWorldPosition().y >= Collision->GetTransform()->GetWorldPosition().y)
		{
			if (MapBotCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 300.0f);
			}
		}
		else if (Player::MainPlayer->GetTransform()->GetWorldPosition().y < Collision->GetTransform()->GetWorldPosition().y)
		{
			if (MapTopCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::UP * 300.0f);
			}
		}

		if (ImmuneTime <= 0.0f)
		{
			GetDamage = false;
			Collision->On();
			PlayerImageRenderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		}
	}

	if (false == GetDamage)
	{
		Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
			[&](GameEngineCollision* _OtherCollision)
			{
				HP -= 1;
				GetDamage = true;
				ImmuneTime = 0.2f;
				Collision->Off();
				if ("Die" != PlayerImageRenderer->GetCurrentAnimationName())
				{
					PlayerImageRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
				}
			}
		);
	}

}


void FlyBug::Idle()
{
	PlayerImageRenderer->SetChangeAnimation("Idle");

	RangeCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			StateManager_.ChangeState("Startle");
		}
	);
}

void FlyBug::Die()
{
	PlayerImageRenderer->SetChangeAnimation("Die");

	if (MapBotCollisionColor != float4::BLACK)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN *1000.0f);
	}

	PlayerImageRenderer->SetEndCallBack("Die", [&]()
		{
			StateManager_.ChangeState("Idle");
			Off();
		}
	);
}

void FlyBug::Startle()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();
	
	if (PlayerPos.x > MonsterPos.x)
	{
		Direction = LeftRight::RIGHT;
	}
	else
	{
		Direction = LeftRight::LEFT;
	}

	PlayerImageRenderer->SetChangeAnimation("Startle");

	PlayerImageRenderer->SetEndCallBack("Startle", [&]()
		{
			StateManager_.ChangeState("Chase");
		}
	);
}

void FlyBug::Chase()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();
	PlayerImageRenderer->SetChangeAnimation("Chase");
	LeftRight PostDirection = Direction;

	if (PlayerPos.x > MonsterPos.x)
	{
		Direction = LeftRight::RIGHT;

		if (MapRightCollisionColor != float4::BLACK)
		{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	
		if (PlayerPos.y > MonsterPos.y)
		{
			if (MapTopCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
			}
		}
		else
		{
			if (MapBotCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed);
			}
		}
	
	}
	else
	{
		Direction = LeftRight::LEFT;
		if (MapLeftCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}

		if (PlayerPos.y > MonsterPos.y)
		{
			if (MapTopCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
			}
		}
		else
		{
			if (MapBotCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed);
			}
		}
	
	}

	if (MapBotCollisionColor == float4::BLACK)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
	}

	//x값이 겹칠경우 float 값때문에 발작하는것 방지
	if (-2.0f <= (PlayerPos.x - MonsterPos.x) &&
		2.0f >= (PlayerPos.x - MonsterPos.x)
		)
	{
		Direction = PostDirection;
	}


}