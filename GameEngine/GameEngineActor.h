#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// Ό³Έν :
class GameEngineLevel;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	GameEngineLevel* GetLevel()
	{
		return Level;
	}


protected:
	virtual void Update(float _DeltaTime);

private:
	GameEngineLevel* Level;

	void SetLevel(GameEngineLevel* Level);
};

