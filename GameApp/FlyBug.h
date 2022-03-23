#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class FlyBug : public GameEngineActor
{
public:
	// constrcuter destructer
	FlyBug();
	~FlyBug();

	// delete Function
	FlyBug(const FlyBug& _Other) = delete;
	FlyBug(FlyBug&& _Other) noexcept = delete;
	FlyBug& operator=(const FlyBug& _Other) = delete;
	FlyBug& operator=(FlyBug&& _Other) noexcept = delete;

	GameEngineImageRenderer* PlayerImageRenderer;
	GameEngineCollision* Collision;

	bool Immune;

protected:
	//콜백함수용 함수, 기능에 맞춰서 이름붙힐것
	void TestStartCallBack();
	void Die();

	int HP;

	float ImmuneTime;
	
private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void ImmuneOff();
};

