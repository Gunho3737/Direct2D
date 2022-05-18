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
	GameEngineImageRenderer* AttackEffectRenderer;

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
	void Wait(); 
	void Walk();
	void Attack();
	void JumpReady();
	void Jump();
	void GetUp();
	void Death();

public:
	bool GetDamage;

	//이동정지후 회전 여부를 체크하는 bool
	bool TurnOn;

	int HP;

	//충격파를 사용하기위한 공격횟수카운트
	int GroundAttackCount;

	float TurnTime;
	float ImmuneTime;
	float JumpReadyTime;
	float Speed;
};

