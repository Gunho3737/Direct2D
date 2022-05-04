#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// 분류 : 
// 용도 : 
// 설명 : 
class MiddleBoss : public GameEngineActor
{
private:	// member Var

public:
	MiddleBoss(); // default constructer 디폴트 생성자
	~MiddleBoss(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

	float StartX;
protected:		// delete constructer
	MiddleBoss(const MiddleBoss& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MiddleBoss(MiddleBoss&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MiddleBoss& operator=(const MiddleBoss& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MiddleBoss& operator=(const MiddleBoss&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Wake();
	void Walk();
	void Turn();
	void Attack();

	void JumpReady();
	void Jump();
	void GetUp();

	void Death();

public:
	bool GetDamage;
	int HP;

	float MoveDistance;
	float ImmuneTime;
	float SpinTime;
	float Speed;
};

