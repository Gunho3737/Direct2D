#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// 분류 : 
// 용도 : 
// 설명 : 
class GroundWave : public GameEngineActor
{
private:	// member Var

public:
	GroundWave(); // default constructer 디폴트 생성자
	~GroundWave(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

	LeftRight Direction;

protected:		// delete constructer
	GroundWave(const GroundWave& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GroundWave(GroundWave&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GroundWave& operator=(const GroundWave& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GroundWave& operator=(const GroundWave&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

