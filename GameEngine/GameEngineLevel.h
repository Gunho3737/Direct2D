#pragma once
#include <list>
#include <map>
#include "GameEngineActor.h"
#include "GameEngineActor.h"

// Ό³Έν : 
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:
	std::map<int, std::list<GameEngineActor*>> ActorList_;

public:
	void CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new GameEngineActor();
		NewActor->SetLevel(this);

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);
	}

	void Update(float _DeltaTime);

	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();
};