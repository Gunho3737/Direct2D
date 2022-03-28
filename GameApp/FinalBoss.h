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
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

protected:		// delete constructer
	FinalBoss(const FinalBoss& _other) = delete; // default Copy constructer 디폴트 복사생성자
	FinalBoss(FinalBoss&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	FinalBoss& operator=(const FinalBoss& _other) = delete; // default Copy operator 디폴트 대입 연산자
	FinalBoss& operator=(const FinalBoss&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

