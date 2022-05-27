#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// 분류 : 
// 용도 : 
// 설명 : 
class DashBug : public GameEngineActor
{
private:	// member Var

public:
	DashBug(); // default constructer 디폴트 생성자
	~DashBug(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* ImageRenderer;
	GameEngineImageRenderer* DeathEffectRenderer;

	//몬스터자체의콜리전
	GameEngineCollision* Collision;

	//플레이어 인식콜리전
	GameEngineCollision* ViewCollision;

	//몬스터 공격패턴 인식거리 콜리전
	GameEngineCollision* RangeCollision;
	GameEngineFSM StateManager_;
	LeftRight Direction;

	float4 MapBotCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

protected:		// delete constructer
	DashBug(const DashBug& _other) = delete; // default Copy constructer 디폴트 복사생성자
	DashBug(DashBug&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	DashBug& operator=(const DashBug& _other) = delete; // default Copy operator 디폴트 대입 연산자
	DashBug& operator=(const DashBug&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Walk();
	void DashReady();
	void Dash();
	void DashCoolDown();
	void Death();


	void SetCallBackFunc();

	void DirectionCheck();
public:
	bool GetDamage;

	int HP;

	float ImmuneTime;
	float DashTime;
	float Speed;
};

