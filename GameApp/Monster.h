#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	//콜백함수용 함수, 기능에 맞춰서 이름붙힐것
	void TestStartCallBack();
	void TestEndCallBack();

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

