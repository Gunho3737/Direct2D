#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <vector>


// 분류 : 
// 용도 : 
// 설명 : 
class CollapseFloor : public GameEngineActor
{
private:	// member Var

public:
	CollapseFloor(); // default constructer 디폴트 생성자
	~CollapseFloor(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

	GameEngineImageRenderer* CollapseImageRenderer0;
	GameEngineImageRenderer* CollapseImageRenderer1;
	GameEngineImageRenderer* CollapseImageRenderer2;

	static bool CollapseOn;
	//std::vector<GameEngineImageRenderer*> CollapseFloorPieces;

	static CollapseFloor* FinalBossRoomFloor;

public:


protected:		// delete constructer
	CollapseFloor(const CollapseFloor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	CollapseFloor(CollapseFloor&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	CollapseFloor& operator=(const CollapseFloor& _other) = delete; // default Copy operator 디s폴트 대입 연산자
	CollapseFloor& operator=(const CollapseFloor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
	
private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

