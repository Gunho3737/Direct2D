#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// 분류 : 
// 용도 : 
// 설명 : 
class JumpBug : public GameEngineActor
{
private:	// member Var

public:
	JumpBug(); // default constructer 디폴트 생성자
	~JumpBug(); // default destructer 디폴트 소멸자

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
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

	GameEngineSoundPlayer* MoveSoundPlayer;

protected:		// delete constructer
	JumpBug(const JumpBug& _other) = delete; // default Copy constructer 디폴트 복사생성자
	JumpBug(JumpBug&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	JumpBug& operator=(const JumpBug& _other) = delete; // default Copy operator 디폴트 대입 연산자
	JumpBug& operator=(const JumpBug&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Walk();
	void JumpReady();
	void Jump();
	void JumpAttack();
	void Death();


	void SetCallBackFunc();

	void DirectionCheck();
public:
	float4 JumpPower;

	bool GetDamage;

	int HP;

	float ImmuneTime;
	float Speed;
};

