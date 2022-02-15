#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// Ό³Έν :
class GameEngineActor;
class GameEngineComponent : public GameEngineObjectNameBase
{
public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	GameEngineActor* GetActor() 
	{
		return Actor_;
	}

protected:
	virtual void InitComponent(GameEngineActor* Actor_);

private:
	GameEngineActor* Actor_;



};

