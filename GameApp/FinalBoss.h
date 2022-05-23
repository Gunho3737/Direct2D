#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// 분류 : 
// 용도 : 
// 설명 : 
class FinalBoss : public GameEngineActor
{
private:	// member Var

public:
	FinalBoss(); // default constructer 디폴트 생성자
	~FinalBoss(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* ImageRenderer;
	GameEngineImageRenderer* RealBodyRenderer;

	//보스자체의콜리전
	GameEngineCollision* Collision;

	//플레이어 인식콜리전
	GameEngineCollision* ViewCollision;

	//이동정지후, 방향 전환을 위한 인식 콜리전
	GameEngineCollision* TurnCheckCollision;

	//플레이어와의 거리를 재기위한 콜리전
	GameEngineCollision* RangeCollision;

	//공격자체의 콜리전
	GameEngineCollision* AttackCollision;

	GameEngineFSM StateManager_;
	LeftRight Direction;

	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

protected:		// delete constructer
	FinalBoss(const FinalBoss& _other) = delete; // default Copy constructer 디폴트 복사생성자
	FinalBoss(FinalBoss&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	FinalBoss& operator=(const FinalBoss& _other) = delete; // default Copy operator 디폴트 대입 연산자
	FinalBoss& operator=(const FinalBoss&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Walk();
	void AttackReady();
	void Attack();
	void AttackRecover();
	void Jump();
	void JumpAttack();
	void JumpAttackRecover();
	void Damage();
	void FaceOff();
	void Faint();
	void GetUp();
	void Death();
	void DirectionCheck();

	void FloorCollisionCheck();
	void SetCallBackFunc();

public:
	bool GetDamage;
	bool FloorCheck;

	//갑옷 HP
	int HP;

	//본체 HP
	int BodyHP;

	//바닥꺼지는 연출을 위한 bool
	bool DeathOn;

	//충격파를 사용하기위한 공격횟수카운트
	int GroundAttackCount;

	float4 JumpPower;
	float TurnTime;
	float ImmuneTime;
	float Speed;
};

